#include <android/log.h>
#include <napi.h>

#include "log.h"

Napi::Value Write(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  if (info.Length() < 3) {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }
  if (!info[0].IsNumber() || !info[1].IsString() || !info[2].IsString()) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }
  int prio = info[0].As<Napi::Number>().Int32Value();
  std::string tag = info[1].As<Napi::String>();
  std::string msg = info[2].As<Napi::String>();
  __android_log_write(prio, tag.c_str(), msg.c_str());
  return env.Null();
}
