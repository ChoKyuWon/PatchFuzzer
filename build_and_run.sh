make -C AFL/llvm_mode
make -C test patch
make -C test bitcode
make -C src
src/main ./test/test.bc ./test/patched_test.bc
