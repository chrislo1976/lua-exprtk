cmake_minimum_required(VERSION 3.16)

project(lua-exprtk LANGUAGES CXX)

# compile in release  mode by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

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
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

if (CMAKE_INSTALL_PREFIX)
    install(TARGETS ${PROJECT_NAME} DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
endif(CMAKE_INSTALL_PREFIX)
