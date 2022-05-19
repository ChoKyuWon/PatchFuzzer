export AFL_PATH=`pwd`/../../AFL/
export LLVM_COMPILER_PATH=$AFL_PATH
export LLVM_COMPILER=clang
export CC=wllvm
export CXX=wllvm++
export AFL_QUIET=1

cd openssl
WLLVM_CONFIGURE_ONLY=1 ./config -d
AFL_USE_ASAN=1 make
cd ../
AFL_USE_ASAN=1 wllvm++ -O0 -g handshake.cc openssl/libssl.a openssl/libcrypto.a -o handshake -I openssl/include/ -ldl -fno-threadsafe-statics
extract-bc handshake -l llvm-link-12