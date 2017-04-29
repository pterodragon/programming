cmake_minimum_required (VERSION 3.4)
project (code_exercises)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(THIRD_PARTY_DIR "${CMAKE_CURRENT_LIST_DIR}/third_party")
list(APPEND CMAKE_INCLUDE_PATH ${THIRD_PARTY_DIR})

include(FindPackageHandleStandardArgs)
find_package(cxx_prettyprint REQUIRED)

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

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Boost 1.62.0 QUIET #OPTIONAL_COMPONENTS filesystem regex
    )
if (NOT Boost_FOUND)
    message(WARNING "Optional Boost dependency not found")
endif()

add_subdirectory("coding_session/")
add_subdirectory("leetcode/")
add_subdirectory("lintcode/")
add_subdirectory("other_projects/")

