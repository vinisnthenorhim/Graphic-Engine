cmake_minimum_required(VERSION 3.20)

project(BrokenWorld LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_subdirectory(include/SDL3 EXCLUDE_FROM_ALL)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" )
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "src/*.h"   )


add_library( glad STATIC include/OpenGL/src/gl.c )

target_include_directories(glad PUBLIC include/OpenGL/include)



add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/script/game)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/script/renderer)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/script/window)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/OpenGL/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)


target_link_libraries(${PROJECT_NAME}
    PRIVATE
    SDL3::SDL3
    glad
    opengl32
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<TARGET_FILE:SDL3::SDL3>"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    VERBATIM
)