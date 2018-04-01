//===- InstCounter.cpp - Example code from "Writing an LLVM Pass" ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements two versions of the LLVM "InstCounter World" pass described
// in docs/WritingAnLLVMPass.html
//
//===----------------------------------------------------------------------===//

#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

#define DEBUG_TYPE "cs255"


/* The following code counts and reports the number of static 
 * statements in every basic block. */
void  count_static_stmts(Function &F){
	errs() <<  "Function: " << F.getName() << "\n";

	int bb_counter = 0;
	for (Function::iterator BB = F.begin(), FE = F.end(); BB != FE; ++BB) {	
		int stmt_counter = 0;
		for (BasicBlock::iterator II = BB->begin(), BBE = BB->end(); II != BBE; ++II) {	
			if(!isa<AllocaInst>(II) && !isa<PHINode>(II))
				stmt_counter++;
		}
		errs() << "\tNo. " << bb_counter << "bb: " << stmt_counter << " statements.\n";
		bb_counter++;
	}
}

/* The following code transforms the program to count
 * the number of dynamic basic block executions.  
 * TODO You need to transform the program to
 * count the number of dynamic statement executions.
 * You can base you work on the following code. */

void count_dynamic_bbs(Function &F){

	Module *M = F.getParent();
	for (Function::iterator BB = F.begin(), E = F.end(); BB != E; ++BB) {	
		BasicBlock::iterator InsertPos = BB->begin();
		while (InsertPos!=BB->end() && (isa<AllocaInst>(InsertPos) || isa<PHINode>(InsertPos)))
			InsertPos++;
		LLVMContext &Context = F.getContext();
		Type *VoidTy = Type::getVoidTy(Context);
		Constant *IncFn = M->getOrInsertFunction("increase", VoidTy, (Type *)0);
		if(InsertPos==BB->end())
			CallInst::Create(IncFn,  "", &*BB);
		else
			CallInst::Create(IncFn,  "", &*InsertPos);
	}


}

/* You need to transform the main function to Call init()
 * at the entry of the program. */

void add_init_call(Function &F){
	if(F.getName().equals("main")){
		/* TODO */
	}


}


namespace {
	// InstCounter - The first implementation, without getAnalysisUsage.
	struct InstCounter : public FunctionPass {
		static char ID; // Pass identification, replacement for typeid
		InstCounter() : FunctionPass(ID) {}

		bool runOnFunction(Function &F) override {
			count_static_stmts(F);
			count_dynamic_bbs(F);
			add_init_call(F);
			return true;
		}
	};
}

char InstCounter::ID = 0;
static RegisterPass<InstCounter> X("nloop", "Nature Loop Detector");
