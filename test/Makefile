all:patch bitcode ll

patch:
	patch -p1 -i patch -o patched_test.c
bitcode:
	$(CC) -emit-llvm -o test.bc -c test.c -g -O0
	$(CC) -emit-llvm -o patched_test.bc -c patched_test.c -g -O0

ll:
	$(CC) -S -emit-llvm -o test.ll -c test.c -g -O0
	$(CC) -S -emit-llvm -o patched_test.ll -c patched_test.c -g -O0
clean:
	rm patched_test.c
.PHONY:patch bitcode