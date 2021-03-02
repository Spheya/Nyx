#pragma once

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "Base.hpp"

namespace Nyx {

	class Logger {
	public:
		static void init();

		[[nodiscard]] inline static const std::shared_ptr<spdlog::logger>& getCoreLogger() {
			return s_coreLogger;
		}
		[[nodiscard]] inline static const std::shared_ptr<spdlog::logger>& getClientLogger() {
			return s_clientLogger;
		}

	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
	};
}

#ifdef NYX_ENABLE_LOGGER
#define NYX_LOG(...)   SPDLOG_LOGGER_TRACE(Nyx::Logger::getClientLogger(), __VA_ARGS__)
#define NYX_INFO(...)  SPDLOG_LOGGER_INFO (Nyx::Logger::getClientLogger(), __VA_ARGS__)
#define NYX_WARN(...)  SPDLOG_LOGGER_WARN (Nyx::Logger::getClientLogger(), __VA_ARGS__)
#define NYX_ERROR(...) SPDLOG_LOGGER_ERROR(Nyx::Logger::getClientLogger(), __VA_ARGS__)

#define NYX_CORE_LOG(...)   SPDLOG_LOGGER_TRACE(Nyx::Logger::getCoreLogger(), __VA_ARGS__)
#define NYX_CORE_INFO(...)  SPDLOG_LOGGER_INFO (Nyx::Logger::getCoreLogger(), __VA_ARGS__)
#define NYX_CORE_WARN(...)  SPDLOG_LOGGER_WARN (Nyx::Logger::getCoreLogger(), __VA_ARGS__)
#define NYX_CORE_ERROR(...) SPDLOG_LOGGER_ERROR(Nyx::Logger::getCoreLogger(), __VA_ARGS__)

#define NYX_GRAPHICS_WARNING(file, line, ...) Nyx::Logger::getCoreLogger()->log(spdlog::source_loc(file, line, SPDLOG_FUNCTION), spdlog::level::err, __VA_ARGS__)
#define NYX_GRAPHICS_ERROR(file, line, ...)   Nyx::Logger::getCoreLogger()->log(spdlog::source_loc(file, line, SPDLOG_FUNCTION), spdlog::level::err, __VA_ARGS__)
#else
#define NYX_LOG(...)   ((void)0)
#define NYX_INFO(...)  ((void)0)
#define NYX_WARN(...)  ((void)0)
#define NYX_ERROR(...) ((void)0)

#define NYX_CORE_LOG(...)   ((void)0)
#define NYX_CORE_INFO(...)  ((void)0)
#define NYX_CORE_WARN(...)  ((void)0)
#define NYX_CORE_ERROR(...) ((void)0)

#define NYX_GRAPHICS_WARNING(file, line, ...) ((void)0)
#define NYX_GRAPHICS_ERROR(file, line, ...)   ((void)0)
#endif