#===- test/Makefile -------------------------*- Makefile -*-===##

# Relative path to the top of the source tree.
#
LEVEL=..
BUILD=../build

#LLVM_BIN_DIR=/u/cs255/build-llvm-38/bin
#CLANG_BIN_DIR=/u/cs255/build-llvm-38/bin
CLANG_BIN_DIR=/LLVM_ROOT/build/bin
#LLVM_BIN_DIR=/u/cs255/dc_llvm/build/bin
LLVM_BIN_DIR=/LLVM_ROOT/build/bin

OPT= $(LLVM_BIN_DIR)/opt
LLC= $(LLVM_BIN_DIR)/llc
CC= $(CLANG_BIN_DIR)/clang
DIS= $(LLVM_BIN_DIR)/llvm-dis
RT = $(BUILD)/runtime

all: check dv ir

check: test.c
	$(CC) -O0 -c -emit-llvm test.c -o test.bc
	$(OPT) -load ../build/lib/libNatLoopPass.so -nloop <test.bc> test.bc.opt
	$(LLC) -filetype=obj test.bc.opt -o test.o
	$(CC) test.o $(RT)/libInstCounting_rt.a -o test

adv: advtest.c
	$(CC) -O0 -c -emit-llvm advtest.c -o advtest.bc
	$(OPT) -load ../build/lib/libNatLoopPass.so -nloop <advtest.bc> advtest.bc.opt
	$(LLC) -filetype=obj advtest.bc.opt -o advtest.o
	$(CC) advtest.o $(RT)/libInstCounting_rt.a -o advtest

ir:	
	$(DIS) test.bc.opt
	$(DIS) advtest.bc.opt

clean:
	rm -f *.bc *.opt *.o *.ll test advtest
