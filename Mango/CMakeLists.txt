add_library( Mango STATIC )

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

if(WIN32)
	target_include_directories( Mango PUBLIC
			${CMAKE_SOURCE_DIR}/external/glm
	)
endif ()

target_precompile_headers ( Mango PUBLIC
							${CMAKE_CURRENT_SOURCE_DIR}/src/mangopch.hpp
)

if( WIN32 )
	target_link_libraries( Mango PUBLIC
							d3d12
							dxgi
							d3dcompiler
	)
else ()
	target_link_libraries( Mango PUBLIC
			glfw
			Vulkan::Vulkan
	)
endif ()

target_compile_definitions ( Mango PUBLIC
			$<$<PLATFORM_ID:Windows>:MANGO_PLATFORM_WINDOWS>
			$<$<PLATFORM_ID:Windows>:MANGO_RENDERER_DX12>
			$<$<NOT:$<PLATFORM_ID:Windows>>:MANGO_PLATFORM_LINUX>
			$<$<NOT:$<PLATFORM_ID:Windows>>:MANGO_RENDERER_VULKAN>
)

set_target_properties (Mango PROPERTIES
					   ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${OUTPUT_DIR}/Mango
					   LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${OUTPUT_DIR}/Mango
					   RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${OUTPUT_DIR}/Mango
)

target_compile_definitions(Mango PRIVATE
						   $<$<CONFIG:Debug>:DEBUG>
						   $<$<CONFIG:Release>:RELEASE>
						   $<$<CONFIG:Debug>:MANGO_USE_VULKAN_VALIDATION>
						   $<$<PLATFORM_ID:Windows>:NOMINMAX>
						   $<$<PLATFORM_ID:Windows>:WIN32_LEAN_AND_MEAN>
)

if (MSVC)
	target_compile_options (Mango PRIVATE
							/utf-8
							$<$<CONFIG:Debug>:/MDd>
							$<$<CONFIG:Release>:/MD>
	)
endif ()