//
// Created by Beany on 9/20/26.
//

#pragma once

#include <Mango/Events/Event.hpp>
#include <spdlog/fmt/bundled/format.h>

#ifdef MANGO_PLATFORM_WINDOWS
    #include <intrin.h>
    #define MANGO_DEBUGBREAK() __debugbreak()
#else
    #include <csignal>
    #define MANGO_DEBUGBREAK() raise(SIGTRAP)
#endif

template<typename T>
struct fmt::formatter<T, char, std::enable_if_t<std::is_base_of_v<Mango::Event, T>>>
	: fmt::formatter<std::string> {
	auto format(const T& e, format_context& ctx) const -> decltype(ctx.out()) {
		return fmt::formatter<std::string>::format(e.ToString(), ctx);
	}
};

#define MANGO_CORE_ASSERT(x, ...) { \
    if (!(x)) { \
        MANGO_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
        MANGO_DEBUGBREAK(); \
    } \
}

#define MANGO_ASSERT(x, ...) { \
    if (!(x)) { \
        MANGO_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
        MANGO_DEBUGBREAK(); \
    } \
}

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define BIT(x) (1 << x)