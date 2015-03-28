#include <nan.h>
#include "container.h"
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
  free(this->lxc);
}

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

  Local<FunctionTemplate> constructorHandle =
    NanNew<FunctionTemplate>(container_constructor);

  Handle<Value> argv[] = { name };
  Local<Object> instance = constructorHandle->GetFunction()->NewInstance(1, argv);

  return NanEscapeScope(instance);
}


} // namespace lxc
