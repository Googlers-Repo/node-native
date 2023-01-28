#include <napi.h>

#include "log/log.h"

using namespace Napi;

Object Init(Env env, Object exports) {
  exports.Set(String::New(env, "__android_log_write"), Function::New(env, Write));
  return exports;
}

NODE_API_MODULE(addon, Init)