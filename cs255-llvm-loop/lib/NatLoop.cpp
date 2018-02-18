//===- NatLoop.cpp - Code for Loop & DOM Analysis ------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the pass that can detects all BasicBlock within Loops
// And the DOM relation within these block.
//
//===----------------------------------------------------------------------===//

#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/CFG.h"


using namespace llvm;
using namespace std;


void nameBasicBlocks(Function &F);

namespace {
    
    // name each basic block in given function
    void nameBasicBlocks(Function &F) {
        for (Function::iterator BB = F.begin(), FE = F.end(); BB != FE; ++BB) {
            if (!BB->hasName()) {
                BB->setName("BB_");
            }
        }
    }
    
    
    // NatLoop - Find all nature loops and do the dominator analysis.
    struct NatLoop : public FunctionPass {
        static char ID; // Pass identification, replacement for typeid
        NatLoop() : FunctionPass(ID) {}
        
        bool runOnFunction(Function &F) override {
            
            return false;
        }
    };
}

char NatLoop::ID = 0;
static RegisterPass<NatLoop> X("nloop", "Nature Loop Analysis Pass");

