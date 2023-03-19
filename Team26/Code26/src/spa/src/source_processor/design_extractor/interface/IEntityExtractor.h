#pragma once

#include "source_processor/design_extractor/interface/statement_extractor/IStmtExtractor.h"
#include "source_processor/design_extractor/interface/IExtractor.h"

class IEntityExtractor : public IStmtExtractor, public IExtractor {
};
