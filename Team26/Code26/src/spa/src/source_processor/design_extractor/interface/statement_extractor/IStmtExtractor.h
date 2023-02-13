#pragma once

#include "IReadExtractor.h"
#include "IPrintExtractor.h"
#include "IAssignExtractor.h"
#include "IIfExtractor.h"
#include "IWhileExtractor.h"
#include "ICallExtractor.h"

class IStmtExtractor : public IReadExtractor, public IPrintExtractor, public IAssignExtractor, public IIfExtractor,
        public IWhileExtractor, public ICallExtractor {
};
