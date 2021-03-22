cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(lesson_project VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Threads REQUIRED)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
find_package(spdlog CONFIG REQUIRED)

configure_file(version.h.in ${PROJECT_SOURCE_DIR}/version.h)

add_executable(lesson_project_cli main.cpp)

add_library(lesson_project lib.cpp)

add_executable(test_version test_version.cpp)

set_target_properties(lesson_project_cli lesson_project test_version PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON)

if (NOT WIN32)
    set_target_properties(lesson_project_cli lesson_project test_version PROPERTIES
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )
endif()


set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(lesson_project_cli
    PRIVATE spdlog::spdlog
    lesson_project
    Threads::Threads
)

target_link_libraries(test_version
    ${Boost_LIBRARIES}
    lesson_project
)

if (NOT WIN32)
    install(TARGETS lesson_project_cli RUNTIME DESTINATION bin)

    set(CPACK_GENERATOR DEB)

    set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
    set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
    set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

    set(CPACK_PACKAGE_CONTACT romakashey@gmail.com)

    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

    include(CPack)
endif()

enable_testing()

add_test(lesson_project_tests test_version)
