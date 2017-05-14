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

set(leetcode_dir ${CMAKE_CURRENT_SOURCE_DIR})
set(test_common_dir "${leetcode_dir}/test_common")
SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})
list(FILTER SUBDIRS EXCLUDE REGEX "test_common")

enable_testing ()
include_directories(${CXX_PRETTYPRINT_DIR})
include_directories(${Boost_INCLUDE_DIRS})

FOREACH(subdir ${SUBDIRS})
    file(GLOB_RECURSE HEADERS "${subdir}/*.h" "${subdir}/*.hpp")
    file(GLOB_RECURSE SOURCES "${subdir}/*.cpp")
    list(FILTER HEADERS EXCLUDE REGEX "${subdir}/test/.*")
    list(FILTER SOURCES EXCLUDE REGEX "${subdir}/test/.*")

    set(SOURCES_NO_MAIN ${SOURCES})
    list(FILTER SOURCES_NO_MAIN EXCLUDE REGEX "${subdir}/main.cpp")

    file(GLOB_RECURSE TEST_HEADERS 
        "${subdir}/test/*.h"
        "${subdir}/test/*.hpp"
        "${test_common_dir}/test_common.hpp"
        )
    file(GLOB_RECURSE TEST_SOURCES 
        "${subdir}/test/*.cpp"
        )
    file(GLOB_RECURSE TEST_FILES "${subdir}/test/*.txt")
    get_filename_component(subdirname ${subdir} NAME)
    set(subproject_name ${subdirname})
    add_executable(${subproject_name} ${SOURCES} ${HEADERS})
    target_link_libraries (${subproject_name}
       ${Boost_LIBRARIES}
    )

    if (TEST_SOURCES)
        LIST(APPEND TEST_SOURCES "${test_common_dir}/test_common.cpp")
        set(test_name "${subdirname}_test")
        set(test_output_dir "${CMAKE_CURRENT_BINARY_DIR}/${subdirname}/test")
        add_executable(${test_name} ${SOURCES_NO_MAIN} ${HEADERS} ${TEST_SOURCES} ${TEST_HEADERS})
        target_include_directories (${test_name} PRIVATE
            ${test_common_dir}
            ${subdirname}
        )
        target_link_libraries (${test_name}
           ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
           ${Boost_LIBRARIES}
        )
        add_test (NAME ${test_name}
            COMMAND "$<TARGET_FILE:${test_name}>"
            WORKING_DIRECTORY ${test_output_dir}
        )
        set_target_properties(${test_name} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${test_output_dir}
        )
        set_property(TEST ${test_name}
            PROPERTY LABELS ${test_name}
        )
        FOREACH(test_file ${TEST_FILES})
            get_filename_component(test_file_name ${test_file} NAME)
            configure_file(${test_file} "${test_output_dir}/${test_file_name}" COPYONLY)
        ENDFOREACH()
    endif()
    set_target_properties(${subdirname} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${subdirname}"
    )
ENDFOREACH()
