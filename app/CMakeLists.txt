###########################################
## CONFIGURE THE COMMAND LINE DRIVER
###########################################
set(DRIVER_NAME "${LIB_NAME}Driver")
set(DRIVER_VERSION ${PROJECT_VERSION}) # May be set manually instead
set(DRIVER_HEADERS "${PROJECT_SOURCE_DIR}/app/include")

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
