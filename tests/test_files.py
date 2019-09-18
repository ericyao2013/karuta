#
EXTRA = ["QA", "imported_file.karuta", "run-test", "resource.v", "test_tb.v",
         "test_files.py"]

# see file QA to see category.
default_tests = ["fe_error/misc.karuta",
                 "fe_error/tbd.karuta",
                 "fe_error/infinite_loop.karuta",
                 "fe_error/parse_error.karuta",
                 "fe_lang/import_file.karuta", "fe_lang/load.karuta", "fe_lang/for.karuta",
                 "fe_lang/funcall.karuta", "fe_lang/if.karuta", "fe_lang/string.karuta",
                 "fe_lang/decl.karuta", "fe_lang/scope.karuta", "fe_lang/pipe.karuta",
                 "fe_lang/while.karuta",
                 "fe_misc/errors.karuta", "fe_misc/tb.karuta",
                 "fe_misc/hello.karuta", "fe_misc/parser.karuta",
                 "fe_misc/misc.karuta",
                 "fe_obj/object.karuta", "fe_obj/this_obj.karuta", "fe_obj/thread.karuta",
                 "fe_typeobj/basic.karuta",
                 "fe_value/basic.karuta", "fe_value/numeric.karuta",
                 "fe_value/false.karuta", "fe_value/array.karuta",
                 "lib_fp/fp16rmul.karuta",
                 "lib_fp/fp16baddsub.karuta",
                 "lib_fp/fp16bmul.karuta",
                 "synth_axi/interface_only.karuta",
                 "synth_ext/ext_entry.karuta",
                 "synth_ext/ext_io.karuta",
                 "synth_ext/ext_stub.karuta",
                 "synth_shared/channel.karuta",
                 "synth_shared/mailbox.karuta",
                 "synth_shared/mailbox_10.karuta",
                 "synth_shared/memory.karuta",
                 "synth_shared/notify.karuta",
                 "synth_shared/shared_reg.karuta",
                 "synth_misc/null.karuta", "synth_value/false.karuta",
                 "synth_value/basic.karuta",
                 "synth_value/bitops.karuta", "synth_value/shift.karuta",
                 "synth_value/array_ro.karuta", "synth_value/array_rw.karuta",
                 "synth_lang/mem.karuta", "synth_lang/cond.karuta", "synth_lang/member.karuta",
                 "synth_lang/import_resource.karuta", "synth_lang/return.karuta",
                 "synth_obj/sub_obj_call.karuta",
                 "synth_obj/multi_caller.karuta",
                 "synth_obj/inter_dep.karuta",
                 "synth_lang/funcall.karuta",
                 #"synth_lang/no_member_decl.karuta",
                 "synth_regression/t04_0_0_26.karuta",
                 "synth_regression/t04_0_0_30.karuta",
                 "synth_regression/t04_0_0_30_1.karuta",
                 "synth_regression/t04_0_0_30_2.karuta",
                 "synth_regression/t04_0_0_33.karuta",
                 "synth_regression/t04_0_0_33_1.karuta",
                 "synth_regression/t04_0_0_33_2.karuta",
                 "synth_regression/t04_0_0_33_3.karuta",
                 "synth_regression/t04_0_0_33_4.karuta",
                 "synth_regression/t04_0_0_33_5.karuta",
                 "synth_regression/t04_0_0_33_6.karuta",
                 "synth_regression/t04_0_0_34_1.karuta",
                 "synth_regression/t04_0_0_34_2.karuta",
                 "synth_regression/t04_0_0_35_1.karuta",
                 "synth_regression/t04_0_1_0_0.karuta",
                 "synth_regression/t04_0_1_1_0.karuta",
                 "synth_regression/t04_0_1_9_0.karuta",
                 "synth_regression/t04_0_1_9_1.karuta",
#                 "t91_funcall_width_infer.karuta",
#                 "type_inf.karuta",
                 ]

def GetFiles(base_dir):
    files = []
    for fn in default_tests + EXTRA:
        files.append(base_dir + fn)
    return files
