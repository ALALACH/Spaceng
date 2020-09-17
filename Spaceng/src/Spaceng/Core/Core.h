#pragma once
#include "Log.h"

//PLATFORM
#ifndef SE_PLATFORM_WIN
#define SE_PLATFORM_WIN
#endif

//BUILD
#define SE_BUILD_ID "v0.01"


// LOG
#define LOG_TRACE(...)		Spaceng::log::GetLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)		Spaceng::log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)		Spaceng::log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)		Spaceng::log::GetLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)	Spaceng::log::GetLogger()->critical(__VA_ARGS__)