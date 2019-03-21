get_filename_component(subdirname ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project (${subdirname})

file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${Boost_LIBRARIES})
install(TARGETS ${PROJECT_NAME} DESTINATION bin) # install to usr/local/bin
