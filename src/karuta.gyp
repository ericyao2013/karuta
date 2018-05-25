# gyp src/karuta.gyp --depth=. -f make
{
  'make_global_settings': [
  ],
  'target_defaults': {
    'cflags': [ '-std=c++11', ],
    'defines': ['PACKAGE="karuta"', 'VERSION="0.3.2wip"'],
    'xcode_settings': {
      'OTHER_CFLAGS': [
          '-std=c++11',
      ],
    },
  },
  'targets': [
    {
      'target_name': 'karuta',
      'product_name': 'karuta',
      'type': 'executable',
      'include_dirs': [
        './',
        '../iroha/src/',
      ],
      'sources': [
        'base/pool.h',
        'base/annotation.cpp',
        'base/annotation.h',
        'base/annotation_builder.cpp',
        'base/annotation_builder.h',
        'base/dump_stream.cpp',
        'base/dump_stream.h',
        'base/status.cpp',
        'base/status.h',
        'base/stl_util.h',
        'base/sym.cpp',
        'base/sym.h',
        'base/util.cpp',
        'base/util.h',
        'base/logging.cpp',
        'base/logging.h',
        'compiler/compiler.cpp',
        'compiler/compiler.h',
        'compiler/common.h',
        'compiler/expr_compiler.cpp',
        'compiler/expr_compiler.h',
        'compiler/reg_checker.cpp',
        'compiler/reg_checker.h',
        'fe/builder.cpp',
        'fe/builder.h',
        'fe/common.cpp',
        'fe/common.h',
        'fe/emitter.cpp',
        'fe/emitter.h',
        'fe/enum_decl.cpp',
        'fe/enum_decl.h',
        'fe/expr.cpp',
        'fe/expr.h',
        'fe/fe.cpp',
        'fe/fe.h',
        'fe/parser.cpp',
        'fe/parser.h',
        'fe/method.cpp',
        'fe/method.h',
        'fe/nodecode.cpp',
        'fe/nodecode.h',
        'fe/scanner.cpp',
        'fe/scanner.h',
        'fe/stmt.cpp',
        'fe/stmt.h',
        'fe/var_decl.cpp',
        'fe/var_decl.h',
        'main.cpp',
        'karuta.cpp',
        'karuta.h',
        'synth/common.h',
        'synth/design_synth.cpp',
        'synth/design_synth.h',
        'synth/insn_walker.cpp',
        'synth/insn_walker.h',
        'synth/method_context.cpp',
        'synth/method_context.h',
        'synth/method_expander.cpp',
        'synth/method_expander.h',
        'synth/method_scanner.cpp',
        'synth/method_scanner.h',
        'synth/method_synth.cpp',
        'synth/method_synth.h',
        'synth/object_method.cpp',
        'synth/object_method.h',
        'synth/object_method_names.h',
        'synth/object_synth.cpp',
        'synth/object_synth.h',
        'synth/object_tree.cpp',
        'synth/object_tree.h',
        'synth/resource_set.cpp',
        'synth/resource_set.h',
        'synth/resource_synth.cpp',
        'synth/resource_synth.h',
        'synth/shared_resource_set.cpp',
        'synth/shared_resource_set.h',
        'synth/synth.cpp',
        'synth/synth.h',
        'synth/thread_synth.cpp',
        'synth/thread_synth.h',
        'synth/tool.cpp',
        'synth/tool.h',
        'vm/array_wrapper.cpp',
        'vm/array_wrapper.h',
        'vm/channel_wrapper.cpp',
        'vm/channel_wrapper.h',
        'vm/common.h',
        'vm/executor.cpp',
        'vm/executor.h',
        'vm/gc.cpp',
        'vm/gc.h',
        'vm/insn_annotator.cpp',
        'vm/insn_annotator.h',
        'vm/insn.cpp',
        'vm/insn.h',
        'vm/int_array.cpp',
        'vm/int_array.h',
        'vm/mailbox_wrapper.cpp',
        'vm/mailbox_wrapper.h',
        'vm/method.cpp',
        'vm/method.h',
        'vm/native_methods.cpp',
        'vm/native_methods.h',
        'vm/numeric_object.cpp',
        'vm/numeric_object.h',
        'vm/object.cpp',
        'vm/object.h',
        'vm/opcode.cpp',
        'vm/opcode.h',
        'vm/register.cpp',
        'vm/register.h',
        'vm/enum_type_wrapper.cpp',
        'vm/enum_type_wrapper.h',
        'vm/string_wrapper.cpp',
        'vm/string_wrapper.h',
        'vm/thread.cpp',
        'vm/thread.h',
        'vm/thread_wrapper.cpp',
        'vm/thread_wrapper.h',
        'vm/tls_wrapper.cpp',
        'vm/tls_wrapper.h',
        'vm/value.cpp',
        'vm/value.h',
        'vm/vm.cpp',
        'vm/vm.h',
      ],
      'dependencies': [
        '../iroha/src/iroha.gyp:libiroha'
      ],
    },
  ] # targets
}
