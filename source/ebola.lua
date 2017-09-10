
-- Define this to the directory where the external libraries are located
ExternalFolder = "D:/Development/External/"

workspace "ebola"
	location "../gen"
	language "C++"
	flags { "C++11"}
	architecture "x86_64"
	
	targetdir ("../build/%{prj.name}/%{cfg.longname}")
	objdir ("../artifacts/%{prj.name}/%{cfg.longname}")
	
	configurations { "Debug", "Release" }
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		targetsuffix "_d"
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
	
-- ------------------------------------
-- Project 'core'
-- ------------------------------------
project "core"
   kind "StaticLib"
   
   includedirs { "core/public" }
   files { "core/**.h", "core/**.cpp" }
   removefiles { "core/tests/**" }
  
	  
function use_core()
	includedirs "core/public"
	links "core"
end

-- ------------------------------------
-- Project 'gfx'
-- ------------------------------------
project "gfx"
	kind "StaticLib"
	
	includedirs { "gfx/public" }
	files { "gfx/**.h", "gfx/**.cpp" }
	removefiles { "gfx/tests/**" }
	
function use_gfx()
	includedirs "gfx/public"
	links "gfx"
end

-- ------------------------------------
-- External
-- ------------------------------------
function use_vulkan()
	includedirs(ExternalFolder .. "VulkanSDK/1.0.57.0/Include")
	links(ExternalFolder .. "VulkanSDK/1.0.57.0/Lib/vulkan-1.lib")
end

function use_glfw()
	includedirs({ ExternalFolder .. "glfw-3.2.1/include" })
	links(ExternalFolder .. "glfw-3.2.1/lib-vc2015/glfw3.lib")
end

function use_glm()
	includedirs({ ExternalFolder .. "glm" })
end

-- ------------------------------------
-- Project 'editor_app'
-- ------------------------------------
project "editor_app"
	kind "ConsoleApp"
	files { "editor_app/**.h", "editor_app/**.cpp" }
	
	use_core()
	use_gfx()
	use_vulkan();
	use_glfw();
	use_glm();
	
-- ------------------------------------
-- Project 'editor_app'
-- ------------------------------------
project "test_runner"
	kind "ConsoleApp"
	files { 
		"test_runner/**.cpp", 
		"test_runner/**.h",
		"core/tests/**.cpp",
		"gfx/tests/**.cpp" 
		}
		
	includedirs({ 
		ExternalFolder .. "googletest/googletest/include/",
		})
		
		filter "configurations:Debug"
			links({
				ExternalFolder .. "googletest/googletest/msvc/2010/gtest/x64-Debug/gtestd.lib",
				ExternalFolder .. "googletest/googletest/msvc/2010/gtest/x64-Debug/gtest_maind.lib",
				})
				
		filter "configurations:Debug"
			links({
				ExternalFolder .. "googletest/googletest/msvc/2010/gtest/x64-Release/gtest.lib",
				ExternalFolder .. "googletest/googletest/msvc/2010/gtest/x64-Release/gtest_main.lib",
				})
		
	use_core();
	use_gfx();