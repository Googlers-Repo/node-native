#include <napi.h>
#include <sys/system_properties.h>

#include "properties.h"

using namespace std;
using namespace Napi;

Value GetProp(const CallbackInfo& info) {
  Env env = info.Env();
  
  if (info.Length() < 2) {
    TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  if (!info[0].IsString()) {
    TypeError::New(env, "The key should be an string").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  if (!info[1].IsString()) {
    TypeError::New(env, "The default value should be an string").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  string name = info[0].As<String>();
  string def = info[1].As<String>();
  
  char value[PROP_VALUE_MAX] = {0};
  __system_property_get(name.c_str(), value);
  
  if (strlen (value) == 0) {
    return String::New(env, def);
  } else {
    return String::New(env, value);
  }
}

Value SetProp(const CallbackInfo& info) {
  Env env = info.Env();
  
  if (info.Length() < 2) {
    TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  if (!info[0].IsString() || !info[1].IsString()) {
    TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  string name = info[0].As<String>();
  string value = info[1].As<String>();
  
  int rc = __system_property_set(name.c_str(), value.c_str());
  if (rc == -1) {
    TypeError::New(env, "setprop failed").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  return env.Null();
}
