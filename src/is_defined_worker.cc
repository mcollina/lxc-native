#include <nan.h>
#include "container.h"
#include "is_defined_worker.h"
#include <lxc/lxccontainer.h>

namespace lxc {

IsDefinedWorker::IsDefinedWorker (
  Container* container,
  NanCallback* callback
) : NanAsyncWorker(callback) {
  this->container = container;
};

void IsDefinedWorker::Execute () {
  if (container->lxc->is_defined(container->lxc)) {
    result = true;
  }
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
