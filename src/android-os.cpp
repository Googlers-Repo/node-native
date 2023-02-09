#include <napi.h>
#include <internal/os/system.h>
#include <internal/os/properties.h>

using namespace Napi;

Object Init(Env env, Object exports) {
  BaseProperties::Init(env, exports);
  BaseSystem::Init(env, exports);
  return exports;
}

NODE_API_MODULE(addon, Init)
