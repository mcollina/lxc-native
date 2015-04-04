/* Copyright (c) 2015 Matteo Collina <hello@matteocollina.com>
 * MIT License
 */

#include <nan.h>
#include "container.h"

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
