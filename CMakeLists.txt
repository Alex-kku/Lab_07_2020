cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)
option(BUILD_DOCS "Build documentation" OFF)
option(BUILD_COVERAGE "Build code coverage" OFF)

set(
        HUNTER_CACHE_SERVERS
        "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
        CACHE STRING "Default cache server"
)

include("cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.290.tar.gz"
        SHA1 "04487198159a9754ac9603aa464cd3de23ca3f3d"
)


# TODO: rename project and delete this comment
project(Server VERSION 0.1.0)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

hunter_add_package(Beast)
find_package(Beast CONFIG REQUIRED)
hunter_add_package(Boost COMPONENTS thread filesystem)
find_package(Boost CONFIG REQUIRED thread filesystem)
find_package(Threads)
hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)
hunter_add_package(nlohmann_json)
find_package(nlohmann_json CONFIG REQUIRED)

#add_executable(demo
#  ${CMAKE_CURRENT_SOURCE_DIR}/sources/Suggest.cpp
# ${CMAKE_CURRENT_SOURCE_DIR}/demo/main.cpp
# )
add_executable(testing
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/Suggest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp
        )
#target_include_directories(demo
# PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
# )
target_include_directories(testing
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        )

#target_link_libraries(demo
#  Beast::Beast
# Boost::filesystem
# Boost::thread
# GTest::gtest_main
# nlohmann_json::nlohmann_json
# )
target_link_libraries(testing
        Beast::Beast
        Boost::filesystem
        Boost::thread
        GTest::gtest_main
        nlohmann_json::nlohmann_json
        )
enable_testing()
add_test(NAME unit_tests COMMAND tests)

if (BUILD_COVERAGE)
    set(ENABLE_COVERAGE ON CACHE BOOL "Enable coverage build." FORCE)
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/coverage/cmake")
    find_package(codecov)
    add_coverage(${PROJECT_NAME})
    add_coverage(tests)
    coverage_evaluate()
endif ()

if (BUILD_DOCS)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/_docs)
    set(DOXYGEN_EXAMPLE_PATH examples)
    set(DOXYGEN_GENERATE_HTML NO)
    set(DOXYGEN_GENERATE_MAN YES)
    find_package(Doxygen)
    doxygen_add_docs(docs include)
    install(DIRECTORY ${DOXYGEN_OUTPUT_DIRECTORY}/man DESTINATION share)
    # add_dependencies(install docs) need to call target docs before install or package
endif ()
