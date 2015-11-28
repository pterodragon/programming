cmake_minimum_required (VERSION 3.2)
project (code_exercises)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_path(Boost_INCLUDE_DIR bootstrap.sh)
find_library(Boost 1.58 REQUIRED thread asio)

add_subdirectory(AProject)
add_subdirectory(maximum_subarray_3)

