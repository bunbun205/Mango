//
// Created by Beany on 9/21/26.
//

#include "Log.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Mango {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("MANGO_CORE");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("MANGO_CLIENT");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
} // Mango

#define MANGO_CORE_TRACE(...) ::Mango::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MANGO_CORE_INFO(...) ::Mango::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MANGO_CORE_WARN(...) ::Mango::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MANGO_CORE_ERROR(...) ::Mango::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MANGO_CORE_CRITICAL(...) ::Mango::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define MANGO_TRACE(...) ::Mango::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MANGO_INFO(...) ::Mango::Log::GetClientLogger()->info(__VA_ARGS__)
#define MANGO_WARN(...) ::Mango::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MANGO_ERROR(...) ::Mango::Log::GetClientLogger()->error(__VA_ARGS__)
#define MANGO_CRITICAL(...) ::Mango::Log::GetClientLogger()->critical(__VA_ARGS__)