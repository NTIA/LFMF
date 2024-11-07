###########################################
## CONFIGURE THE COMMAND LINE DRIVER
###########################################
set(DRIVER_NAME "${LIB_NAME}Driver")
set(DRIVER_VERSION ${PROJECT_VERSION}.0)
set(DRIVER_HEADERS "${PROJECT_SOURCE_DIR}/app/include")

###########################################
## BUILD THE COMMAND LINE DRIVER
###########################################
add_subdirectory(src)

###########################################
## BUILD AND RUN THE DRIVER TESTS
###########################################
if (RUN_DRIVER_TESTS)
    #set_target_properties(${DRIVER_NAME} PROPERTIES ENABLE_EXPORTS ON)
    #add_subdirectory(tests)
    message(STATUS "STATUS: RUNTIME_OUTPUT_DIRECTORY: " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
 
    # define a function to simplify adding tests
    function(do_test test_name test_arg test_result)
      add_test(NAME ${test_name} COMMAND ${DRIVER_NAME}-${DRIVER_VERSION} ${test_arg} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
      set_tests_properties(${test_name}
          PROPERTIES PASS_REGULAR_EXPRESSION ${test_result}
          )
    endfunction()

    # do a bunch of result based tests
    do_test("NoArguments" "" "${DRIVER_NAME} Error:")
    do_test("help" "-h" "Usage:")
    do_test("version" "-v" "Driver Version: ${DRIVER_VERSION}")

    function(result_test test_name input_file output_file test_result)
      add_test(NAME ${test_name} COMMAND ${DRIVER_NAME}-${DRIVER_VERSION} -i ${input_file} -o ${output_file} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
      set_tests_properties(${test_name}
          PROPERTIES PASS_REGULAR_EXPRESSION ${test_result}
          )
    endfunction()
    result_test("results01" "${PROJECT_SOURCE_DIR}/app/data/i_lfmf_01.txt" "o_lfmf_01.txt" "Return Code: 0, LFMF Status: Successful execution\nBasic transmission loss: 184.49")
    result_test("results02" "${PROJECT_SOURCE_DIR}/app/data/i_lfmf_02.txt" "o_lfmf_02.txt" "Return Code: 0, LFMF Status: Successful execution\nBasic transmission loss: 151.33")
    result_test("results03" "${PROJECT_SOURCE_DIR}/app/data/i_lfmf_03.txt" "o_lfmf_03.txt" "Return Code: 0, LFMF Status: Successful execution\nBasic transmission loss: 264.33")
endif()
