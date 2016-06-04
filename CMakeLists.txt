cmake_minimum_required(VERSION 3.5)
project(raymarcher)

set(SOURCE_FILES main.cpp gl_3_3.cpp)

set(BIN_DIR bin)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(glm ../../usr/include/glm)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -pedantic -std=c++11 -DDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()

find_package (glm REQUIRED)
find_package (OpenGL REQUIRED)
find_package (GLFW REQUIRED)

include_directories(
        ${GLM_INCLUDE_DIR}
        ${GLFW_INCLUDE_DIR}
)

add_executable(raymarcher ${SOURCE_FILES})

target_link_libraries(
        raymarcher
        ${OPENGL_gl_LIBRARY}
        ${GLFW_LIBRARIES})


MESSAGE( WARNING "C++ build flags: " ${CMAKE_CXX_FLAGS} )
MESSAGE( WARNING "GLFW: " ${GLFW_FOUND})

install (TARGETS raymarcher RUNTIME DESTINATION ${BIN_DIR})

