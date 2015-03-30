#include <nan.h>
#include "container.h"
#include <lxc/lxccontainer.h>

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
