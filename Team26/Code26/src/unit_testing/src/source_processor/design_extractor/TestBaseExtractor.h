#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "source_processor/design_extractor/extractor/BaseExtractor.h"

class TestBaseExtractor : public BaseExtractor {
 public:
    int getStatementNumber() {
        return currentStmtNo;
    }
};
