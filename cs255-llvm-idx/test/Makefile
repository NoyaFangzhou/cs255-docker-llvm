#===- runtime/Makefile -------------------------*- Makefile -*-===##

# Relative path to the top of the source tree.
#
LEVEL=..

#LLVM_BIN_DIR=/u/cs255/build-llvm-38/bin
CLANG_BIN_DIR=/u/cs255/build-llvm-38/bin
LLVM_BIN_DIR=/u/cs255/dc_llvm/build/bin

# INST_COUNT_LIB=/Users/Fangzhou_Liu/Documents/fzllvm/build/Debug/lib

OPT= $(LLVM_BIN_DIR)/opt
LLC= $(LLVM_BIN_DIR)/llc
CC= $(CLANG_BIN_DIR)/clang
DIS= $(LLVM_BIN_DIR)/llvm-dis

benchmark := case_a case_b case_c case_d case_e case_f case_g 

check: test.c
	$(CC) -O0 -c -emit-llvm test.c -o test.bc
	$(OPT) -load ../Debug+Asserts/lib/libLLVMInstCnt.so -nloop <test.bc> test.bc.opt

# bench:
# 	for prog in $(benchmark); do \
# 		echo $(prog); \
# 		$(CC) -O0 -c -g -emit-llvm $(prog).c -o $(prog).bc; \
# 		$(OPT) -load ../Debug+Asserts/lib/libLLVMInstCnt.so -nloop <$(prog).bc> $(prog).bc.opt; \
# 	done; \

all:
	$(foreach prog, $(benchmark), $(CC) -O0 -c -g -emit-llvm $(prog).c -o $(prog).bc ;)
	$(foreach prog, $(benchmark), $(OPT) -load ../Debug+Asserts/lib/libLLVMInstCnt.so -nloop <$(prog).bc> $(prog).bc.opt ;)

line:
	$(foreach prog, $(benchmark), $(CC) -O0 -g -S -emit-llvm $(prog).c -o $(prog).ll ;)
	$(CC) -O0 -g -S -emit-llvm hard.c -o hard.ll

hard: hard.c
	$(CC) -O0 -c -g -emit-llvm hard.c -o hard.bc
	$(OPT) -load ../Debug+Asserts/lib/libLLVMInstCnt.so -nloop <hard.bc> hard.bc.opt

ir:
	$(foreach prog, $(benchmark), $(DIS) $(prog).bc.opt ;)

clean:
	rm -f *.bc *.opt *.o *.ll

