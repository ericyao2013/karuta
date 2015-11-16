#include "vm/native_methods.h"

#include <stdlib.h>

#include "pool.h"
#include "messages.h"
#include "synth/synth.h"
#include "vm/channel.h"
#include "vm/method.h"
#include "vm/object.h"
#include "vm/string_wrapper.h"
#include "vm/thread.h"
#include "vm/thread_wrapper.h"
#include "vm/value.h"
#include "vm/vm.h"

namespace vm {

void NativeMethods::Assert(Thread *thr, Object *obj,
			   const vector<Value> &args) {
  CHECK(args.size() == 1) << "Assert got " << args.size() << "args.";
  const Value &arg = args[0];
  VM *vm = thr->GetVM();
  CHECK(arg.type_ == Value::ENUM_ITEM) << "Assert argument is not an enum item";
  CHECK(arg.enum_val_.enum_type == vm->bool_type_.get());
  if (arg.enum_val_.val == 0) {
    cout << "ASSERTION FAILURE\n";
  }
}

void NativeMethods::Clone(Thread *thr, Object *obj,
			  const vector<Value> &args) {
  Value value;
  value.type_ = Value::OBJECT;
  value.object_ = obj->Clone(thr->GetVM());
  SetReturnValue(thr, value);
}

void NativeMethods::Dump(Thread *thr, Object *obj,
			 const vector<Value> &args) {
  obj->Dump();
}

void NativeMethods::Exit(Thread *thr, Object *obj,
			 const vector<Value> &args) {
  thr->Exit();
}

void NativeMethods::Print(Thread *thr, Object *obj,
			  const vector<Value> &args) {
  cout << "print: ";
  for (size_t i = 0; i < args.size(); ++i) {
    args[i].Dump(cout);
    cout << "\n";
  }
}


void NativeMethods::Run(Thread *thr, Object *obj,
			const vector<Value> &args) {
  ThreadWrapper::Run(thr->GetVM(), obj);
}

void NativeMethods::SetDump(Thread *thr, Object *obj,
			    const vector<Value> &args) {
  if (args.size() == 1 && args[0].type_ == Value::OBJECT &&
      StringWrapper::IsString(args[0].object_)) {
    const string &fn = StringWrapper::String(args[0].object_);
    Value value;
    value.object_ = StringWrapper::NewStringWrapper(thr->GetVM(), fn);
    value.type_ = Value::OBJECT;
    obj->InstallValue(sym_lookup("$dump_file_name"), value);
  }
}

void NativeMethods::Compile(Thread *thr, Object *obj,
			    const vector<Value> &args) {
  string phase;
  if (args.size() == 1) {
    CHECK(StringWrapper::IsString(args[0].object_));
    phase = StringWrapper::String(args[0].object_);
  }
  if (!synth::Synth::Synthesize(thr->GetVM(), phase, obj)) {
    thr->UserError("Compile failed");
  }
}

void NativeMethods::WidthOf(Thread *thr, Object *obj,
			    const vector<Value> &args) {
  if (args.size() != 1 || args[0].type_ != Value::NUM) {
    std::unique_ptr<Message> m(Message::CreateMessage(Message::USER));
    m->os() << "Invalid argument to widthof()";
    return;
  }
  Value value;
  value.type_ = Value::NUM;
  numeric::Numeric::MakeConst(numeric::Width::GetWidth(args[0].num_.type),
			      0, &value.num_);
  SetReturnValue(thr, value);
}

void NativeMethods::WriteHdl(Thread *thr, Object *obj,
			     const vector<Value> &args) {
  CHECK(args.size() == 1);
  const Value& arg = args[0];
  CHECK(StringWrapper::IsString(arg.object_));
  synth::Synth::WriteHdl(StringWrapper::String(arg.object_), obj);
}

void NativeMethods::IsMain(Thread *thr, Object *obj,
			   const vector<Value> &args) {
  Value value;
  value.type_ = Value::ENUM_ITEM;
  value.enum_val_.enum_type = thr->GetVM()->bool_type_.get();
  value.enum_val_.val = thr->IsRootThread() ? 1 : 0;
  SetReturnValue(thr, value);
}

void NativeMethods::SetReturnValue(Thread *thr, const Value &value) {
  thr->SetReturnValueFromNativeMethod(value);
}

void Method::InstallNativeRootObjectMethods(VM *vm, Object *obj) {
  vector<RegisterType> rets;
  rets.push_back(ObjectType());
  InstallNativeMethod(vm, obj, "clone", &NativeMethods::Clone, rets);
  rets.clear();
  InstallNativeMethod(vm, obj, "dump", &NativeMethods::Dump, rets);
  InstallNativeMethod(vm, obj, "run", &NativeMethods::Run, rets);
}

void Method::InstallNativeKernelObjectMethods(VM *vm, Object *obj) {
  vector<RegisterType> rets;
  InstallNativeMethodWithAltImpl(vm, obj, "assert", &NativeMethods::Assert, rets, "__assert");
  InstallNativeMethodWithAltImpl(vm, obj, "print", &NativeMethods::Print, rets, "__print");
  InstallNativeMethod(vm, obj, "compile", &NativeMethods::Compile, rets);
  InstallNativeMethod(vm, obj, "__compile", &NativeMethods::Compile, rets);
  InstallNativeMethod(vm, obj, "exit", &NativeMethods::Exit, rets);
  InstallNativeMethod(vm, obj, "setDump", &NativeMethods::SetDump, rets);
  InstallNativeMethod(vm, obj, "widthof", &NativeMethods::WidthOf, rets);
  InstallNativeMethod(vm, obj, "writeHdl", &NativeMethods::WriteHdl, rets);
  // Depreacte this after 0.1.8.
  InstallNativeMethod(vm, obj, "write_hdl", &NativeMethods::WriteHdl, rets);
}

void Method::InstallNativeMethodWithAltImpl(VM *vm, Object *obj, const char *name,
					    method_func func, const vector<RegisterType> &types,
					    const char *alt) {
  Method *method = vm->NewMethod(false /* not toplevel */);
  method->method_fn_ = func;
  method->alt_impl_ = alt;
  method->return_types_ = types;
  Value value;
  value.type_ = Value::METHOD;
  value.method_ = method;
  obj->InstallValue(sym_lookup(name), value);
}

void Method::InstallNativeMethod(VM *vm, Object *obj, const char *name,
				 method_func func, const vector<RegisterType> &types) {
  InstallNativeMethodWithAltImpl(vm, obj, name, func, types, NULL);
}

void Method::InstallEnvNativeMethods(VM *vm, Object *env) {
  vector<RegisterType> rets;
  rets.push_back(BoolType(vm));
  InstallNativeMethod(vm, env, "isMain", &NativeMethods::IsMain, rets);
}

RegisterType Method::ObjectType() {
  return RegisterType(Value::OBJECT, NULL, NULL, false);
}

RegisterType Method::BoolType(VM *vm) {
  return RegisterType(Value::ENUM_ITEM, vm->bool_type_.get(), NULL, false);
}

RegisterType Method::IntType(int w) {
  return RegisterType(Value::NUM, NULL,
		      numeric::Width::MakeInt(false, w, 0), false);
}

}  // namespace vm
