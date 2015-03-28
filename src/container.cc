#include <nan.h>
#include "container.h"

namespace lxc {

NAN_METHOD(Build) {
  NanScope();

  Local<String> name = args[0].As<String>();

  NanReturnValue(Container::NewInstance(name));
}

Persistent<FunctionTemplate> Container::container_constructor;

void Container::Init() {
  Local<FunctionTemplate> tpl = NanNew<FunctionTemplate>(Container::New);
  NanAssignPersistent(container_constructor, tpl);
  tpl->SetClassName(NanNew("Container"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  //NODE_SET_PROTOTYPE_METHOD(tpl, "open", Container::Open);
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

  Local<Object> instance;

  Local<FunctionTemplate> constructorHandle =
    NanNew<FunctionTemplate>(container_constructor);

  Handle<Value> argv[] = { name };
  instance = constructorHandle->GetFunction()->NewInstance(1, argv);

  return NanEscapeScope(instance);
}


} // namespace lxc
