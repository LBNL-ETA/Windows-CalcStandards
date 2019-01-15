cmake_minimum_required(VERSION 2.8.9)

message("Start Windows Standards CMakeLists.txt")

set( target_name Windows-Standards )

set (CMAKE_CXX_STANDARD 11)

project( ${target_name} )

include( cmake/WindowsStandardsProjectMacros.cmake )
include( cmake/WindowsStandardsInternalUtils.cmake )
include( cmake/WindowsStandardsCompilerFlags.cmake )

# google test will not be created by this project if this is not main project. Main project is expected to handle google test.
get_directory_property(hasParent PARENT_DIRECTORY)

#if(hasParent)
#  set( BUILD_WINDOWSSTANDARDS_TESTING OFF )
#  set( DOWNLOAD_GTEST OFF )
#  if( BUILD_TESTING STREQUAL ON ) # EnergyPlus testing is ON
#    set( BUILD_WINDOWSSTANDARDS_TESTING ON )
#  endif()
#	set( SINGLE_PROJECT ON )
#else()
	option( BUILD_WINDOWS_STANDARDS_TESTING "Build testing targets" ON )
	option( SINGLE_PROJECT "Build windows standards library as single project" OFF )
	set( DOWNLOAD_GTEST ON )
#endif()

if( DOWNLOAD_GTEST STREQUAL ON ) # Do not need gtest since it will be processed by E+
	message("DOWNLOAD_GTEST STREQUAL ON")
	# include(CMakeLists-GTest.txt)
	configure_file(CMakeLists.txt.in ${CMAKE_BINARY_DIR}/googletest-download/CMakeLists.txt)
	execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
	execute_process(COMMAND ${CMAKE_COMMAND} --build .
  		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
  		
  	# Prevent GoogleTest from overriding our compiler/linker options
	# when building with Visual Studio
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
 
	# Add googletest directly to our build. This adds
	# the following targets: gtest, gtest_main, gmock
	# and gmock_main
	add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
    	${CMAKE_BINARY_DIR}/googletest-build)
 
	# Now simply link your own targets against gtest, gmock,
	# etc. as appropriate
  		
    include_directories( ${CMAKE_BINARY_DIR}/googletest-src/include )
endif ()

include_directories(include)
#file(GLOB SOURCES "src/*.cpp")

file( GLOB SOURCES_CPP "src/*.cpp" )
file( GLOB SOURCES_HPP "src/*.h" )
file( GLOB INTERFACE_HPP "include/windows_standards/*.h" )
LIST(APPEND SOURCES ${SOURCES_HPP} ${SOURCES_CPP} ${INTERFACE_HPP})

add_library( ${target_name} STATIC ${SOURCES} )

if(BUILD_WINDOWS_STANDARDS_TESTING )
	include_directories(src)
	file( GLOB TEST_CPP RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "test/*.cpp" )
		
	CREATE_TEST_TARGETS_WINDOWS_STANDARDS( ${target_name} "${TEST_CPP}" "" )
endif()

config_compiler_and_linker_windows_standards()


