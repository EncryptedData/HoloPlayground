cmake_minimum_required(VERSION 3.15)

project(HoloPlayground)

# Normal Packages provided by the system
find_package(Vulkan REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(GameNetworkingSockets CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(OpenXR CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

add_subdirectory(Engine)

add_subdirectory(Targets)
