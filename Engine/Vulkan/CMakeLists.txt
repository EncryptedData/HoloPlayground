

set(ENGINE_VK_SRC src/stub.cpp)

add_library(engine_vk STATIC ${ENGINE_VK_SRC})
target_link_libraries(engine_vk PRIVATE
        engine_core
        glm)
