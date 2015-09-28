// This part is copied from nli/ccrt_main.cpp
deque<uint64_t> NliChannel::data_;

int main(int argc, char **argv) {
  bool dbg = false;
  for (int i = 1; i < argc; ++i) {
    string arg(argv[i]);
    if (arg == "-d")  {
      dbg = true;
    }
  }
  Mod_main m;
  m.reset();
  int cycles = 0;
  m.PrepareState();
  while (!m.Dispatch()) {
    ++cycles;
    if (dbg) {
      m.DumpState();
    }
    m.PrepareState();
  }
  printf("%d cycles\n", cycles);
  return 0;
}
