#include "PatternStore.h"

#include <utility>

PatternStore::PatternStore(std::shared_ptr<WriteStorage> storage) {
    patternManager = storage->getPatternManager();
    whileCondManager = storage->getWhileCondManager();
    ifCondManager = storage->getIfCondManager();
}

void PatternStore::insertExpressionPattern(std::shared_ptr<AssignNode> node) {
    patternManager->insertPattern(node->stmtIndex, node->varName, node->exprNode->getRawString());
}

void PatternStore::insertCondExpressionIfStatement(int stmtIndex, std::string variableName) {
    ifCondManager->insertRelationship(stmtIndex, variableName);
}

void PatternStore::insertCondExpressionWhileStatement(int stmtIndex, std::string variableName) {
    whileCondManager->insertRelationship(stmtIndex, variableName);

}
