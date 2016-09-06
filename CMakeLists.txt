# Copyright (c) 2016 Joshua Brookover

cmake_minimum_required( VERSION 3.0 )
project( bgfx-projects )

set( BGFX_BUILD_TOOLS     ON  CACHE INTERNAL "" )
set( BGFX_BUILD_EXAMPLES  OFF CACHE INTERNAL "" )
set( GLFW_BUILD_EXAMPLES  OFF CACHE INTERNAL "" )
set( GLFW_BUILD_TESTS     OFF CACHE INTERNAL "" )
set( GLFW_BUILD_DOCS      OFF CACHE INTERNAL "" )
set( GLFW_INSTALL         OFF CACHE INTERNAL "" )
add_subdirectory( deps/bgfx.cmake )
add_subdirectory( deps/glfw )

include( deps/bgfx.cmake/cmake/util/ConfigureDebugging.cmake )

add_subdirectory( hello )
