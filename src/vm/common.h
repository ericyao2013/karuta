// -*- C++ -*-
#ifndef _vm_common_h_
#define _vm_common_h_

#include "karuta/karuta.h"

class Annotation;
class DumpStream;

namespace fe {
class ArrayInitializer;
class ArrayShape;
class Expr;
class Method;
class VarDecl;
class Stmt;
}  // namespace fe

namespace iroha {
class NumericWidth;
}  // namespace iroha

namespace vm {

class EnumType;
class GC;
class Insn;
class IntArray;
class Method;
class MethodFrame;
class Object;
class Profile;
class Register;
class Thread;
class Value;
class VM;

}  // namespace vm

#endif  // _vm_common_h_
