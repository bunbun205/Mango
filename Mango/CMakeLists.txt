add_library( Mango STATIC )

target_compile_features ( Mango PRIVATE cxx_std_26 )

file (GLOB_RECURSE CORE_SOURCES
	  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
	  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

target_sources ( Mango PRIVATE
				 ${CORE_SOURCES}
)

target_include_directories ( Mango PUBLIC
							 ${CMAKE_CURRENT_SOURCE_DIR}/src
							 ${CMAKE_SOURCE_DIR}/external/spdlog/include
)

target_link_libraries ( Mango PUBLIC
						glfw
						Vulkan::Vulkan
)

set_target_properties (Mango PROPERTIES
					   ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${OUTPUT_DIR}/Mango
					   LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${OUTPUT_DIR}/Mango
					   RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${OUTPUT_DIR}/Mango
)

target_compile_definitions (Mango PRIVATE
							$<$<CONFIG:Debug>:DEBUG>
							$<$<CONFIG:Release>:RELEASE>
							$<$<CONFIG:Debug>:MANGO_USE_VULKAN_VALIDATION>
)

if (MSVC)
	target_compile_options (Mango PRIVATE
							$<$<CONFIG:Debug>:/MDd>
							$<$<CONFIG:Release>:/MD>
	)
endif ()

target_compile_options(Mango PRIVATE
					   $<$<CONFIG:Debug>:-g>
					   $<$<CONFIG:Release>:-O2>
)