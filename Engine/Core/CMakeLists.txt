
set(ENGINE_CORE_SRC src/stub.cpp)

add_library(engine_core STATIC ${ENGINE_CORE_SRC})
target_link_libraries(engine_core PUBLIC
        EnTT
        glm)

target_compile_features(engine_core PRIVATE cxx_std_17)

target_include_directories(engine_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
