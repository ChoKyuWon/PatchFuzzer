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
  Function::const_iterator BBL = this->FnL->begin(), BBLE = this->FnL->end();
  Function::const_iterator BBR = this->FnR->begin(), BBRE = this->FnR->end();
  do {
    errs() << "left block is...\n";
    for(auto& I : *BBL)
      errs() << I << "\n";
    errs() << "right block is...\n";
    for(auto& I : *BBR)
      errs() << I << "\n";

    int res = cmpBasicBlocks(&*BBL, &*BBR);

    errs() << "This block is... " << res << "\n";
    ++BBL;
    ++BBR;
  } while (BBL != BBLE && BBR != BBRE);
  return nullptr;
}