###########################################
## BUILD THE COMMAND LINE DRIVER
###########################################
add_subdirectory(src)

###########################################
## BUILD AND RUN THE DRIVER TESTS
###########################################
if (RUN_DRIVER_TESTS)
    set_target_properties(${DRIVER_NAME} PROPERTIES ENABLE_EXPORTS ON)
    add_subdirectory(tests)
endif()
