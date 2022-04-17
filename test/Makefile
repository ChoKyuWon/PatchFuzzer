patch:
	patch -p1 -i patch -o patched_test.c
bitcode:
	clang -emit-llvm -o test.bc -c test.c -g 
	clang -emit-llvm -o patched_test.bc -c patched_test.c -g
clean:
	rm patched_test.c
.PHONY:patch bitcode