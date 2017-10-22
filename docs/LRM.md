# Language Reference Manual

## Progmram structure

A program is comprised of top level enviroment and method environment.
Methods and various things can be declared only in top level environment.

    // * Top level environment
    // Modifying objects by declaring member variables.
    //
    def f() {
      // * Method environment
      // Object modification is not allowed (hence synthesizable).
    }

TODO: Consider non synthesizable methods.

### Methods

    @Annotation(key1="value1", key2="value2")
    def mod.f(x, y #32) (#16, #16) {
      return (0, 0)
    }

### Threads

    @ThreadEntry()
    def f() {
      print("hello?")
    }
    // The interpreter to start all threads.
    run()

### Data flow

    @DataFlowEntry()
    def f(x int) {
    }

### Object hierarchy

    var O.m1 = SubObj
    def O.f() {
      m1.h()
    }

## Types

### Width spec

    var x #32
    var x int  // Same as #32
    var x #0
    var x bool // Same as bool

### Strings

    var s string = "abc"
    s = s + "1"

### Objects

    var o object = Kernel

### Arrays

    var M.x int[32]
    var M.y #16[4] = {1,2,3,4}

## Expressions

### Names

prefix '__' is reserved for implementation

### Numerics

    123    // Decimal
    0x123  // Hexadecimal
    0b1010 // Binary

### Operators

* +, -
 * Addition and subtraction.
* *
* << >>
 * shift amount should be constant.
* :: bit concat
* [l:r] range should be constant.

## Statements

### Control

* if
 * "if" statement can take a non bool number as its condition.
* for

TODO: switch/case statement

### Declarations

As for variable declaration, please see types section.

### Import

    import "fn.n"

## External communication

### Ext I/O

    @ExtIO(output = "o")
    def L.f(b bool) {
    }

    @ExtIO(input = "i")
    def L.g() (bool) {
      return true
    }

### Ext call/stub with method interface

    @ExtEntry(name="e")
    def f(x int) (int) {
    }

    @ExtStub(name="e")
    def f(x int) (int) {
    }

#### Ext data flow

    @ExtFlowStub(name="e")
    def f(x int) (int) {
    }

#### AXI

    // @AxiMaster(addrWidth = "64") // or "32" to specify the width.
    // @AxiMaster(sramConnection = "shared") // or "exclusive" (default).
    @AxiMaster()
    var M.x int[32]
    def f() {
      x.load(mem_addr, count, array_addr)
    }

    @AxiSlave()
    var M.x int[32]

### Channel

    channel M.c1 int

## Misc features (or to be classified)

### Built in methods

* Object
    * Kernel
        * Module

* Object.clone()
* Object.dump()
* Object.setDump()
* Object.assert()
* Object.Kernel()

* Kernel.abort()
* Kernel.compile()
* Kernel.exit()
* Kernel.print()
* Kernel.writeHdl()
* Kernel.bool()
* Kernel.Object()
* Kernel.Module ()

* .$compiled_module
* .$dump_file_name

#### Memory operations

Memory object represents an address space and can be accessed by read/write method.

    Memory.read(addr)

    Memory.write(addr, data)

This assumes 32bit address/data for now.

#### Iroha related methods

* setIrohaPath(p string)
* setIROuput(p string)
* runIroha(opts string)
    * e.g. runIroha("-v -S -o x.v")

### Mailbox

    mailbox M.m1 int
    def M.f() {
      m1.put(1)
      m1.get()
    }

### Shared register

    var M.x int

### Type class

    var Numerics.Int32 object = Object.clone()
    func Numerics.Int32.Build(arg #32) (#32) {
      return arg
    }

    func Numerics.Int32.Add(lhs, rhs #32) (#32) {
      return lhs + rhs
    }

    // Type class can't be accessed from top level environment.
    func f() {
      var x #Int32
      x = Numerics.Int32.Build(1)
      print(x + x)
    }

## RTL generation

When compilation is requested by calling compile() method, the synthesizer takes a snapshot of the object and generates IR from the structure and computation.

## Format this document

 markdown LRM > LRM.html