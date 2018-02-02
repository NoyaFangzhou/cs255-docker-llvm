
## Tutorial ##
A step-by-step tutorial for building an out-of-source LLVM pass based on Adrian Sampson's "LLVM for Grad Students"

## Setup ##

LLVM is an umbrella project for building compilers
and code transformation tools. We consider in this tutorial:
- Building LLVM from source
- Building a trivial out-of-source LLVM pass.

We will be building LLVM v`5.0.0`.
We assume that you have a working compiler toolchain (GCC or LLVM) and that CMake is installed (minimum version `3.4.3`).

## Building a trivial LLVM pass ##


### Further resources
This tutorial is based on the following resources

- Adrian Sampson's blog entry "LLVM for Grad Students" ([link](http://adriansampson.net/blog/llvm.html))
- LLVM documentation: Writing an LLVM pass ([link](http://llvm.org/docs/WritingAnLLVMPass.html))
- LLVM documentation: Building LLVM with CMake ([link](http://llvm.org/docs/CMake.html#cmake-out-of-source-pass))

The origin tutorial file comes from [abenkhadra/llvm-pass-tutorial](https://github.com/abenkhadra/llvm-pass-tutorial)
