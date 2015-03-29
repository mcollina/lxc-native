#include <nan.h>
#include "container.h"
#include <lxc/lxccontainer.h>

namespace lxc {

class IsDefinedWorker : public NanAsyncWorker {
  public:
    IsDefinedWorker (Container* container, NanCallback* callback);

    virtual void Execute ();
  private:
    virtual void HandleOKCallback ();
    bool result = false;
    Container* container;
};

} // namespace lxc
