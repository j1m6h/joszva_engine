#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <memory>

namespace joszva::graphics
{
    enum class log_level
    {
        TRACE,
        WARNING,
        ERROR,
        FATAL
    };

    class logger
    {
    public:
        static logger* instance();

        void trace(const std::string& txt);
        void warning(const std::string& txt);
        void error(const std::string& txt);
        void fatal(const std::string& txt);

    private:
        void log(log_level level, const std::string& txt);

        std::ofstream output_file;
        std::ifstream input_file;
    };

    /* uses these macros when logging, simpler and more versatile */
    #define JOSZVA_TRACE(txt) logger::instance()->trace(txt);
    #define JOSZVA_WARNING(txt) logger::instance()->warning(txt);
    #define JOSZVA_ERROR(txt) logger::instance()->error(txt);
    #define JOSZVA_FATAL(txt) logger::instance()->fatal(txt);
}
#endif