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
#include "llvm/Transforms/Utils/FunctionComparator.h"

using namespace llvm;

class DiffMarker : public FunctionComparator {
public:
  Function *mark(Function *original, Function *patched);
};

Function *DiffMarker::mark(Function *original, Function *patched) {
  Function::const_iterator BBL = original->begin(), BBLE = original->end();
  Function::const_iterator BBR = patched->begin(), BBRE = patched->end();
  do {
    int res = cmpBasicBlocks(&*BBL, &*BBR);

    ++BBL;
    ++BBR;
  } while (BBL != BBLE && BBR != BBRE);
  return patched;
}