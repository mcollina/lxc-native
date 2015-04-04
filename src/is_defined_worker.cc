/* Copyright (c) 2015 Matteo Collina <hello@matteocollina.com>
 * MIT License
 */

#include <nan.h>
#include <lxc/lxccontainer.h>
#include "container.h"
#include "is_defined_worker.h"

namespace lxc {

IsDefinedWorker::IsDefinedWorker (
  Container* container,
  NanCallback* callback
) : NanAsyncWorker(callback) {
  this->container = container;
};

void IsDefinedWorker::Execute () {
  lxc_container_get(container->lxc);
  if (container->lxc->is_defined(container->lxc)) {
    result = true;
  }
  lxc_container_put(container->lxc);
}

void IsDefinedWorker::HandleOKCallback () {
  Local<Value> returnValue = NanNew<Boolean>(result);

  Local<Value> argv[] = {
    NanNull(),
    returnValue
  };

  callback->Call(2, argv);
}

} // namespace lxc
