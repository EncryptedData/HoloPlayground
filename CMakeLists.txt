cmake_minimum_required(VERSION 3.15)

project(HoloPlayground)

# Include CMake Package Manager
include(CMake/CPM.cmake)

# Include the needed externals
CPMAddPackage("gh:/g-truc/glm#0.9.9.8")
CPMAddPackage("gh:/skypjack/entt#v3.10.1")
CPMAddPackage("gh:/KhronosGroup/OpenXR-SDK#release-1.0.24")
#CPMAddPackage("gh:/ValveSoftware/GameNetworkingSockets#v1.4.1")

add_subdirectory(Engine)

add_subdirectory(Targets)
