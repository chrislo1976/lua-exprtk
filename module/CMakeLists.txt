cmake_minimum_required(VERSION 3.16)

project(lua-exprtk LANGUAGES CXX)

find_package(Lua REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


SET(SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lua_exprtk.cpp
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${LUA_INCLUDE_DIR}
)

add_library(${PROJECT_NAME} MODULE ${SRCS})
target_link_libraries(${PROJECT_NAME} ${LUA_LIBRARIES} sol exprtk)
