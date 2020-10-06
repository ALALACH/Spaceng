#pragma once
#include "Log.h"

//PLATFORM
#ifndef SE_PLATFORM_WIN
#define SE_PLATFORM_WIN
#endif

//BUILD
#define SE_BUILD_ID "v0.01"

//Event
#define BIND_EVENT(fn) std::bind(&##fn, this, std::placeholders::_1)

// LOG
#define LOG_TRACE(...)		Spaceng::log::GetLogger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...)		Spaceng::log::GetLogger()->debug(__VA_ARGS__)
#define LOG_INFO(...)		Spaceng::log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)		Spaceng::log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)		Spaceng::log::GetLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)	Spaceng::log::GetLogger()->critical(__VA_ARGS__)



#ifdef SE_DEBUG
       #define ENABLE_ASSERT
#endif
#ifdef ENABLE_ASSERT
       #define SE_ASSERT(condition, ...) { if(!(condition)) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#endif