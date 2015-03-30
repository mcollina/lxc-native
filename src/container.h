
/* Copyright (c) 2015 Matteo Collina <hello@matteocollina.com>
 * MIT License
 */
#ifndef LN_CONTAINER_H
#define LN_CONTAINER_H

#include <nan.h>
#include <lxc/lxccontainer.h>

using namespace v8;

namespace lxc {

NAN_METHOD(Build);

class Container : public node::ObjectWrap {
  public:
    static void Init ();
    static Handle<Value> NewInstance (Local<String> &name);

    Container (NanUtf8String* name);
    ~Container ();

    struct lxc_container *lxc;
  private:
    static Persistent<FunctionTemplate> container_constructor;
    static NAN_METHOD(New);
    static NAN_METHOD(IsDefined);
    static NAN_METHOD(Create);
};

} // namespace lxc

#endif
