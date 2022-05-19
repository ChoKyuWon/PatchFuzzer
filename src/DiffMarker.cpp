#include "llvm/ADT/StringRef.h"
#include "llvm/Bitcode/BitcodeReader.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorOr.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Transforms/Utils/FunctionComparator.h"

#include <cstdlib>
#include <vector>

#include "DiffMarker.h"

#define MAP_SIZE 65536
using namespace llvm;

bool DiffMarker::cmpBasicBlocks(const BasicBlock* BBL, const BasicBlock* BBR)
{
  bool res = FunctionComparator::cmpBasicBlocks(BBL, BBR);
  if(res == 0) return res;
  else{
      if(BBL->size() != BBR->size()){
        return false;
      }
      BasicBlock::const_iterator InstL = BBL->begin(), InstR = BBR->begin();
      for(size_t i=0; i < BBL->size(); ++i){
        std::string strL, strR;
        raw_string_ostream(strL) << *InstL;
        raw_string_ostream(strR) << *InstR;
        if(strL != strR){
          return false;
        }
        ++InstL;
        ++InstR;
      }
    }
    return true;
}

void DiffMarker::traverse(std::vector<BasicBlock*> LeftList, std::vector<BasicBlock*> RightList)
{
}

Function *DiffMarker::mark() {
  LLVMContext& C = this->FnR->getContext();
  std::vector<BasicBlock*> diffBlocks;

  for(auto &BBR: *(this->FnR)){
    bool flag = false;
    for(auto &BBL: *(this->FnL)){
      if(cmpBasicBlocks(&BBL, &BBR))
        flag = true;
    }
    if(!flag)
      diffBlocks.push_back(const_cast<BasicBlock*>(&BBR));
  }

  // Block ID randomization
  // for(auto& BB: *(this->FnR)){
  //   for(auto& I : BB){
  //     if(I.getOpcode() == Instruction::Xor){
          
  //     }
  //   }
  // }

  // Work with diff blocks
  for(auto& BB: diffBlocks){
    int blockID = -1;
    for(auto& I : *BB){
      if(I.getOpcode() == Instruction::Xor){
          if(blockID != -1)
            continue;
          blockID = std::rand() % MAP_SIZE;
          auto OP = I.getOperand(1);
          auto* R = ConstantInt::get(OP->getType(), blockID);
          const_cast<Instruction*>(&I)->setOperand(1, R);
      }
      // Increase the weight
      if(I.getOpcode() == Instruction::Add){
        auto INC = I.getOperand(1);
        int val = 0;
        if(isa<ConstantInt>(INC))
          val = dyn_cast<ConstantInt>(INC)->getSExtValue();
        const_cast<Instruction*>(&I)->setOperand(1, ConstantInt::get(INC->getType(), 2));
        break;
      }
    }
    // Coverage measuring
      IntegerType *Int8Ty  = IntegerType::getInt8Ty(C);
      IntegerType *Int32Ty = IntegerType::getInt32Ty(C);
      const Module *M = FnR->getParent();
      
      GlobalVariable *AFLMapPtr = FnR->getParent()->getGlobalVariable("__afl_patched_area_ptr");
      assert(AFLMapPtr);
      IRBuilder<> IRB(&BB->front());
      LoadInst *MapPtr = IRB.CreateLoad(AFLMapPtr);
      MapPtr->setMetadata(M->getMDKindID("nosanitize"), MDNode::get(C, None));
      Value *MapPtrIdx =
          IRB.CreateGEP(MapPtr, ConstantInt::get(Int32Ty, blockID));

      LoadInst *Counter = IRB.CreateLoad(MapPtrIdx);
      Counter->setMetadata(M->getMDKindID("nosanitize"), MDNode::get(C, None));
      Value *Incr = IRB.CreateAdd(Counter, ConstantInt::get(Int8Ty, 1));
      IRB.CreateStore(Incr, MapPtrIdx)
          ->setMetadata(M->getMDKindID("nosanitize"), MDNode::get(C, None));
  }
  return nullptr;
}