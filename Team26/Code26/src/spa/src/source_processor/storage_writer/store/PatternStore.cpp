#include "PatternStore.h"
#include <utility>

PatternStore::PatternStore(const std::shared_ptr<WriteStorage>& storage) {
    patternManager = storage->getAssignPatternManager();
    whileCondManager = storage->getWhileCondManager();
    ifCondManager = storage->getIfCondManager();
}

void PatternStore::insertExpressionPattern(std::shared_ptr<AssignNode> node) {
    patternManager->insertPattern(node->stmtIndex, node->varName, node->shutNode);
}

void PatternStore::insertCondExpressionIfStatement(int stmtIndex, std::string variableName) {
    ifCondManager->insertRelationship(stmtIndex, variableName);
}

void PatternStore::insertCondExpressionWhileStatement(int stmtIndex, std::string variableName) {
    whileCondManager->insertRelationship(stmtIndex, variableName);
}

void PatternStore::invokePostReversePattern() {
    whileCondManager->setReverse();
    ifCondManager->setReverse();
}
