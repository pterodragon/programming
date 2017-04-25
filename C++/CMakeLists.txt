cmake_minimum_required (VERSION 3.2)
project (code_exercises)

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

SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})



set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_path(Boost_INCLUDE_DIR bootstrap.sh)
#find_package(Boost REQUIRED system thread)

include_directories(${Boost_INCLUDE_DIR})

FOREACH(subdir ${SUBDIRS})
	ADD_SUBDIRECTORY(${subdir})
ENDFOREACH()

