#include "Log.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Tetris{
    void Log::init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        m_ptrGameLogger = spdlog::stdout_color_mt("Tetris");
        m_ptrGameLogger->set_level(spdlog::level::trace);
    }
}
