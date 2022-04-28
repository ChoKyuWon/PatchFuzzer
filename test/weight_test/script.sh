#!/bin/bash 

for var in {1..100}
do
	echo "handshake_patched_8 $var"
	afl-fuzz -i input -o ./output/patched8/output$var -m none ./handshake_patched_8
done

for var in {1..100}
do
	echo "handshake_patched_8_only_target $var"
	afl-fuzz -i input -o ./output/patched8_only_target/output$var -m none ./handshake_patched_8_only_target
done
