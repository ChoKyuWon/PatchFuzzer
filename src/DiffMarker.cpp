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

#include "DiffMaker.h"
using namespace llvm;



Function *DiffMarker::mark() {
  LLVMContext& C = this->FnR->getContext();
  std::vector<const BasicBlock*> diffBlocks;

  Function::const_iterator BBL = this->FnL->begin(), BBLE = this->FnL->end();
  Function::const_iterator BBR = this->FnR->begin(), BBRE = this->FnR->end();
  for(auto &BBR: *(this->FnR)){
    int res = cmpBasicBlocks(&*BBL, &BBR);
    if(res == 0)
      continue;
    else{
      if(BBL->size() != BBR.size()){
        diffBlocks.push_back(&BBR);
        continue;
      }
      BasicBlock::const_iterator InstL = BBL->begin(), InstR = BBR.begin();
      for(int i=0; i<BBL->size(); ++i){
        std::string strL, strR;
        raw_string_ostream(strL) << *InstL;
        raw_string_ostream(strR) << *InstR;
        if(strL != strR){
          diffBlocks.push_back(&BBR);
          break;
        }
        ++InstL;
        ++InstR;
      }
    }
    ++BBL;
  }
  for(auto& BB: diffBlocks){
    for(auto& I : *BB)
      if(I.getOpcode() == Instruction::Add){
        auto INC = I.getOperand(1);
        int val = 0;
        if(isa<ConstantInt>(INC))
          val = dyn_cast<ConstantInt>(INC)->getSExtValue();
        const_cast<Instruction*>(&I)->setOperand(1, ConstantInt::get(Type::getInt64Ty(C), 2));
      }
  }
  return nullptr;
}