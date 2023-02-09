#include "EntityStore.h"

EntityStore::EntityStore(std::shared_ptr<WriteOnlyStorage> storage) : entityStorage(storage) {}

void EntityStore::insertProcedure(std::shared_ptr<ProcedureNode> node) {
    // TODO(zhengteck): Implementation fo checking dup procedure name or check with PKB team
    entityStorage->getProcedureManager()->insertEntity(node->procedureName);
}

void EntityStore::insertStatement(std::shared_ptr<StmtNode> node) {
    entityStorage->getStmtManager()->insertEntity(node->stmtIndex);
}

void EntityStore::insertReadStatement(std::shared_ptr<ReadNode> node) {
    entityStorage->getReadManager()->insertEntity(node->stmtIndex);
    entityStorage->getVariableManager()->insertEntity(node->varName);
}

void EntityStore::insertPrintStatement(std::shared_ptr<PrintNode> node) {
    entityStorage->getPrintManager()->insertEntity(node->stmtIndex);
    entityStorage->getVariableManager()->insertEntity(node->varName);
}

void EntityStore::insertAssignStatement(std::shared_ptr<AssignNode> node) {
    entityStorage->getAssignManager()->insertEntity(node->stmtIndex);
}

void EntityStore::insertCallStatement(std::shared_ptr<CallNode> node) {
    entityStorage->getCallManager()->insertEntity(node->stmtIndex);
}

void EntityStore::insertWhileStatement(std::shared_ptr<WhileNode> node) {
}

void EntityStore::insertIfStatement(std::shared_ptr<IfNode> node) {
}

void EntityStore::insertName(std::string &name) {
    entityStorage->getVariableManager()->insertEntity(name);
}

void EntityStore::insertConstant(std::string &integer) {
    entityStorage->getConstantManager()->insertEntity(stoi(integer));
}
