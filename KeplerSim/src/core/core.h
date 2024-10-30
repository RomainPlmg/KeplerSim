#pragma once

// Macro for debugger
#ifndef NDEBUG
#ifdef WIN32
#define CORE_DEBUGBREAK __debugbreak()
#elif UNIX
#include <csignal>
#define CORE_DEBUGBREAK raise(SIGTRAP)
#endif
#else
#define CORE_DEBUGBREAK
#endif