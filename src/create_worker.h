/* Copyright (c) 2015 Matteo Collina <hello@matteocollina.com>
 * MIT License
 */

#include <nan.h>
#include "container.h"

namespace lxc {

class CreateWorker : public NanAsyncWorker {
  public:
    CreateWorker (
        Container* container,
        Local<Value> templ,
        Local<Array> args,
        NanCallback* callback);

    ~CreateWorker ();

    virtual void Execute ();
  private:
    bool result = false;
    char* templ;
    char** args;
    Container* container;
};

} // namespace lxc
