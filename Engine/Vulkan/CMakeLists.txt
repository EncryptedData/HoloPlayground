

set(ENGINE_VK_SRC src/stub.cpp)

add_library(engine_vk STATIC ${ENGINE_VK_SRC})
target_link_libraries(engine_vk PUBLIC
        engine_core
        glm::glm
        Vulkan::Vulkan)

target_compile_features(engine_vk PRIVATE cxx_std_17)

target_include_directories(engine_vk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
