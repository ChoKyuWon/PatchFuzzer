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

#include <memory>

using namespace llvm;

static cl::opt<std::string>
    originalFileName(cl::Positional, cl::desc("Bitcode file"), cl::Required);
static cl::opt<std::string>
    patchedFileName(cl::Positional, cl::desc("Bitcode file"), cl::Required);

// int cmpBasicBlocks(const BasicBlock *BBL,
//                                         const BasicBlock *BBR) const {
//    BasicBlock::const_iterator InstL = BBL->begin(), InstLE = BBL->end();
//    BasicBlock::const_iterator InstR = BBR->begin(), InstRE = BBR->end();

//    do {
//      bool needToCmpOperands = true;
//      if (int Res = cmpOperations(&*InstL, &*InstR, needToCmpOperands))
//        return Res;
//      if (needToCmpOperands) {
//        assert(InstL->getNumOperands() == InstR->getNumOperands());

//        for (unsigned i = 0, e = InstL->getNumOperands(); i != e; ++i) {
//          Value *OpL = InstL->getOperand(i);
//          Value *OpR = InstR->getOperand(i);
//          if (int Res = cmpValues(OpL, OpR))
//            return Res;
//          // cmpValues should ensure this is true.
//          assert(cmpTypes(OpL->getType(), OpR->getType()) == 0);
//        }
//      }

//      ++InstL;
//      ++InstR;
//    } while (InstL != InstLE && InstR != InstRE);

//    if (InstL != InstLE && InstR == InstRE)
//      return 1;
//    if (InstL == InstLE && InstR != InstRE)
//      return -1;
//    return 0;
//  }

// int isDiffBB(BasicBlock* b1, BasicBlock* b2) {
//     if(b1->size() != b2->size())
//         return -1;
//     auto inst2 = b2->begin();
//     for (auto inst1 = b1->begin(), e = b1->end() ; inst1!=e; ++inst1) {
//         if(inst1 != inst2){
//             errs() << inst1->getOpcodeName() << " " << inst2->getOpcodeName()
//             << "\n"; return -2;
//         }
//         ++inst2;
//     }
//     return 0;
// }

int main(int argc, char **argv) {
  cl::ParseCommandLineOptions(argc, argv, "LLVM hello world\n");
  LLVMContext context;

  ErrorOr<std::unique_ptr<MemoryBuffer>> mb =
      MemoryBuffer::getFile(originalFileName);
  if (std::error_code ec = mb.getError()) {
    errs() << ec.message();
    return -1;
  }
  auto m_original = parseBitcodeFile(mb->get()->getMemBufferRef(), context);
  if (std::error_code ec = errorToErrorCode(m_original.takeError())) {
    errs() << "Unable to read bitcode file.." << ec.message();
  }

  mb = MemoryBuffer::getFile(patchedFileName);
  if (std::error_code ec = mb.getError()) {
    errs() << ec.message();
    return -1;
  }
  auto m_patched = parseBitcodeFile(mb->get()->getMemBufferRef(), context);
  if (std::error_code ec = errorToErrorCode(m_patched.takeError())) {
    errs() << "Unable to read bitcode file.." << ec.message();
  }

  auto original = std::move(m_original.get());
  auto patched = std::move(m_patched.get());
  if (original == patched)
    errs() << "Something wrong I can feel it\n";
  BasicBlock *b1 = &original->getFunction("main")->getEntryBlock();
  BasicBlock *b2 = &patched->getFunction("main")->getEntryBlock();
  return 0;
}