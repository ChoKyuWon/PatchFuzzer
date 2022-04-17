#include "llvm/Transforms/Utils/FunctionComparator.h"

using namespace llvm;

class DiffMarker : public FunctionComparator {
public:
    DiffMarker(const Function *F1, const Function *F2,
                 GlobalNumberState *GN)
        : FunctionComparator(F1, F2, GN) {
  }
  Function *mark();
};