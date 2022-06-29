
set(DESKTOP_SRC src/main.cpp)

add_executable(Desktop ${DESKTOP_SRC})

target_compile_features(Desktop PRIVATE cxx_std_17)
target_link_libraries(Desktop PUBLIC
        engine_core
        engine_vk
        engine_xr)

