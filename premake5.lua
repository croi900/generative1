-- premake5.lua
workspace "generative1"
    configurations { "Debug", "Release" }

project "generative1"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"

    files { "**.h", "**.hpp", "**.c", "**.cpp"}
    
    libdirs{ "lib" }
    includedirs { "include" }
    links { "raylib", "opengl32","gdi32", "winmm"}


    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"