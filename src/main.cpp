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

#include "DiffMarker.h"

#include <memory>
#include <iostream>


using namespace llvm;

static cl::opt<std::string>
    originalFileName(cl::Positional, cl::desc("Bitcode file"), cl::Required);
static cl::opt<std::string>
    patchedFileName(cl::Positional, cl::desc("Bitcode file"), cl::Required);

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
  GlobalNumberState GN;
  DiffMarker diff(original->getFunction("main"), patched->getFunction("main"), &GN);
  diff.mark();
  patched->print(errs(), nullptr);
  return 0;
}