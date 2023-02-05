#include "EntityExtractor.h"

EntityExtractor::EntityExtractor(std::shared_ptr<WriteOnlyStorage> storage) : AbstractSyntaxTreeExtractor(storage) {}

void EntityExtractor::extractProcedure(std::shared_ptr<ProcedureNode> node) {
    storage->getProcedureManager()->insertEntity(node->procedureName);
    AbstractSyntaxTreeExtractor::extractProcedure(node);
}

void EntityExtractor::extractStmtList(std::shared_ptr<StmtListNode> node) {
    AbstractSyntaxTreeExtractor::extractStmtList(node);
}

void EntityExtractor::extractStmt(std::shared_ptr<StmtNode> node) {
    AbstractSyntaxTreeExtractor::extractStmt(node);
    storage->getStmtManager()->insertEntity(currentStmtNo);
}

void EntityExtractor::extractRead(std::shared_ptr<ReadNode> node) {
    storage->getReadManager()->insertEntity(currentStmtNo);
    storage->getVariableManager()->insertEntity(node->varName);
}

void EntityExtractor::extractPrint(std::shared_ptr<PrintNode> node) {
    storage->getPrintManager()->insertEntity(currentStmtNo);
    storage->getVariableManager()->insertEntity(node->varName);
}

void EntityExtractor::extractCall(std::shared_ptr<CallNode> node) {
    storage->getCallManager()->insertEntity(currentStmtNo);
}

void EntityExtractor::extractAssign(std::shared_ptr<AssignNode> node) {

}

void EntityExtractor::extractIf() {
}

void EntityExtractor::extractWhile() {
}

void EntityExtractor::extractCondExpr() {
}

void EntityExtractor::extractExpr() {
}

