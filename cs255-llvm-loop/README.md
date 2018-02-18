
## Tutorial ##
A step-by-step tutorial for building an out-of-source LLVM pass based on Adrian Sampson's "LLVM for Grad Students" after you successfully build the docker image in your laptop.

- <b>STEP 0</b>

  Correctly pull your docker image from the Docker Hub, or build it by dockerfile. 
  
 
(After run the docker container)
- <b>STEP 1</b>
  
  Go to the cs255-llvm-pass directory
  ```bash
  $ cd cs255-llvm-loop/
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

## Build a LLVM pass ##
After finish implementing your function pass, you can rebuild your function pass by repeating the procedure introduced in the previous session(JUST type `make` under build directory is fine). Also, if you want to see what the IR code looks like, you can type `make ir` in the `test` directory. Then, you'll see `test.bc.opt.ll` file in the directory. These file contains the human readable IR code for your test program. 

Besides, type `make clean` in command line can remove all intermediate files and binary files for the test program.

In this assignment, you only have to deal with nature loops. However, in the test file, I also prepare a program(5-point stencil) contains nested loops. If you want to have a try on nested loops, you can type `make adv` under test directory to see whether your compiler pass works.

### Useful resources
This tutorial is based on the following resources

- Adrian Sampson's blog entry "LLVM for Grad Students" ([link](http://adriansampson.net/blog/llvm.html))
- LLVM documentation: Writing an LLVM pass ([link](http://llvm.org/docs/WritingAnLLVMPass.html))
- LLVM documentation: Building LLVM with CMake ([link](http://llvm.org/docs/CMake.html#cmake-out-of-source-pass))

The origin tutorial file comes from [abenkhadra/llvm-pass-tutorial](https://github.com/abenkhadra/llvm-pass-tutorial)
