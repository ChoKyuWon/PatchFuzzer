#include "llvm/Transforms/Utils/FunctionComparator.h"
#include <vector>

using namespace llvm;

class DiffMarker : public FunctionComparator {
private:
  void traverse(std::vector<BasicBlock*> LeftList, std::vector<BasicBlock*> RightList);
public:
  DiffMarker(Function *F1, Function *F2,
                 GlobalNumberState *GN)
        : FunctionComparator(F1, F2, GN) {
  }
  bool cmpBasicBlocks(const BasicBlock* BBL, const BasicBlock* BBR);
  Function *mark();
};

void tmp_marking(Function& f, int w);