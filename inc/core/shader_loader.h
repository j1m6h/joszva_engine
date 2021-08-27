#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <string>
#include <vector>

namespace joszva::engine
{
    class shader_loader
    {
    private:
        shader_loader() = default;

    public:
        static std::vector<char> load(const std::string& file_path);
    };
}
#endif