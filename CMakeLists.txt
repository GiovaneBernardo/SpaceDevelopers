cmake_minimum_required(VERSION 3.25)

if(POLICY CMP0091) # Force thidparty libraries to use static MSVC
    #cmake_policy(SET CMP0091 NEW)
endif()

project(GameProject)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    #set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>" CACHE INTERNAL "")
    add_compile_options(/MP)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX- /W4 /O2")
    add_compile_options(/bigobj)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "Embedded")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

set(BUILD_STATIC_LIB ON)
set(TARGET_BUILD_PLATFORM "windows")
set(PLATFORM "Windows")
add_compile_definitions(_DEBUG)
add_definitions(-D_DEBUG)
add_definitions(-D_ITERATOR_DEBUG_LEVEL=2)
add_definitions(-DLIBTYPE=STATIC)
add_compile_definitions(IMGUI_DEFINE_MATH_OPERATORS)
option(MSVC_CRT_STATIC   "Link primesieve.lib with /MT instead of the default /MD" OFF)
set(PLATFORM_CMAKELISTS "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt")
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Ob0 /Od /RTC1")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4244")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /C2220")
set(PLAZA_ITERATOR_LEVEL 2)
#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(ENGINE_SOURCE_DIR "C:/PlazaEngine")
#set(ENGINE_SOURCE_DIR "C:/Users/Giovane/Desktop/Workspace/PlazaEngine")


file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Assets/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/Assets/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/Scripts/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/Scripts/*.h")
add_library(GameLib SHARED ${GAME_SOURCES})
target_compile_definitions(GameLib PRIVATE ENGINE_IMPORT)
#target_compile_definitions(GameLib PUBLIC MONO_DLL_IMPORT)
#target_precompile_headers(GameLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Assets/Scripts/pch.h")

target_compile_definitions(GameLib PUBLIC  PX_PHYSX_STATIC_LIB)
target_compile_definitions(GameLib PUBLIC  EDITOR_MODE)
target_compile_definitions(GameLib PUBLIC  COMPILING_GAME_DLL)
target_link_options(GameLib PUBLIC "/INCREMENTAL /PDBALTPATH:$<TARGET_PDB_FILE_NAME:GameLib>")

link_directories("${CMAKE_SOURCE_DIR}/bin")

set_property(TARGET GameLib PROPERTY CXX_STANDARD 20)

#set(CMAKE_OBJECT_PATH_MAX 2048)
#set(CMAKE_OBJECT_PATH_HASH true)

#include(ExternalProject)
#
#ExternalProject_Add(PlazaEngineCoreProject
#    SOURCE_DIR "C:/Users/Giovane/Desktop/Workspace/PlazaEngine"
#    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX="C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/install/"
#    BUILD_ALWAYS OFF
#)
#
## Create an imported target for PlazaEngineCore
#add_library(PlazaEngineCore STATIC IMPORTED)
#set_target_properties(PlazaEngineCore PROPERTIES
#    IMPORTED_LOCATION  "C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/lib/PlazaEngineCore.lib" # Replace with the actual output file
#    INTERFACE_INCLUDE_DIRECTORIES "C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/;C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/Engine;C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/Editor;C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/ThirdParty;C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/ThirdParty/AL/include/AL;C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/ThirdParty/cereal;C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/ThirdParty/DirectXTex/DirectXTex;C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/ThirdParty/filesystem;C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/ThirdParty/FileWatcher;C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/ThirdParty/glad;C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/ThirdParty/GLFW;C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/ThirdParty/glm;C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/ThirdParty/imgui;C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/ThirdParty/Json;C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/ThirdParty/KHR;C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/ThirdParty/minimp3;C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/ThirdParty/mono/include;C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/ThirdParty/PhysX/physx/include;C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/ThirdParty/pfr/include;C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/ThirdParty/premake;C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/ThirdParty/stb;C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/ThirdParty/spdlog/include;C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/ThirdParty/tinyobjloader;C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/ThirdParty/uuid_v4;C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/ThirdParty/vswhere;C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/ThirdParty/vulkan/vulkan;C:/Users/Giovane/Desktop/Workspace/PlazaEngine/out/build/x64-Debug/install/include/PlazaEngineCore/ThirdParty/vulkan/"
#)

## Ensure GameLib depends on the ExternalProject_Add build process
#add_dependencies(GameLib PlazaEngineCore)

include(FetchContent)
FetchContent_Declare(
  PlazaEngineCoreLibs
  SOURCE_DIR "${ENGINE_SOURCE_DIR}/"
)

FetchContent_MakeAvailable(PlazaEngineCoreLibs)

#FetchContent_Declare(
#  PlazaEngineCore
#  SOURCE_DIR "${ENGINE_SOURCE_DIR}/"
#)
#
#FetchContent_MakeAvailable(PlazaEngineCore)

# Link GameLib with the imported PlazaEngineCore target
#target_link_libraries(GameLib PRIVATE PlazaEngineCore)
set(MONO_PATH "${ENGINE_SOURCE_DIR}/ThirdParty/mono/lib/${CMAKE_BUILD_TYPE}")
include(FindVulkan)
if(NOT VULKAN_FOUND)
    message(FATAL_ERROR "Vulkan SDK not installed.")
endif()
find_package(Vulkan REQUIRED)
 
set(PHYSX_LIBS
    "PhysX_static.lib"
    "PhysXExtensions_static.lib"
    "PhysXCooking_static.lib"
    "PhysXCommon_static.lib"
    "PhysXFoundation_static.lib"
    "PhysXPvdSDK_static.lib"
    "PhysXVehicle_static.lib"
    "PhysXVehicle2_static.lib"
)
#target_sources(GameLib public PlazaEngineCoreLibs)
target_link_libraries(GameLib PUBLIC PlazaEngineCore PlazaEngineCoreLibs) 




target_include_directories(GameLib PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    #"${ENGINE_SOURCE_DIR}/"
    #"${ENGINE_SOURCE_DIR}/ThirdParty/AL/include/AL"
    #"${ENGINE_SOURCE_DIR}/ThirdParty/cereal/"
    #"${ENGINE_SOURCE_DIR}/ThirdParty/DirectXTex/DirectXTex/"
    #"${ENGINE_SOURCE_DIR}/ThirdParty/filesystem/"
    #"${ENGINE_SOURCE_DIR}/ThirdParty/FileWathcer/"
    #"${ENGINE_SOURCE_DIR}/ThirdParty/glad/"
    #"${ENGINE_SOURCE_DIR}/ThirdParty/GLFW/"
    #"${ENGINE_SOURCE_DIR}/ThirdParty/glm/"
    #"${ENGINE_SOURCE_DIR}/ThirdParty/Json/"
    #"${ENGINE_SOURCE_DIR}/ThirdParty/KHR/"
    #"${ENGINE_SOURCE_DIR}/ThirdParty/minimp3/"
    #"${ENGINE_SOURCE_DIR}/ThirdParty/mono/include/"
    #"${ENGINE_SOURCE_DIR}/ThirdParty/PhysX/physx/include/"
    #"${ENGINE_SOURCE_DIR}/ThirdParty/premake/"
    #"${ENGINE_SOURCE_DIR}/ThirdParty/stb/"
    #"${ENGINE_SOURCE_DIR}/ThirdParty/spdlog/include/"
    #"${ENGINE_SOURCE_DIR}/ThirdParty/tinyobjloader/"
    #"${ENGINE_SOURCE_DIR}/ThirdParty/ufbx/"
    #"${ENGINE_SOURCE_DIR}/ThirdParty/uuid_v4/"
    #"${ENGINE_SOURCE_DIR}/ThirdParty/vswhere/"
    #"${ENGINE_SOURCE_DIR}/ThirdParty/vulkan/"
    #"${ENGINE_SOURCE_DIR}/ThirdParty/vulkan/vulkan/"
)

set(OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
add_custom_command(TARGET GameLib POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${OUTPUT_DIRECTORY}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<TARGET_FILE:GameLib>"
    "$<TARGET_PDB_FILE:GameLib>"
    "${OUTPUT_DIRECTORY}"
)

add_custom_target(CopyGameLib ALL DEPENDS GameLib)
add_custom_target(DeleteGamePDB ALL DEPENDS GameLib)

add_custom_command(TARGET GameLib
                   PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/bin/PlazaEngineCore.lib" "${CMAKE_CURRENT_BINARY_DIR}/"
                   COMMENT "Copying PlazaEngineCore.lib to game project folder")