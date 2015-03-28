#include <nan.h>
#include <lxc/lxccontainer.h>
#include "container.h"

using namespace v8;

namespace lxc {

void Init(Handle<Object> exports) {
  Container::Init();
  exports->Set(NanNew("lxc"), NanNew<FunctionTemplate>(Build)->GetFunction());
}

NODE_MODULE(lxc, Init)

} //namespace lxc
