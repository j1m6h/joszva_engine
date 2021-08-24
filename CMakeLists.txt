cmake_minimum_required(VERSION 3.5)

project(joszva_engine)

set(imgui_sources 
    vendor/imgui/imgui.cpp
    vendor/imgui/imgui_draw.cpp
    vendor/imgui/imgui_tables.cpp 
    vendor/imgui/imgui_widgets.cpp
    vendor/imgui/backends/imgui_impl_joszva.cpp
    vendor/imgui/backends/imgui_impl_vulkan.cpp)

add_executable(${PROJECT_NAME}
    src/application.cpp
    src/main.cpp
    src/renderer/vulkan/vk_descriptor_pool.cpp 
    src/renderer/vulkan/vk_device.cpp
    src/renderer/vulkan/vk_instance.cpp
    ${imgui_sources})

find_package(Vulkan)
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)

target_link_libraries(${PROJECT_NAME} "/home/joshua/Desktop/joszva_engine/vendor/joszva_graphics/lib/libjoszva_graphics.so")
target_link_libraries(${PROJECT_NAME} "/home/joshua/Desktop/joszva_engine/vendor/joszva_log/lib/libjoszva_log.so")