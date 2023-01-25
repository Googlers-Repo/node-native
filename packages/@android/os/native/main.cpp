#include <napi.h>

#include "system/system.h"
#include "properties/properties.h"

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "getprop"), Napi::Function::New(env, GetProp));
  exports.Set(Napi::String::New(env, "setprop"), Napi::Function::New(env, SetProp));
  exports.Set(Napi::String::New(env, "getenv"), Napi::Function::New(env, Get));
  exports.Set(Napi::String::New(env, "setenv"), Napi::Function::New(env, Set));
  exports.Set(Napi::String::New(env, "cmd"), Napi::Function::New(env, Cmd));
  exports.Set(Napi::String::New(env, "execve"), Napi::Function::New(env, Execve));
  return exports;
}

NODE_API_MODULE(addon, Init)
