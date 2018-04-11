//===- InstCounter.cpp - Code for Previous 3 Analysis ------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
// Take credit to Zhuojia Shen, who helps me on finding induction variables
//
//===----------------------------------------------------------------------===//
//
// This file implements the pass that can detects all BasicBlock within Loops
// And the DOM relation within these block, all Basic and Derived Induction variable
// And the array indices.
//
//===----------------------------------------------------------------------===//

#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/CFG.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Dominators.h"

using namespace llvm;
using namespace std;

#define DEBUG_TYPE "natloop"
// Global DS
vector<Loop *> LOOP_INFO_VECTOR;
map<BasicBlock *, vector<BasicBlock *>> DOM_MAP;
vector<BasicBlock *> BB_VECTOR;
vector<pair<const BasicBlock *, const BasicBlock *>> BACK_EDGE_VECTOR;
map<Loop*, map<string, vector<Value *>>> ARRAY_INFO_MAP;
map<Loop*, vector<Value *>> BASIC_INDUC_VAR;
map<Loop*, vector<Value *>> DERIVED_INDUC_VAR;

// Helper Func
void nameBasicBlocks(Function &F);
string getArrayName(Value* pointer);
string getValueExpr(Value* v);
bool is_linear_basic_indvar(Value * use, vector<Value *> bvars);

// Assignment 2
void getLoopAnalysis(LoopInfo &root);
void getDomAnalysis(DominatorTree &tree);
void getBackEdge(Function &F);

// Assignment 3
void getArrayInfoFromLoop(Loop *loop);
void getBasicInducVar(Loop *loop);
void getDerivedIndcVar(Loop *loop);

// Dump Func
void dump_loop_info();
void dump_dom_info();
void dump_backedge(SmallVectorImpl<pair<const BasicBlock *, const BasicBlock *>> &smv);
    
// name each basic block in each function
void nameBasicBlocks(Function &F) {
    for (Function::iterator BB = F.begin(), FE = F.end(); BB != FE; ++BB) {
        BB_VECTOR.push_back(dyn_cast<BasicBlock>(BB));
        if (!BB->hasName()) {
            BB->setName("BB_");
        }
    }
}

string getArrayName(Value* pointer) {
//        errs() << *pointer << "\n";
    // constant array
    if (isa<GlobalVariable>(pointer) || isa<ConstantArray>(pointer)) {
        return pointer->getName().str();
    }
    if (!isa<Instruction>(pointer)) {
        return "";
    }
    Instruction* instr = dyn_cast<Instruction>(pointer);
    GetElementPtrInst *gepinst = dyn_cast<GetElementPtrInst>(instr);
    switch (instr->getOpcode()) {
        case Instruction::Alloca:
            return instr->getName().str();
            break;
        case Instruction::Load:
        {
            LoadInst* load = dyn_cast<LoadInst>(instr);
            if (load->getPointerOperand()->hasName()) {
                return getArrayName(load->getPointerOperand());
            }
            else {
                BasicBlock* b = cast<Instruction>(load->getPointerOperand())->getParent();
                for (BasicBlock::iterator IIT = b->begin(); IIT != b->end(); ++IIT) {
                    Instruction* i = dyn_cast<Instruction>(IIT);
//                        errs() << *i << "\n";
                    if (isa<StoreInst>(i) && i->getOperand(1) == load->getPointerOperand()) {
                        return i->getOperand(0)->getName().str();
                    }
                }
            }
            return "";
            break;
        }
        case Instruction::GetElementPtr:
//                errs() << "Pointer: \t" << * dyn_cast<GetElementPtrInst>(dyn_cast<GetElementPtrInst>(instr) << "\n";
            return getArrayName(dyn_cast<GetElementPtrInst>(gepinst->getPointerOperand()));
            break;
        default:
            return "";
            break;
    }
}

// print the value expresion in string format
string getValueExpr(Value* v) {
    if (isa<Instruction>(v)) {
        
        Instruction* inst = cast<Instruction>(v);
        
        switch (inst->getOpcode()) {
            case Instruction::Add:
                return "(" + getValueExpr(inst->getOperand(0)) + " + " + getValueExpr(inst->getOperand(1)) + ")";
                break;
            case Instruction::Sub:
                return "(" + getValueExpr(inst->getOperand(0)) + " - " + getValueExpr(inst->getOperand(1)) + ")";;
                break;
            case Instruction::Mul:
                return "(" + getValueExpr(inst->getOperand(0)) + " * " + getValueExpr(inst->getOperand(1)) + ")";;
                break;
            case Instruction::FDiv:
            case Instruction::SDiv:
            case Instruction::UDiv:
                return "(" + getValueExpr(inst->getOperand(0)) + " / " + getValueExpr(inst->getOperand(1)) + ")";
                break;
            case Instruction::Alloca:
                return inst->getName().str();
            case Instruction::Load:
                return cast<LoadInst>(inst)->getPointerOperand()->getName().str();
                break;
            case Instruction::SExt:
                return getValueExpr(inst->getOperand(0));
            default:
                return "";
                break;
        }
    }
    else if (isa<ConstantInt>(v)) {
        return to_string(dyn_cast<ConstantInt>(v)->getValue().getSExtValue());
    }
    else if (v->hasName()) {
        return v->getName().str();
    }
    return "";
}

bool is_linear_basic_indvar(Value * use, vector<Value *> bvars) {
    while (true) {
        Instruction * inst = NULL;
        LoadInst * load = NULL;
        Value * op1 = NULL, * op2 = NULL;

        /*
        * Every use in the use-def chain should be an
        * instruction.
        */
        if (!isa<Instruction>(use)) {
            return false;
        }
        inst = cast<Instruction>(use);

        switch (inst->getOpcode()) {
            /* Linear opcode */
            case Instruction::Add:
            case Instruction::Sub:
            case Instruction::Mul:
                op1 = inst->getOperand(0);
                op2 = inst->getOperand(1);
                /* One operand must be a constant */
                if (isa<Constant>(op1)) {
                    use = op2;
                } else if (isa<Constant>(op2)) {
                    use = op1;
                } else {
                    return false;
                }
                break;
            case Instruction::UDiv:
            case Instruction::SDiv:
            case Instruction::URem:
            case Instruction::SRem:
                op1 = inst->getOperand(0);
                op2 = inst->getOperand(1);
                if (isa<Constant>(op2)) {
                    use = op1;
                } else {
                    return false;
                }
                break;
            /* Get a load instruction */
            case Instruction::Load:
                load = cast<LoadInst>(inst);
                op1 = load->getPointerOperand();
                /* Its operand must have a name */
                if (!op1->hasName()) {
                    return false;
                }
                /* Its operand must be a basic indvar */
                if (find(bvars.begin(), bvars.end(), op1) == bvars.end()) {
                    return false;
                }
                /*
                * If we reach here, the variable must be a
                * derived indvar.
                */
                return true;
            default:
                return false;
        }
    }
}


// iterate each loop and find
// 1. All Loops
// 2. All BasicBlocks in each loop
void getLoopAnalysis(LoopInfo &root) {
    for (LoopInfo::iterator LI = root.begin(), LE = root.end(); LI != LE; ++LI) {
        Loop* loop = *LI;
        
        LOOP_INFO_VECTOR.push_back(loop);
        
        // iterate all subloops
        for (auto subloop: loop->getSubLoops()) {
            LOOP_INFO_VECTOR.push_back(subloop);
        }
        
    }
}

// iterate each Loop and get the dominator information within each loop
void getDomAnalysis(DominatorTree &tree) {
    for (vector<BasicBlock *>::iterator bb = BB_VECTOR.begin(), ebb = BB_VECTOR.end(); bb != ebb; ++bb) {
        BasicBlock* b = *bb;
        SmallVector<BasicBlock *, 8> dominatees;
        tree.getDescendants(b, dominatees);
        vector<BasicBlock *> d;
        for (auto b: dominatees) {
            d.push_back(b);
        }
        DOM_MAP.insert(map<BasicBlock *, vector<BasicBlock *>>::value_type(b, d));
    }
}

void getBackEdge(Function &F) {
    SmallVector<pair<const BasicBlock *, const BasicBlock *>, 8> backedge;
    FindFunctionBackedges(F, backedge);
//        errs() << "\nBack Edges: \n";
    for(auto backedge_pair: backedge) {
        BACK_EDGE_VECTOR.push_back(make_pair(backedge_pair.first, backedge_pair.second));
//            errs() << backedge_pair.first->getName() << " -> " << backedge_pair.second->getName() << "\n";
    }
}

map<Value *, bool> findDef(Loop* loop) {
    map<Value *, bool> temp;
    for (Loop::block_iterator BBI = loop->block_begin(); BBI != loop->block_end(); ++BBI) {
        BasicBlock* BB = *BBI;
        for (auto inst = BB->begin(); inst != BB->end(); ++inst) {
            if (isa<StoreInst>(inst)) {
                StoreInst* stinst = cast<StoreInst>(inst);
                if (stinst->getPointerOperand()->hasName()) {
                    temp.insert(map<Value *, bool>::value_type(stinst->getPointerOperand(), true));
                }
            }
        }
    }
    return temp;
}

void getBasicInducVar(Loop *loop) {
    vector<Value *> basic_ind_var;
    auto is_bvar = findDef(loop);
    for (Loop::block_iterator BBI = loop->block_begin(); BBI != loop->block_end(); ++BBI) {
        BasicBlock *BB = *BBI;
        /* Iterate over all the instructions, finding store */
        for (auto inst = BB->begin(); inst != BB->end(); ++inst) {
            Value* op1 = NULL, * op2 = NULL, * var = NULL;
            LoadInst* load = NULL;
            StoreInst* store = NULL;
            Instruction* addsub = NULL;

            /* Get a store instruction */
            if (!isa<StoreInst>(inst)) {
                continue;
            }
            store = cast<StoreInst>(inst);

            /*
            * Ensure its pointer operand is a variable
            * (it has a name).
            */
            var = store->getPointerOperand();
            if (!var->hasName()) {
                continue;
            }

            /* Ensure it uses a value of instruction */
            if (!isa<Instruction>(store->getValueOperand())) {
                /*
                * Mark this variable as not basic
                * indvar, the same below.
                */
                is_bvar[var] = false;
                continue;
            }
            addsub = cast<Instruction>(store->getValueOperand());

            /* The use must have exactly 2 operands */
            if (addsub->getNumOperands() != 2) {
                is_bvar[var] = false;
                continue;
            }
            op1 = addsub->getOperand(0);
            op2 = addsub->getOperand(1);

            switch (addsub->getOpcode()) {
                case Instruction::Add:
                    /*
                    * Must be load + constant or
                    * constant + load.
                    */
                    if (isa<LoadInst>(op1) && isa<Constant>(op2)) {
                    load = cast<LoadInst>(op1);
                    } else if (isa<Constant>(op1) &&
                    isa<LoadInst>(op2)) {
                    load = cast<LoadInst>(op2);
                    } else {
                    is_bvar[var] = false;
                    continue;
                    }
                    break;
                case Instruction::Sub:
                    /* Must be load - constant */
                    if (isa<LoadInst>(op1) && isa<Constant>(op2)) {
                        load = cast<LoadInst>(op1);
                    } else {
                        is_bvar[var] = false;
                        continue;
                    }
                    break;
                default:
                    is_bvar[var] = false;
                    continue;
            }
        }
    }
    for (auto def : is_bvar) {
        if (def.second) {
            basic_ind_var.push_back(def.first);
        }
    }
    BASIC_INDUC_VAR.insert(map<Loop *, vector<Value *>>::value_type(loop, basic_ind_var));
}

void getDerivedIndcVar(Loop *loop) {
    // get the basic induction variable defines within the loop
    vector<Value *> basic_ind_var = BASIC_INDUC_VAR[loop];
    vector<Value *> derived_ind_var;
    auto single_def = findDef(loop);

    for (Loop::block_iterator BBI = loop->block_begin(); BBI != loop->block_end(); ++BBI) {
        BasicBlock *BB = *BBI;
        /* Iterate over all the instructions, finding store */
        for (auto inst = BB->begin(); inst != BB->end(); ++inst) {
            Value * var = NULL;
            StoreInst * store = NULL;

            /* Get a store instruction */
            if (!isa<StoreInst>(inst)) {
                continue;
            }
            store = cast<StoreInst>(inst);

            /*
            * Ensure its pointer operand is a variable
            * (it has a name).
            */
            var = store->getPointerOperand();
            if (!var->hasName()) {
                continue;
            }

            /* Skip if the variable is a basic indvar */
            if (find(basic_ind_var.begin(), basic_ind_var.end(), var) != basic_ind_var.end()) {
                continue;
            }
            /*
            * Skip if the variable is defined more than
            * once in the loop.
            */
            if (single_def[var]) {
                single_def[var] = false;
            } else {
                continue;
            }

            /*
            * Now we get here, we should check if the
            * variable is a linear function of a basic
            * indvar.
            */
            Value * use = store->getValueOperand();
            if (is_linear_basic_indvar(use, basic_ind_var)) {
                derived_ind_var.push_back(var);
            }
        }
    }
    DERIVED_INDUC_VAR.insert(map<Loop *, vector<Value *>>::value_type(loop, derived_ind_var));
}


// find array name with its index expression
void getArrayInfoFromLoop(Loop *loop) {
    map<string, vector<Value *>> temp_map;
    for (Loop::block_iterator BBI = loop->block_begin(); BBI != loop->block_end(); ++BBI) {
        BasicBlock* bb = *BBI;
        for (BasicBlock::iterator II = bb->begin(); II != bb->end(); ++II) {

            if (isa<GetElementPtrInst>(*II)) {
                GetElementPtrInst* gepinst = dyn_cast<GetElementPtrInst>(II);
                // get the array name
                Value* arr = gepinst->getPointerOperand();
                string arr_name = getArrayName(arr);
                // array access was found before
                if (temp_map.find(arr_name) == temp_map.end()) {
                    vector<Value *> temp_vector;
                    temp_map.insert(map<string, vector<Value *>>::value_type(arr_name, temp_vector));
                }
                for (auto VI = gepinst->idx_begin(); VI != gepinst->idx_end(); ++VI) {
                    // check whether it is an array pointer
                    if (VI == gepinst->idx_begin() && isa<ArrayType>(arr->getType()->getPointerElementType())) {
                        continue;
                    }
                    temp_map[arr_name].push_back(*VI);
                }
            }
        }
    }
    ARRAY_INFO_MAP.insert(map<Loop *, map<string, vector<Value *>>>::value_type(loop, temp_map));
}

// print the loop and its basic blocks
void dump_loop_info() {
    int loopcount = 0;
    errs() << "There are " << LOOP_INFO_VECTOR.size() << " Loops in total\n";
    for (vector<Loop *>::iterator it = LOOP_INFO_VECTOR.begin(), eit = LOOP_INFO_VECTOR.end(); it != eit; ++it) {
        loopcount++;
        errs() << "In Loop " << loopcount << ":\n";
        Loop* l = *it;
        for (Loop::block_iterator BBI = l->block_begin(); BBI != l->block_end(); ++BBI) {
            errs() << (*BBI)->getName() << " ";
        }
        errs() << "\n";
    }
}

// print the dominator and all basic blocks it dominates
void dump_dom_info() {
    errs() << "\nDominator List: \n";
    for (map<BasicBlock *, vector<BasicBlock *>>::iterator it = DOM_MAP.begin(); it != DOM_MAP.end(); ++it) {
        errs() << it->first->getName() << ":\t";
        for (auto dombb: it->second) {
            errs() << dombb->getName() << ", ";
        }
        errs() << "\n";
    }
    
}

// print the backedge
void dump_backedge() {
    errs() << "\nBack Edges: \n";
    for(auto backedge_pair: BACK_EDGE_VECTOR) {
        errs() << backedge_pair.first->getName() << " -> " << backedge_pair.second->getName() << "\n";
    }
}

void dump_basic_induction_var() {
    int loop = 0;
    for (map<Loop *, vector<Value *>>::iterator it = BASIC_INDUC_VAR.begin(); it != BASIC_INDUC_VAR.end(); ++it) {
        if (!it->second.empty()) {
            errs() << "\nBasic Induction Variable in Loop " << loop <<"\n";
        }
        for (auto var: it->second) {
            errs() << getValueExpr(var) << " | ";
        }
        errs() << "\n";
        loop ++;
    }
    
}

void dump_derived_indcution_var() {
    int loop = 0;
    for (map<Loop *, vector<Value *>>::iterator it = DERIVED_INDUC_VAR.begin(); it != DERIVED_INDUC_VAR.end(); ++it) {
        if (!it->second.empty()) {
            errs() << "\nDerived Induction Variable in Loop " << loop <<"\n";
        }
        for (auto var: it->second) {
            errs() << getValueExpr(var) << " | ";
        }
        errs() << "\n";
        loop ++;
    }
    
}

// print the array access
void dump_array_accesses() {
    int loop = 0;
    for (map<Loop *, map<string, vector<Value *>>>::iterator it = ARRAY_INFO_MAP.begin(); it != ARRAY_INFO_MAP.end(); ++it) {
        if (!it->second.empty()) {
            errs() << "\nArray Accesses in Loop " << loop <<"\n";
        }
        for (map<string, vector<Value *>>::iterator iit = it->second.begin(); iit != it->second.end(); ++iit) {
            errs() << "Access to " << iit->first << " is\t";
            for (auto value : iit->second) {
//                    errs() << *value << " | ";
                errs() << getValueExpr(value) << " | ";
            }
            errs() << "\n";
        }
        loop ++;
    }
}
    
namespace{
    // NatLoop - Find all nature loops and do the dominator analysis.
    struct InstCounter : public FunctionPass {
        static char ID; // Pass identification, replacement for typeid
        InstCounter() : FunctionPass(ID) {}
        
        bool runOnFunction(Function &F) override {
            nameBasicBlocks(F);
            LoopInfo &root = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
            getLoopAnalysis(root);
            dump_loop_info();
            DominatorTree &dtree = getAnalysis<DominatorTreeWrapperPass>().getDomTree();
            getDomAnalysis(dtree);
            dump_dom_info();
            getBackEdge(F);
            dump_backedge();
            // get array accesses from loop
            for (auto loop: LOOP_INFO_VECTOR) {
                getBasicInducVar(loop);
                getDerivedIndcVar(loop);
                getArrayInfoFromLoop(loop);
            }
            dump_basic_induction_var();
            dump_derived_indcution_var();
            dump_array_accesses();
            
            return false;
        }
        
        void getAnalysisUsage(AnalysisUsage &AU) const override{
            AU.setPreservesAll();
            AU.addRequired<LoopInfoWrapperPass>();
            AU.addRequired<DominatorTreeWrapperPass>();
        }
    };
}

char InstCounter::ID = 0;
static RegisterPass<InstCounter> X("nloop", "Induction variable and Array Index Analysis Pass");


