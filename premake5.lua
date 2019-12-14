include "libs/PrLib"

workspace "SphereConnection"
    location "build"
    configurations { "Debug", "Release" }
    startproject "SphereConnection"

architecture "x86_64"

externalproject "prlib"
	location "libs/PrLib/build" 
    kind "StaticLib"
    language "C++"

project "SphereConnection"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/"
    systemversion "latest"
    flags { "MultiProcessorCompile", "NoPCH" }

    -- Src
    files { "main.cpp" }

    -- prlib
    -- setup command
    -- git submodule add https://github.com/Ushio/prlib libs/prlib
    -- premake5 vs2017
    dependson { "prlib" }
    includedirs { "libs/prlib/src" }
    libdirs { "libs/prlib/bin" }
    filter {"Debug"}
        links { "prlib_d" }
    filter {"Release"}
        links { "prlib" }
    filter{}

    symbols "On"

    filter {"Debug"}
        runtime "Debug"
        targetname ("SphereConnection_Debug")
        optimize "Off"
    filter {"Release"}
        runtime "Release"
        targetname ("SphereConnection")
        optimize "Full"
    filter{}
