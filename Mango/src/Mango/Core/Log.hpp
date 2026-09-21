//
// Created by Beany on 9/21/26.
//

#pragma once

#include "spdlog/spdlog.h"

namespace Mango {
	class Log {
	public:
		static void Init();

		inline static std::shared_ptr< spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr< spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr< spdlog::logger> s_CoreLogger;
		static std::shared_ptr< spdlog::logger> s_ClientLogger;
	};
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