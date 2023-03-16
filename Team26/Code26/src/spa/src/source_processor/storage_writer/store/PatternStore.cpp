#include "PatternStore.h"
#include <utility>
#include "common/parser/ShuntingYardParser.h"

PatternStore::PatternStore(const std::shared_ptr<WriteStorage>& storage) {
    patternManager = storage->getAssignPatternManager();
    whileCondManager = storage->getWhileCondManager();
    ifCondManager = storage->getIfCondManager();
}

void PatternStore::insertExpressionPattern(std::shared_ptr<AssignNode> node) {
    patternManager->insertPattern(node->stmtIndex, node->varName,
                                  ShuntingYardParser::parse(node->exprNode->getRawString()));
}

void PatternStore::insertCondExpressionIfStatement(int stmtIndex, std::string variableName) {
    ifCondManager->insertRelationship(stmtIndex, variableName);
}

void PatternStore::insertCondExpressionWhileStatement(int stmtIndex, std::string variableName) {
    whileCondManager->insertRelationship(stmtIndex, variableName);
}

void PatternStore::invokePostReverseRelationship() {
    whileCondManager->setReverse();
    ifCondManager->setReverse();
}
