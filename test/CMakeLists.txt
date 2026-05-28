include_directories("${PROJECT_SOURCE_DIR}")

set(PROJECT_TEST_NAME ${LIB_NAME}-test)

if(DOWNLOAD_GTEST STREQUAL ON)
    if(MSVC)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()

    if(NOT TARGET gtest)
        include(FetchContent)
        FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG v1.16.0
            GIT_SHALLOW TRUE
        )
        FetchContent_MakeAvailable(googletest)
    endif()
endif()


add_executable(${PROJECT_TEST_NAME}
        create_wavelength_boundary.unit.cpp
        create_integration_rule.unit.cpp
        create_wavelength_set.unit.cpp
        create_spectrum.unit.cpp
        read_standard_from_disk.unit.cpp
        main.cpp
        paths.h)

include_directories(${PROJECT_SOURCE_DIR}/src)

target_link_libraries(${PROJECT_TEST_NAME} gmock_main ${LIB_NAME})

add_test(NAME ${PROJECT_TEST_NAME}-runner COMMAND ${PROJECT_TEST_NAME} "${CMAKE_CURRENT_LIST_DIR}")

target_compile_features(${PROJECT_TEST_NAME} PRIVATE cxx_std_17)
