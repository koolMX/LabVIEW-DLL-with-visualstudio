#pragma once
#include "pch.h"
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include "comm/datalayer/datalayer.h"
#include "comm/datalayer/datalayer_system.h"
#include "shared_lib.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef BUILD_FOR_X64
#ifdef _WIN64
#define WRAP_FUN __declspec(dllexport)
#endif
#else
#ifdef _WIN64
#define WRAP_FUN __declspec(dllimport)
#endif
#endif

SharedLib Toast("192.168.1.1", "boschrexroth", "boschrexroth", 443);
__declspec(dllexport) const char* Connectstring(const char* ip, const char* user, const char* password, int myPort);
__declspec(dllexport) const char* read(const char* str, const char* corepipe);
__declspec(dllexport) void Looseclient();


}
#ifdef __cplusplus
#endif