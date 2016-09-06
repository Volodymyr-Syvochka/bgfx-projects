add_executable( hello main.cpp vs_hello.sc fs_hello.sc )
target_link_libraries( hello glfw bgfx )

add_shader( vs_hello.sc VERTEX   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/shaders PLATFORMS dx11 glsl DX11_MODEL 5_0 GLSL 130 )
add_shader( fs_hello.sc FRAGMENT OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/shaders PLATFORMS dx11 glsl DX11_MODEL 5_0 GLSL 130 )

configure_debugging( hello WORKING_DIR ${CMAKE_CURRENT_BINARY_DIR} )
