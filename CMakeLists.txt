cmake_minimum_required(VERSION 3.5)

project(joszva_engine)

add_executable(${PROJECT_NAME}
    src/main.cpp)

target_link_libraries(${PROJECT_NAME} "/home/joshua/Desktop/joszva_engine/vendor/graphics/lib/libjoszva_graphics.so")