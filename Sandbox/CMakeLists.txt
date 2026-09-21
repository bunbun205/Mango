add_executable ( Sandbox )

target_compile_features ( Sandbox PRIVATE cxx_std_26 )

file ( GLOB_RECURSE Sandbox_SOURCES
	   "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
	   "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

target_sources ( Sandbox PRIVATE ${Sandbox_SOURCES} )

target_include_directories ( Sandbox PRIVATE
							 ${CMAKE_CURRENT_SOURCE_DIR}/src
							 ${CMAKE_SOURCE_DIR}/Mango/src
)

target_link_libraries ( Sandbox PRIVATE Mango )

set_target_properties ( Sandbox PROPERTIES
						ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${OUTPUT_DIR}/Sandbox
						LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${OUTPUT_DIR}/Sandbox
						RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${OUTPUT_DIR}/Sandbox
)

target_compile_definitions ( Sandbox PRIVATE
							 $<$<CONFIG:Debug>:DEBUG>
							 $<$<CONFIG:Release>:RELEASE>
)

if ( MSVC )
	target_compile_options ( Sandbox PRIVATE
							 $<$<CONFIG:Debug>:/MDd>
							 $<$<CONFIG:Release>:/MD>
	)
endif ()