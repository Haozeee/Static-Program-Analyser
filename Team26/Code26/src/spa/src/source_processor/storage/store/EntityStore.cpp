#include "EntityStore.h"

#include <utility>

EntityStore::EntityStore(std::shared_ptr<WriteStorage> storage) {
    procedureManager = storage->getProcedureManager();
    statementManager = storage->getStmtManager();
    readManager = storage->getReadManager();
    printManager = storage->getPrintManager();
    assignManager = storage->getAssignManager();
    callManager = storage->getCallManager();
    whileManager = storage->getWhileManager();
    ifManager = storage->getIfManager();
    variableManager = storage->getVariableManager();
    constantManager = storage->getConstantManager();
}

void EntityStore::insertProcedure(std::shared_ptr<ProcedureNode> node) {
    procedureManager->insertEntity(node->procedureName);
}

void EntityStore::insertStatement(std::shared_ptr<StmtNode> node) {
    statementManager->insertEntity(node->stmtIndex);
}

void EntityStore::insertReadStatement(std::shared_ptr<ReadNode> node) {
    /**
     *  Read Statement
     *  1. Statement Index
     *  2. Variable Name
     * */
    readManager->insertEntity(node->stmtIndex);
    insertName(node->varName);
}

void EntityStore::insertPrintStatement(std::shared_ptr<PrintNode> node) {
    /**
     *  Print Statement
     *  1. Statement Index
     *  2. Variable Name
     * */
    printManager->insertEntity(node->stmtIndex);
    insertName(node->varName);
}

void EntityStore::insertAssignStatement(std::shared_ptr<AssignNode> node) {
    /**
     *  Print Statement
     *  1. Statement Index
     *  2. Variable Name
     * */
    assignManager->insertEntity(node->stmtIndex);
    insertName(node->varName);
}

void EntityStore::insertCallStatement(std::shared_ptr<CallNode> node) {
    // TBD
    callManager->insertEntity(node->stmtIndex);
}

void EntityStore::insertWhileStatement(std::shared_ptr<WhileNode> node) {
    /**
     *  While Statement
     *  1. Statement Index
     * */
    whileManager->insertEntity(node->stmtIndex);
}

void EntityStore::insertIfStatement(std::shared_ptr<IfNode> node) {
    /**
     *  If Statement
     *  1. Statement Index
     * */
    ifManager->insertEntity(node->stmtIndex);
}

void EntityStore::insertName(std::string &name) {
    variableManager->insertEntity(name);
}

void EntityStore::insertConstant(int &integer) {
    constantManager->insertEntity(integer);
}
