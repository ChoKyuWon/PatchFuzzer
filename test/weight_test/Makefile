AFL_PATH=~/patchfuzzer_project/AFL

all:
	cd ./openssl && AFL_PATH=$(AFL_PATH) CC=$(AFL_PATH)/afl-clang-fast CXX=$(AFL_PATH)/afl-clang-fast++ ./config -d && AFL_PATH=$(AFL_PATH) AFL_USE_ASAN=1 make
	AFL_USE_ASAN=1 AFL_PATH=$(AFL_PATH) $(AFL_PATH)/afl-clang-fast++ -O0 -g handshake.cc openssl/libssl.a openssl/libcrypto.a -o handshake -I openssl/include/ -ldl
