/* Copyright (c) 2015 Matteo Collina <hello@matteocollina.com>
 * MIT License
 */

#include <nan.h>
#include "container.h"
#include "is_defined_worker.h"
#include "create_worker.h"
#include <lxc/lxccontainer.h>

namespace lxc {

NAN_METHOD(Build) {
  NanScope();

  if (args.Length() == 0 || !args[0]->IsString())
    return NanThrowError("initializing a container requires a name");

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
  NODE_SET_PROTOTYPE_METHOD(tpl, "create", Container::Create);
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

NAN_METHOD(Container::Create) {
  NanScope();

  Container* container = node::ObjectWrap::Unwrap<Container>(args.This());

  if (args.Length() != 2 || !args[0]->IsObject() || !args[1]->IsFunction())
    return NanThrowError("isDefined() requires a an object and a callback");

  Local<Object> options = args[0].As<Object>();
  Local<Function> callback = args[1].As<Function>();

  if (!options->Has(NanNew("template")) || !options->Get(NanNew("template"))->IsString())
    return NanThrowError("missing template option for creating a container");

  if (!options->Has(NanNew("args")) || !options->Get(NanNew("args"))->IsArray())
    return NanThrowError("missing args option for creating a container");

  Local<Array> templArgs = options->Get(NanNew("args")).As<Array>();

  // validate args
  for (uint i = 0; i < templArgs->Length(); i++) {
    if (!templArgs->Get(i)->IsString()) {
      return NanThrowError("template arguments can only be strings");
    }
  }

  CreateWorker* worker = new CreateWorker(
      container,
      options->Get(NanNew("template")),
      templArgs,
      new NanCallback(callback));

  Local<Object> _this = args.This();
  worker->SaveToPersistent("container", _this);
  NanAsyncQueueWorker(worker);

  NanReturnValue(args.This());
}

} // namespace lxc
