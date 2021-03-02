#include "nyx_pch.hpp"
#include "Logger.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Nyx {

	std::shared_ptr<spdlog::logger> Logger::s_coreLogger;
	std::shared_ptr<spdlog::logger> Logger::s_clientLogger;

	void Logger::init() {
		spdlog::set_pattern("[%T]%^ %-3!n > %-64v %$(%s:%#)");

		s_coreLogger = spdlog::stdout_color_mt("Nyx");
		s_coreLogger->set_level(spdlog::level::trace);

		s_clientLogger = spdlog::stdout_color_mt("App");
		s_clientLogger->set_level(spdlog::level::trace);

		NYX_CORE_INFO("Logger setup completed");
	}

}
