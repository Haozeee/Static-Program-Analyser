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
    /**
     *  Read Statement
     *  1. Statement Index
     *  2. Variable Name
     * */
    entityStorage->getReadManager()->insertEntity(node->stmtIndex);
    insertName(node->varName);
}

void EntityStore::insertPrintStatement(std::shared_ptr<PrintNode> node) {
    /**
     *  Print Statement
     *  1. Statement Index
     *  2. Variable Name
     * */
    entityStorage->getPrintManager()->insertEntity(node->stmtIndex);
    insertName(node->varName);
}

void EntityStore::insertAssignStatement(std::shared_ptr<AssignNode> node) {
    /**
     *  Print Statement
     *  1. Statement Index
     *  2. Variable Name
     * */
    entityStorage->getAssignManager()->insertEntity(node->stmtIndex);
    insertName(node->varName);
}

void EntityStore::insertCallStatement(std::shared_ptr<CallNode> node) {
    // TBD
    entityStorage->getCallManager()->insertEntity(node->stmtIndex);
}

void EntityStore::insertWhileStatement(std::shared_ptr<WhileNode> node) {
    /**
     *  While Statement
     *  1. Statement Index
     * */
    entityStorage->getWhileManager()->insertEntity(node->stmtIndex);
}

void EntityStore::insertIfStatement(std::shared_ptr<IfNode> node) {
    /**
     *  If Statement
     *  1. Statement Index
     * */
    entityStorage->getIfManager()->insertEntity(node->stmtIndex);
}

void EntityStore::insertName(std::string &name) {
    entityStorage->getVariableManager()->insertEntity(name);
}

void EntityStore::insertConstant(int &integer) {
    entityStorage->getConstantManager()->insertEntity(integer);
}
