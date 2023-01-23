#include <napi.h>

#include "log/log.h"

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "__android_log_write"), Napi::Function::New(env, Write));
  return exports;
}

NODE_API_MODULE(addon, Init)