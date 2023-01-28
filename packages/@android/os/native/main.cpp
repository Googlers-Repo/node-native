#include <napi.h>

#include "system/system.h"
#include "properties/properties.h"

using namespace Napi;

Object Init(Env env, Object exports) {
  exports.Set(String::New(env, "getprop"), Function::New(env, GetProp));
  exports.Set(String::New(env, "setprop"), Function::New(env, SetProp));
  exports.Set(String::New(env, "getenv"), Function::New(env, Get));
  exports.Set(String::New(env, "setenv"), Function::New(env, Set));
  exports.Set(String::New(env, "cmd"), Function::New(env, Cmd));
  exports.Set(String::New(env, "execve"), Function::New(env, Execve));
  return exports;
}

NODE_API_MODULE(addon, Init)
