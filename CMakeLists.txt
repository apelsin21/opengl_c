cmake_minimum_required(VERSION 2.8)
project(opengl_c)

set(LIBRARIES
   freeimage 
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
