#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <napi.h>

Napi::Value GetProp(const Napi::CallbackInfo& info);
Napi::Value SetProp(const Napi::CallbackInfo& info);

#endif