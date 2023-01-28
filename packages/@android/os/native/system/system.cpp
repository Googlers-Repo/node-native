#include <napi.h>
#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/stat.h> 
#include <conio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

#include "system.h"

using namespace std;
using namespace Napi;

Value Get(const CallbackInfo& info) {
  Env env = info.Env();
  
  if (info.Length() < 1) {
    TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }
  
  if (!info[0].IsString()) {
    TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  std::string name = info[0].As<String>();
  
  return String::New(env, getenv(name.c_str()));
}

Value Set(const CallbackInfo& info) {
  Env env = info.Env();
  
  if (info.Length() < 3) {
    TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  if (!info[0].IsString() || !info[1].IsString() || !info[2].IsNumber()) {
    TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  string name = info[0].As<String>();
  string value = info[1].As<String>();
  int overrid = info[2].As<Number>();
  
  setenv(name.c_str(), value.c_str(), overrid);
  
  return String::New(env, getenv(name.c_str()));
}

Value Cmd(const CallbackInfo& info) {
  Env env = info.Env();
  
  if (info.Length() < 1) {
    TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }
  
  if (!info[0].IsString()) {
    TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  string cmd = info[0].As<String>();
  
  array<char, 128> buffer;
  string result;
  unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
  
  if (!pipe) {
    TypeError::New(env, "popen() failed!").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }
  
  return String::New(env, result);
}
