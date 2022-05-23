export AFL_PATH=`pwd`/../../AFL/
export LLVM_COMPILER_PATH=$AFL_PATH
export LLVM_COMPILER=clang
export CC=wllvm
export CXX=wllvm++
export AFL_QUIET=1
export AFL_USE_ASAN=1

cd openssl
WLLVM_CONFIGURE_ONLY=1 ./config -d
make -j`nproc`
cd ../
wllvm++ -O0 -g handshake.cc openssl/libssl.a openssl/libcrypto.a -o handshake -I openssl/include/ -ldl -fno-threadsafe-statics 
extract-bc handshake -l llvm-link-12
echo "[*] Compile done! Please give me the function list and end..."
../../src/main ../test.bc ./handshake.bc
echo "[*] BC write done! I'll compile the bitcode NOW..."
llc-12 module -o handshake.opt.s
clang handshake.opt.s openssl/libssl.a openssl/libcrypto.a -fsanitize=address -L$AFL_PATH/ -l:afl-llvm-rt.o -o handshake.opt.out
echo "[*] Compile done! cleanup some trash..."
rm handshake.bc handshake.opt.s module
