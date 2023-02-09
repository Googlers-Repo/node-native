#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <napi.h>

using namespace Napi;

class BaseProperties : public Napi::ObjectWrap<BaseProperties> {
  public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    BaseProperties(const Napi::CallbackInfo& info);
    static Napi::Value CreateNewItem(const Napi::CallbackInfo& info);

  private:
    static Napi::Value GetProp(const Napi::CallbackInfo& info);
    static Napi::Value SetProp(const Napi::CallbackInfo& info);
};

#endif