
set(ENGINE_XR_SRC src/stub.cpp)

add_library(engine_xr STATIC ${ENGINE_XR_SRC})

target_link_libraries(engine_xr PRIVATE
        glm
        openxr_loader)

target_compile_features(engine_xr PRIVATE cxx_std_17)
target_include_directories(engine_xr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)