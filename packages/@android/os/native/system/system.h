#ifndef SYSTEM_H
#define SYSTEM_H

#include <napi.h>

Napi::Value Get(const Napi::CallbackInfo& info);
Napi::Value Set(const Napi::CallbackInfo& info);
Napi::Value Cmd(const Napi::CallbackInfo& info);
Napi::Value Execve(const Napi::CallbackInfo& info);

#endif