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

#include <cstdlib>
#include <vector>

#include <llvm-12/llvm/Transforms/Utils/FunctionComparator.h>

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
  std::vector<const BasicBlock*> diffBlocks;

  for(auto &BBR: *(this->FnR)){
    bool flag = false;
    for(auto &BBL: *(this->FnL)){
      if(cmpBasicBlocks(&BBL, &BBR))
        flag = true;
    }
    if(!flag)
      diffBlocks.push_back(&BBR);
  }
  for(auto& BB: *(this->FnR)){
    for(auto& I : BB){
      if(I.getOpcode() == Instruction::Xor){
          auto OP = I.getOperand(1);
          auto* R = ConstantInt::get(OP->getType(), std::rand() % MAP_SIZE);
          const_cast<Instruction*>(&I)->setOperand(1, R);
        }
    }
  }
  for(auto& BB: diffBlocks){
    errs() << BB << "\n";
    for(auto& I : *BB){
      if(I.getOpcode() == Instruction::Add){
        auto INC = I.getOperand(1);
        int val = 0;
        if(isa<ConstantInt>(INC))
          val = dyn_cast<ConstantInt>(INC)->getSExtValue();
        const_cast<Instruction*>(&I)->setOperand(1, ConstantInt::get(Type::getInt64Ty(C), 2));
        break;
      }
    }
  }
  return nullptr;
}