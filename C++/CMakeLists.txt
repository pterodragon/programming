cmake_minimum_required (VERSION 3.6)
project (code_exercises)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(THIRD_PARTY_DIR "${CMAKE_CURRENT_LIST_DIR}/third_party")
list(APPEND CMAKE_INCLUDE_PATH ${THIRD_PARTY_DIR})
add_subdirectory(third_party/Catch2/)

include(FindPackageHandleStandardArgs)
find_package(cxx_prettyprint REQUIRED)

option(build_leetcode_only "build_leetcode_only" OFF)
option(build_codeforces_only "build_codeforces_only" OFF)

if (build_leetcode_only)
    add_subdirectory("leetcode/")
elseif (build_codeforces_only)
    add_subdirectory("codeforces/")
elseif (build_algorithms_only)
    add_subdirectory("algorithms/")
else()
    add_subdirectory("coding_session/")
    add_subdirectory("leetcode/")
    add_subdirectory("lintcode/")
    add_subdirectory("codeforces/")
    add_subdirectory("other_projects/")
    add_subdirectory("algorithms/")
endif()

