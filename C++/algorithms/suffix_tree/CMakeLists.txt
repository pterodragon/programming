get_filename_component(subdirname ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project (${subdirname})

file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE SOURCES "*.cpp")

include_directories(${Boost_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
install(TARGETS ${PROJECT_NAME} DESTINATION bin) # install to usr/local/bin
