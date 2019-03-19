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

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

FOREACH(subdir ${SUBDIRS})
	ADD_SUBDIRECTORY(${subdir})
ENDFOREACH()
