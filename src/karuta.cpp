#include "karuta.h"

#include <set>
#include <string.h>

using std::set;

const char *Env::karuta_dir_;
string Env::output_root_;
string Env::output_marker_;
string Env::module_prefix_;
bool Env::sandbox_mode_;
string Env::argv0_;
string Env::iroha_bin_path_;

const string &Env::GetVersion() {
  static string v(VERSION);
  return v;
}

const char *Env::GetKarutaDir() {
  if (!karuta_dir_) {
    karuta_dir_ = getenv("KARUTA_DIR");
  }
  if (!karuta_dir_) {
#ifdef KARUTA_DIR
    karuta_dir_ = KARUTA_DIR;
#else
    karuta_dir_ = ".";
#endif
  }
  return karuta_dir_;
}

void Env::SearchPathList(const char *fn,
			 vector<string> *paths) {
  if (fn[0] != '/' && fn[0] != '.') {
    string fn1 = Env::GetKarutaDir() +
      string("/") + string(fn);
    paths->push_back(fn1);
  }
  paths->push_back(string(fn));
}

bool Env::GetOutputPath(const char *fn, string *path) {
  if (output_root_.empty()) {
    *path = string(fn);
    return true;
  }
  if (sandbox_mode_) {
    if (!strncmp(fn, "../", 3)) {
      return false;
    }
    if (strstr(fn, "/../")) {
      return false;
    }
  }
  *path = output_root_ + string("/") + fn;
  return true;
}

const string &Env::GetOutputMarker() {
  return output_marker_;
}

void Env::SetOutputRootPath(const string &path) {
  output_root_ = path;
  sandbox_mode_ = true;
}

void Env::SetOutputMarker(const string &marker) {
  output_marker_ = marker;
}

void Env::SetModulePrefix(const string &name) {
  module_prefix_ = name;
}

const string & Env::GetModulePrefix() {
  return module_prefix_;
}

void Env::SetArgv0(const string &c) {
  argv0_ = c;
}

const string &Env::GetArgv0() {
  return argv0_;
}

bool Env::IsSandboxMode() {
  return sandbox_mode_;
}

void Env::SetIrohaBinPath(const string &iroha) {
  iroha_bin_path_ = iroha;
}

const string &Env::GetIrohaBinPath() {
  return iroha_bin_path_;
}
