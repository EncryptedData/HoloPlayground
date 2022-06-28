
set(ENGINE_CORE_SRC src/stub.cpp)

add_library(engine_core STATIC ${ENGINE_CORE_SRC})
target_link_libraries(engine_core PRIVATE
        EnTT
        glm)
