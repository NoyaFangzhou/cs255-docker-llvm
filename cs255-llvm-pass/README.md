
## Tutorial ##
A step-by-step tutorial for building an out-of-source LLVM pass based on Adrian Sampson's "LLVM for Grad Students" after you successfully build the docker image in your laptop.

- <b>STEP 0</b>

  Correctly pull your docker image from the Docker Hub, or build it by dockerfile. 
  
 
(After run the docker container)
- <b>STEP 1</b>
  
  Go to the cs255-llvm-pass directory
  ```bash
  $ cd cs255-llvm-pass/
  ```

- <b>STEP 2</b>

  Create a directory named build
  ```bash
  $ mkdir build
  ```

- <b>STEP 3</b>
 
  Under the build directory, build the LLVM Function Pass Template via cmake
  ```bash
  $ cmake ..
  
  # After cmake success
  $ make
  ```
  
To test whether you build success or not, please `cd` to the `test` directory and type `make check` in the command line.
If you build your pass template correct, you'll see the following output:
```bash
/LLVM_ROOT/build/bin/clang -O0 -c -emit-llvm test.c -o test.bc
test.c:9:4: warning: implicit declaration of function 'gets' is invalid in C99
      [-Wimplicit-function-declaration]
   gets(str);
   ^
1 warning generated.
/LLVM_ROOT/build/bin/opt -load ../build/lib/libInstCounterPass.so -inst-count <test.bc> test.bc.opt
Function: main
	No. 0 bb: 12 statements.
	No. 1 bb: 4 statements.
	No. 2 bb: 25 statements.
	No. 3 bb: 3 statements.
/LLVM_ROOT/build/bin/llc -filetype=obj test.bc.opt -o test.o
/LLVM_ROOT/build/bin/clang test.o ../build/runtime/libInstCounting_rt.a -o test
test.o: In function `main':
test.bc.opt:(.text+0x53): warning: the `gets' function is dangerous and should not be used.
```

## Build a trivial LLVM pass ##
After finish implementing your function pass, you can rebuild your function pass by repeating the procedure introduced in the previous session. Also, if you want to see what the IR code looks like, you can type `make ir` in the `test` directory. Then, you'll see `test.bc.opt.ll` file in the directory. These file contains the human readable IR code for your test program. 

Besides, type `make clean` in command line can remove all intermediate files and binary files for the test program.

### Useful resources
This tutorial is based on the following resources

- Adrian Sampson's blog entry "LLVM for Grad Students" ([link](http://adriansampson.net/blog/llvm.html))
- LLVM documentation: Writing an LLVM pass ([link](http://llvm.org/docs/WritingAnLLVMPass.html))
- LLVM documentation: Building LLVM with CMake ([link](http://llvm.org/docs/CMake.html#cmake-out-of-source-pass))

The origin tutorial file comes from [abenkhadra/llvm-pass-tutorial](https://github.com/abenkhadra/llvm-pass-tutorial)
