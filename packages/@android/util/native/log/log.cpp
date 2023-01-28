#include <android/log.h>
#include <napi.h>

#include "log.h"

using namespace std;
using namespace Napi;

Value Write(const CallbackInfo& info) {
  Env env = info.Env();
  
  if (info.Length() < 3) {
    TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  if (!info[0].IsNumber() || !info[1].IsString() || !info[2].IsString()) {
    TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  int prio = info[0].As<Number>().Int32Value();
  string tag = info[1].As<String>();
  string msg = info[2].As<String>();
  
  __android_log_write(prio, tag.c_str(), msg.c_str());
  
  return env.Null();
}
