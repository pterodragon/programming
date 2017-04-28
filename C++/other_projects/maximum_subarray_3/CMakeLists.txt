project (Maximum_subarray_3)

file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
install(TARGETS ${PROJECT_NAME} DESTINATION bin) # install to usr/local/bin