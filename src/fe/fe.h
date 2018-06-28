// -*- C++ -*-
//
#ifndef _fe_fe_h_
#define _fe_fe_h_

#include "fe/common.h"

namespace fe {

class FE {
 public:
  FE(bool dbg_parser, bool dbg_scanner, bool dbg_bytecode);

  void Run(bool vanilla, const vector<string> &files);

  static vm::Method *CompileFile(const string &file, bool dbg_parser,
				 vm::VM *vm, vm::Object *obj);
  static FileImage *GetFileImage(const string &fn);

 private:
  bool RunFile(const string &file, vm::VM *vm);

  static Method *ReadFile(const string &file);
  static void InitScannerInfo(ScannerInfo *s_info);
  static void InitSyms();

  bool dbg_parser_;

  static std::unique_ptr<ScannerInfo> scanner_info_;
};

}  // namespace fe

#endif  // _fe_fe_h_
