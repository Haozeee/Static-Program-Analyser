#include "StmtNode.h"

StmtNode::StmtNode(int stmtIndex, StmtType stmtType) : stmtIndex(stmtIndex), stmtType(stmtType) {}

void StmtNode::evaluatePattern(IPatternExtractor &extractor) {
    throw new SourceExtractorException(BaseExtractorNotSupportedEvaluationExceptionMessage);
}
