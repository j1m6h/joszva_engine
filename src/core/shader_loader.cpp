#include <fstream>

#include "../../inc/core/shader_loader.h"

using joszva::engine::shader_loader;

std::vector<char> shader_loader::load(const std::string& file_path)
{
    std::ifstream file(file_path, std::ios::ate | std::ios::binary);
    if (!file.is_open())
    {
        /* failed */
    }

    size_t file_size = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(file_size);
    file.seekg(0);
    file.read(buffer.data(), file_size);
    file.close();

    return buffer;
}