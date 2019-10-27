project(atcoder)

MACRO(SUBDIRLIST result curdir)
	FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
	SET(dirlist "")
	FOREACH(child ${children})
		IF(IS_DIRECTORY ${curdir}/${child})
			LIST(APPEND dirlist ${child})
		ENDIF()
	ENDFOREACH()
	SET(${result} ${dirlist})
ENDMACRO()

set(atcoder_dir ${CMAKE_CURRENT_SOURCE_DIR})
SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing ()

FOREACH(subdir ${SUBDIRS})
    if(NOT EXISTS "${atcoder_dir}/${subdir}/main.cpp")
        continue()
    endif()
    file(GLOB HEADERS "${subdir}/*.h" "${subdir}/*.hpp")
    file(GLOB SOURCES "${subdir}/*.cpp")

    file(GLOB_RECURSE TEST_HEADERS 
        "${subdir}/test/*.h"
        "${subdir}/test/*.hpp"
        )
    file(GLOB_RECURSE TEST_SOURCES "${subdir}/*.cpp" "${subdir}/test/*.cpp")
    list(FILTER TEST_SOURCES EXCLUDE REGEX "main.cpp")
    get_filename_component(subdirname ${subdir} NAME)
    set(subproject_name ${subdirname})
    add_executable(${subproject_name} ${SOURCES} ${HEADERS})
    target_link_libraries(${subproject_name} Catch2::Catch2)

    target_include_directories(${subproject_name} PRIVATE ${CXX_PRETTYPRINT_DIR})
    set_target_properties(${subproject_name} PROPERTIES
        CXX_STANDARD 17
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${subdirname}"
    )

    if (TEST_SOURCES)
        set(test_name "${subdirname}_test")
        set(test_output_dir "${CMAKE_CURRENT_BINARY_DIR}/${subdirname}/test")
        add_executable(${test_name} ${TEST_SOURCES} ${TEST_HEADERS})
        target_include_directories(${test_name} PRIVATE
            ${subdirname} ${CXX_PRETTYPRINT_DIR}
        )
        target_link_libraries(${test_name} Catch2::Catch2)

        add_test (NAME ${test_name}
            COMMAND "$<TARGET_FILE:${test_name}>"
            WORKING_DIRECTORY ${test_output_dir}
        )
        set_target_properties(${test_name} PROPERTIES
            CXX_STANDARD 17
            RUNTIME_OUTPUT_DIRECTORY ${test_output_dir}
        )
    endif()
ENDFOREACH()
