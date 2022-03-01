#ifndef LOGGER_HPP
#define LOGGER_HPP
#include "Singleton.hpp"
#include <spdlog/spdlog.h>

#include <memory>
namespace Tetris
{
    class Log:public Singleton<Log>
    {
        friend class Singleton<Log>;
        private:
         std::shared_ptr<spdlog::logger> m_ptrGameLogger;
        inline Log() { init(); }
        inline ~Log() {}
        public:
        
        void init();
        inline  std::shared_ptr<spdlog::logger> getGameLogger() { return m_ptrGameLogger;}
    };
}

#define TETRIS_ERROR(...) ::Tetris::Log::getInstance()->getGameLogger()->error(__VA_ARGS__)
#define TETRIS_INFO(...) ::Tetris::Log::getInstance()->getGameLogger()->info(__VA_ARGS__)
#define TETRIS_TRACE(...) ::Tetris::Log::getInstance()->getGameLogger()->trace(__VA_ARGS__)
#define TETRIS_WARN(...) ::Tetris::Log::getInstance()->getGameLogger()->warn(__VA_ARGS__)
#define TETRIS_CRITICAL(...) ::Tetris::Log::getInstance()->getGameLogger()->critical(__VA_ARGS__)
#endif