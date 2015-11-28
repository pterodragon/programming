cmake_minimum_required (VERSION 3.2)
project (code_exercises)

include_directories(temp)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

file(GLOB_RECURSE ALL_HEADERS "temp/*.h")
file(GLOB_RECURSE ALL_SOURCES "temp/*.cpp")
file(GLOB MAIN_SOURCES "*.cpp")

find_path(Boost_INCLUDE_DIR bootstrap.sh)
find_library(Boost 1.58 REQUIRED thread asio)

#loop over all test .cpp files to create executable
foreach( sourcefile ${MAIN_SOURCES} )
	get_filename_component(sourcefilename ${sourcefile} NAME [CACHE])
	string( REPLACE ".cpp" "" basename ${sourcefilename} )
	add_executable( ${basename} ${sourcefile} ${ALL_HEADERS} ${ALL_SOURCES})
	target_link_libraries( ${basename} ${Boost_LIBRARIES})
	install(TARGETS ${basename} DESTINATION bin) # install to usr/local/bin
endforeach()