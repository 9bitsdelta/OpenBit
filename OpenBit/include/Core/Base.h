#pragma once

#include <memory>

#ifdef BIT_DEBUG
	#if defined(BIT_PLATFORM_WINDOWS)
		#define BIT_DEBUGBREAK() __debugbreak()
	#elif defined(BIT_PLATFORM_LINUX)
		#include <signal.h>
		#define BIT_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define BIT_ENABLE_ASSERTS
#else
	#define BIT_DEBUGBREAK()
#endif

#ifdef BIT_ENABLE_ASSERTS
	#define BIT_ASSERT(x, ...) { if(!(x)) { BIT_ERROR("Assertion Failed: {0}", __VA_ARGS__); BIT_DEBUGBREAK(); } }
	#define BIT_CORE_ASSERT(x, ...) { if(!(x)) { BIT_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); BIT_DEBUGBREAK(); } }
#else
	#define BIT_ASSERT(x, ...)
	#define BIT_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BIT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Bit {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}

#include "Core/Log.h"
