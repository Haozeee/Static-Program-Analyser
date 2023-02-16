#pragma once

#include "source_processor/design_extractor/interface/statement_extractor/IAssignExtractor.h"
#include "source_processor/design_extractor/interface/statement_extractor/IWhileExtractor.h"
#include "source_processor/design_extractor/interface/statement_extractor/IIfExtractor.h"

class IPatternExtractor : public IAssignExtractor, public  IWhileExtractor, public IIfExtractor {
};
