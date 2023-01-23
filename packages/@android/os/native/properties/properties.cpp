#include <napi.h>
#include <sys/system_properties.h>

#include "properties.h"

Napi::Value GetProp(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }
  if (!info[0].IsString()) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  std::string name = info[0].As<Napi::String>();
  
  char value[PROP_VALUE_MAX] = {0};
  __system_property_get(name.c_str(), value);
  
  return Napi::String::New(env, value);
}

Napi::Value SetProp(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  if (info.Length() < 2) {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }
  if (!info[0].IsString() || !info[1].IsString()) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  std::string name = info[0].As<Napi::String>();
  std::string value = info[1].As<Napi::String>();
  
  
  int rc = __system_property_set(name.c_str(), value.c_str());
  if (rc == -1) {
    Napi::TypeError::New(env, "setprop failed").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  return env.Null();
}
