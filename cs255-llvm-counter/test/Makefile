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

check: test.c
	$(CC) -O0 -c -emit-llvm test.c -o test.bc
	$(OPT) -load ../build/lib/libInstCounterPass.so -inst-count <test.bc> test.bc.opt
	$(LLC) -filetype=obj test.bc.opt -o test.o
	$(CC) test.o $(RT)/libInstCounting_rt.a -o test

ir:	test.bc.opt
	$(DIS) test.bc.opt

clean:
	rm -f *.bc *.opt *.o *.ll test
