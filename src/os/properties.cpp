#include <napi.h>
#include <sys/system_properties.h>
#include <internal/os/properties.h>
#include <internal/internal/properties.h>


using namespace std;
using namespace Napi;

Napi::Object BaseProperties::Init(Napi::Env env, Napi::Object exports) {
    // This method is used to hook the accessor and method callbacks
    Napi::Function func = DefineClass(env, "BaseProperties", {
        StaticMethod<&BaseProperties::GetProp>("native_get", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
        StaticMethod<&BaseProperties::GetPropBool>("native_get_boolean", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
        StaticMethod<&BaseProperties::GetPropInt>("native_get_int", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
        StaticMethod<&BaseProperties::SetProp>("native_set", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
        StaticMethod<&BaseProperties::ListProps>("native_list", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
        StaticMethod<&BaseProperties::CreateNewItem>("CreateNewItem", static_cast<napi_property_attributes>(napi_writable | napi_configurable)),
    });

    Napi::FunctionReference* constructor = new Napi::FunctionReference();

    // Create a persistent reference to the class constructor. This will allow
    // a function called on a class prototype and a function
    // called on instance of a class to be distinguished from each other.
    *constructor = Napi::Persistent(func);
    exports.Set("BaseProperties", func);

    // Store the constructor as the add-on instance data. This will allow this
    // add-on to support multiple instances of itself running on multiple worker
    // threads, as well as multiple instances of itself running in different
    // contexts on the same thread.
    //
    // By default, the value set on the environment here will be destroyed when
    // the add-on is unloaded using the `delete` operator, but it is also
    // possible to supply a custom deleter.
    env.SetInstanceData<Napi::FunctionReference>(constructor);

    return exports;
}

BaseProperties::BaseProperties(const Napi::CallbackInfo& info) :
    Napi::ObjectWrap<BaseProperties>(info) {
  Napi::Env env = info.Env();
}

Napi::Value BaseProperties::GetPropInt(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  
  if (info.Length() < 2) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  if (!info[0].IsString()) {
    Napi::TypeError::New(env, "The key should be an string").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  if (!info[1].IsNumber()) {
    Napi::TypeError::New(env, "The default value should be an number").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  string key = info[0].As<Napi::String>();
  int def = info[1].As<Napi::Number>();
  
  int value = property_get_int64(key.c_str(), def);

  return Napi::Number::New(env, value);
}

Napi::Value BaseProperties::ListProps(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  
  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  if (!info[0].IsFunction()) {
    Napi::TypeError::New(env, "The callback should be an function").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  Napi::Function cb = info[0].As<Napi::Function>();
  
  char name[PROP_NAME_MAX];
  char value[PROP_VALUE_MAX];
  const prop_info *pi;
  unsigned n;
    
  for(n = 0; (pi = __system_property_find_nth(n)); n++) {
      __system_property_read(pi, name, value);
      cb.Call(env.Global(), { Napi::String::New(env, name), Napi::String::New(env, value) });
  }
  
  return env.Null();
}

Napi::Value BaseProperties::GetProp(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  
  if (info.Length() < 2) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  if (!info[0].IsString()) {
    Napi::TypeError::New(env, "The key should be an string").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  if (!info[1].IsString()) {
    Napi::TypeError::New(env, "The default value should be an string").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  string key = info[0].As<Napi::String>();
  string def = info[1].As<Napi::String>();
  
  char value[PROP_VALUE_MAX] = {0};
  property_get(key.c_str(), value, def.c_str());
  return Napi::String::New(env, value);
}

Napi::Value BaseProperties::GetPropBool(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  
  if (info.Length() < 2) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  if (!info[0].IsString()) {
    Napi::TypeError::New(env, "The key should be an string").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  if (!info[1].IsBoolean()) {
    Napi::TypeError::New(env, "The default value should be an boolean").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  string key = info[0].As<Napi::String>();
  bool def = info[1].As<Napi::Boolean>();
  
  int8_t value = property_get_bool(key.c_str(), def);

  return Napi::Boolean::New(env, value);
}

Napi::Value BaseProperties::SetProp(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  
  if (info.Length() < 2) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  if (!info[0].IsString() || !info[1].IsString()) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  string name = info[0].As<Napi::String>();
  string value = info[1].As<Napi::String>();
  
  int rc = property_set(name.c_str(), value.c_str());
  if (rc == -1) {
    Napi::TypeError::New(env, "SystemProperties.set failed").ThrowAsJavaScriptException();
    return env.Null();
  }
  
  return env.Null();
}

// Create a new item using the constructor stored during Init.
Napi::Value BaseProperties::CreateNewItem(const Napi::CallbackInfo& info) {
  // Retrieve the instance data we stored during `Init()`. We only stored the
  // constructor there, so we retrieve it here to create a new instance of the
  // JS class the constructor represents.
  Napi::FunctionReference* constructor = info.Env().GetInstanceData<Napi::FunctionReference>();
  return constructor->New({ Napi::Number::New(info.Env(), 42) });
}