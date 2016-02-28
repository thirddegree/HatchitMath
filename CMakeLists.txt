cmake_minimum_required (VERSION 2.8.7)

set(BUILD_TEST FALSE CACHE BOOL "Build the google test project")

project(HatchitMath)

file(GLOB HATCHIT_MATH_HEADERS "include/*.h")
file(GLOB HATCHIT_MATH_INLINE "source/inline/*.inl")
file(GLOB HATCHIT_MATH_SOURCE "source/*.cpp")

# Compiler flag
include (CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
    if(CMAKE_BUILD_TYPE MATCHES DEBUG)
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -g -msse")
    else()
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -msse")
    endif()
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()


include_directories("include" "source/inline")
include_directories(SYSTEM)

source_group("Headers" FILES ${HATCHIT_MATH_HEADERS})
add_library(HatchitMath SHARED ${HATCHIT_MATH_SOURCE} ${HATCHIT_MATH_INLINE} ${HATCHIT_MATH_HEADERS})

#Need to link some basic libraries
#if(UNIX)
#	target_link_libraries(HatchitMath m)
#endif(UNIX)

#set_property(TARGET HatchitMath PROPERTY FOLDER "lib")
#target_compile_definitions(HatchitMath PRIVATE HT_NONCLIENT_BUILD)

#install(TARGETS HatchitMath
#		LIBRARY DESTINATION ${PROJECT_BINARY_DIR}
#		ARCHIVE DESTINATION ${PROJECT_BINARY_DIR})

# Test project
if(BUILD_TEST)
	project(HatchitMathTest)

	find_package(GTest REQUIRED)
	find_package(Threads REQUIRED)

	file(GLOB TEST_SOURCE "test/*.cpp")

	include_directories(${GTEST_INCLUDE_DIRS})
	include_directories("include")

	add_executable(test_bin ${TEST_SOURCE})
	target_link_libraries(test_bin ${GTEST_BOTH_LIBRARIES})
	target_link_libraries(test_bin ${CMAKE_THREAD_LIBS_INIT})
	#target_link_libraries(test_bin HatchitMath)

	enable_testing()
	add_test(A test_bin)
endif(BUILD_TEST)
