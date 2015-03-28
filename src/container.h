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
};

} // namespace lxc
