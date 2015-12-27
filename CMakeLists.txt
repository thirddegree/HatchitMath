if(WIN32)
	cmake_minimum_required (VERSION 3.1)
else()
	cmake_minimum_required (VERSION 3.0)
endif()

project(HachitMath)

file(GLOB HACHIT_MATH_HEADERS "include/HachitMath/*.h")
file(GLOB HACHIT_MATH_SOURCE "src/*.cpp")

#C++ 11
if(UNIX)
	set(CMAKE_CXX_FLAGS "-std=c++11 -g ${CMAKE_CXX_FLAGS}")
endif(UNIX)

include_directories("include")
include_directories(SYSTEM)

source_group("Headers" FILES ${HACHIT_MATH_HEADERS})
add_library(HachitMath SHARED ${HACHIT_MATH_SOURCE} ${HACHIT_MATH_HEADERS})

#Need to link some basic libraries
if(UNIX)
	target_link_libraries(HachitMath m)
endif(UNIX)

set_property(TARGET HachitMath PROPERTY FOLDER "lib")

install(TARGETS HachitMath
		LIBRARY DESTINATION ${PROJECT_BINARY_DIR}
		ARCHIVE DESTINATION ${PROJECT_BINARY_DIR})
