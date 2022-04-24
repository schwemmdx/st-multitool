# cmake script for generating binary and hex format and for flashing


set(OPENOCD_TARGET st_nucleo_h743zi)

#add_custom_command(OUTPUT ${PROJECT_NAME}.srec
#    DEPENDS ${PROJECT_NAME}
#    COMMAND ${CMAKE_OBJCOPY} -Osrec $<TARGET_FILE:${EXECUTABLE}> ${PROJECT_NAME}.srec
#)
#add_custom_command(OUTPUT ${PROJECT_NAME}.hex
#    DEPENDS ${PROJECT_NAME}
#    COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${EXECUTABLE}> ${PROJECT_NAME}.hex
#)
#add_custom_command(OUTPUT ${PROJECT_NAME}.bin
#    DEPENDS ${PROJECT_NAME}
#    COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${EXECUTABLE}> ${PROJECT_NAME}.bin
#)
add_custom_command(OUTPUT ${PROJECT_NAME}.lst
    DEPENDS ${PROJECT_NAME}
    COMMAND ${CMAKE_OBJDUMP} -S $<TARGET_FILE:${EXECUTABLE}> > ${PROJECT_NAME}.lst
)
add_custom_command(OUTPUT ${PROJECT_NAME}.sym
    DEPENDS ${PROJECT_NAME}
    COMMAND ${CMAKE_NM} -C -l -n -S $<TARGET_FILE:${EXECUTABLE}> > ${PROJECT_NAME}.sym
)

#add_custom_target(srec
#    DEPENDS ${PROJECT_NAME}.srec
#)
#add_custom_target(hex
#    DEPENDS ${PROJECT_NAME}.hex
#)
#add_custom_target(bin
#    DEPENDS ${PROJECT_NAME}.bin
#)
#add_custom_target(lst
#    DEPENDS ${PROJECT_NAME}.lst
#)
#add_custom_target(sym
#    DEPENDS ${PROJECT_NAME}.sym
#)
add_custom_target(FLASH
    openocd -f board/${OPENOCD_TARGET}.cfg -c "program $<TARGET_FILE:${EXECUTABLE}> verify reset exit"
    DEPENDS $<TARGET_FILE:${EXECUTABLE}>
)

