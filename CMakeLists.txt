cmake_minimum_required( VERSION 3.24 )

project( MangoEngine LANGUAGES CXX )

if(CMAKE_GENERATOR MATCHES "Visual Studio")
	set(CMAKE_GENERATOR_PLATFORM x64)
endif()

set ( CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE )
set ( OUTPUT_DIR "${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE}" )

set_property ( GLOBAL PROPERTY USE_FOLDERS ON )

find_package ( Vulkan REQUIRED )

add_subdirectory ( Mango )
add_subdirectory ( Sandbox )