#include "llvm/Transforms/Utils/FunctionComparator.h"

using namespace llvm;

class DiffMarker : public FunctionComparator {
public:
  DiffMarker(Function *F1, Function *F2,
                 GlobalNumberState *GN)
        : FunctionComparator(F1, F2, GN) {
  }
  Function *mark();
};