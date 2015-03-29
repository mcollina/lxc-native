/* Copyright (c) 2015 Matteo Collina <hello@matteocollina.com>
 * MIT License
 */

#include <nan.h>
#include "container.h"
#include "is_defined_worker.h"
#include <lxc/lxccontainer.h>

namespace lxc {

NAN_METHOD(Build) {
  NanScope();

  Local<String> name = args[0].As<String>();

  NanReturnValue(Container::NewInstance(name));
}

Persistent<FunctionTemplate> Container::container_constructor;

Container::Container (NanUtf8String* name) {
  this->lxc = lxc_container_new((char*) name, NULL);
};

Container::~Container () {
  lxc_container_put(this->lxc);
}

void Container::Init() {
  Local<FunctionTemplate> tpl = NanNew<FunctionTemplate>(Container::New);
  NanAssignPersistent(container_constructor, tpl);
  tpl->SetClassName(NanNew("Container"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  NODE_SET_PROTOTYPE_METHOD(tpl, "isDefined", Container::IsDefined);
}

NAN_METHOD(Container::New) {
  NanScope();

  NanUtf8String* name = new NanUtf8String(args[0]);

  Container* obj = new Container(name);
  obj->Wrap(args.This());

  NanReturnValue(args.This());
}

Handle<Value> Container::NewInstance (Local<String> &name) {
  NanEscapableScope();

  Local<FunctionTemplate> constructorHandle =
    NanNew<FunctionTemplate>(container_constructor);

  Handle<Value> argv[] = { name };
  Local<Object> instance = constructorHandle->GetFunction()->NewInstance(1, argv);

  return NanEscapeScope(instance);
}


NAN_METHOD(Container::IsDefined) {
  NanScope();

  Container* container = node::ObjectWrap::Unwrap<Container>(args.This());

  if (args.Length() == 0 || !args[0]->IsFunction())
    return NanThrowError("isDefined() requires a callback argument");

  Local<Function> callback = args[0].As<Function>();

  IsDefinedWorker* worker = new IsDefinedWorker(container, new NanCallback(callback));

  Local<Object> _this = args.This();
  worker->SaveToPersistent("container", _this);
  NanAsyncQueueWorker(worker);

  NanReturnValue(args.This());
}

} // namespace lxc
