/* Copyright (c) 2015 Matteo Collina <hello@matteocollina.com>
 * MIT License
 */

#include <nan.h>
#include "container.h"

using namespace v8;

namespace lxc {

void Init(Handle<Object> exports) {
  Container::Init();
  exports->Set(NanNew("lxc"), NanNew<FunctionTemplate>(Build)->GetFunction());
}

NODE_MODULE(lxc, Init)

} //namespace lxc
