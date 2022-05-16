# Basic CMake 
cmake_minimum_required(VERSION 3.12)
include("cmake/gcc-arm-none-eabi.cmake")

project(multitool)



set(APP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/application)
set(CUBEMX_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cube_mx)
set(DRV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/drivers)
set(MIDDLEWARE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/middleware)



option(DUMP_ASM "Create full assembly of final executable" OFF)

# Set microcontroller information
set(MCU_FAMILY STM32H7xx)
set(MCU_MODEL STM32H743xx)
set(CPU_PARAMETERS
    -mcpu=cortex-m7
    -mthumb
    -mfpu=fpv5-sp-d16
    -mfloat-abi=hard)

set(STARTUP_SCRIPT ${CUBEMX_DIR}/startup_stm32h743xx.s)
set(MCU_LINKER_SCRIPT ${CUBEMX_DIR}/STM32H743ZITx_FLASH.ld)

###############################################################################
set(EXECUTABLE ${CMAKE_PROJECT_NAME})

enable_language(C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

###############################################################################
set(STM32CUBEMX_INCLUDE_DIRECTORIES
    ${CUBEMX_DIR}/Core/Inc
    ${CUBEMX_DIR}/Drivers/${MCU_FAMILY}_HAL_Driver/Inc
    ${CUBEMX_DIR}/Drivers/${MCU_FAMILY}_HAL_Driver/Inc/Legacy
    ${CUBEMX_DIR}/Drivers/CMSIS/Device/ST/${MCU_FAMILY}/Include
    ${CUBEMX_DIR}/Drivers/CMSIS/Include)
    
file(GLOB STM32CUBEMX_SOURCES CONFIGURE_DEPENDS
    ${CUBEMX_DIR}/Drivers/${MCU_FAMILY}_HAL_Driver/Src/*.c
    ${CUBEMX_DIR}/Core/Src/*.c
)

set(RTOS_INCLUDE_DIRECTORIES 
    ${MIDDLEWARE_DIR}/rtos/include
    ${MIDDLEWARE_DIR}/rtos/port
)

file(GLOB RTOS_SOURCES CONFIGURE_DEPENDS
    ${MIDDLEWARE_DIR}/rtos/*.c
    ${MIDDLEWARE_DIR}/rtos/port/*.c
)

set(FATFS_INCLUDE_DIRECTORIES
    ${MIDDLEWARE_DIR}/fatfs 
)

file(GLOB FATFS_SOURCES CONFIGURE_DEPENDS
    ${MIDDLEWARE_DIR}/fatfs/*.c
)

set(APP_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/application)

file(GLOB APP_SOURCES CONFIGURE_DEPENDS
    ${APP_DIR}/*.cpp
    ${APP_DIR}/*.c
    )

set(DRV_INCLUDE_DIRECTORIES
    ${DRV_DIR})

file(GLOB DRV_SOURCES CONFIGURE_DEPENDS
    ${DRV_DIR}/*.cpp
    ${DRV_DIR}/*.c
    )


add_executable(${EXECUTABLE}
    ${STM32CUBEMX_SOURCES} 
    ${APP_SOURCES}
    ${STARTUP_SCRIPT}
    ${RTOS_SOURCES}
    ${FATFS_SOURCES})



target_compile_definitions(${EXECUTABLE} PRIVATE
    #$<$<CONFIG:Debug>:DEBUG>
    ${MCU_MODEL}
    USE_HAL_DRIVER)

target_include_directories(${EXECUTABLE} SYSTEM PRIVATE
    ${STM32CUBEMX_INCLUDE_DIRECTORIES}
    )


target_include_directories(${EXECUTABLE} PRIVATE
    ${APP_INCLUDE_DIRECTORIES}
    ${RTOS_INCLUDE_DIRECTORIES}
    ${DRV_INCLUDE_DIRECTORIES}
    ${FATFS_INCLUDE_DIRECTORIES}
    )
###############################################################################
add_compile_definitions(USE_MULTI_CORE_SHARED_CODE=0)
target_compile_options(${EXECUTABLE} PRIVATE
${CPU_PARAMETERS}
    $<$<COMPILE_LANGUAGE:C>:-std=c11>
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>
    $<$<COMPILE_LANGUAGE:CXX>:-fms-extensions>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-use-cxa-atexit>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>

    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wdouble-promotion
    -Wformat=2 -Wformat-truncation
    -Wundef
    -fno-common
    -Wno-unused-parameter

    $<$<COMPILE_LANGUAGE:CXX>:
        -Wconversion # STM libraries!
        -Wno-volatile
        -Wold-style-cast
        -Wuseless-cast
        -Wsuggest-override>

    $<$<CONFIG:Debug>:-Og -g3 -ggdb>
    $<$<CONFIG:Release>:-Og -g0>)

target_link_options(${EXECUTABLE} PRIVATE
    -T${MCU_LINKER_SCRIPT}
    ${CPU_PARAMETERS}
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    --specs=nosys.specs
    -Wl,--start-group
    -lc
    -lm
    -lstdc++
    -Wl,--end-group
    -Wl,--print-memory-usage)



set_property(TARGET ${PROJECT_NAME} PROPERTY LINK_DEPENDS ${CMAKE_SOURCE_DIR}/${LINKER_SCRIPT})
# The last command can take a couple of seconds on larger project, usefull for debugging
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.bin)

if (${DUMP_ASM})
    add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
        COMMAND ${CMAKE_OBJDUMP} -D $<TARGET_FILE:${EXECUTABLE}> > ${EXECUTABLE}.s)
endif()

include ("cmake/utils.cmake")