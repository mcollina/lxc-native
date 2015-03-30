#include <nan.h>
#include "container.h"
#include "create_worker.h"
#include <lxc/lxccontainer.h>
#include <string.h>

namespace lxc {

CreateWorker::CreateWorker (
  Container* container,
  Local<Value> templ,
  Local<Array> args,
  NanCallback* callback
) : NanAsyncWorker(callback) {
  this->container = container;
  this->templ = strdup((char*) *NanUtf8String(templ));

  int length = args->Length();
  this->args = (char**) calloc(length + 1, sizeof(char*));

  // pre init the list
  for (int i = 0; i < length + 1; i++) {
    this->args[i] = NULL;
  }

  for (int i = 0; i < length; i++) {
    Local<String> v8str = args->Get(i).As<String>();
    this->args[i] = strdup((char*) *NanUtf8String(v8str));
  }
};

CreateWorker::~CreateWorker () {
  int i = 0;
  while (args[i] != NULL) {
    delete args[i];
    i++;
  }

  delete templ;
  delete args;
}

void CreateWorker::Execute () {
  lxc_container* lxc = this->container->lxc;
  if (!lxc->create(lxc, this->templ, NULL, NULL, LXC_CREATE_QUIET,
        this->args)) {
    this->SetErrorMessage("unable to create the container");
  }
}

} // namespace lxc
