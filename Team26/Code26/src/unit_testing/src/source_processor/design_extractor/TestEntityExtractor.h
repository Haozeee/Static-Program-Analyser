#pragma once

#include "source_processor/storage/interface/IEntityStore.h"
#include <unordered_set>
#include <set>
#include <memory>

class MockEntityStore : public IEntityStore {
public:
    std::unordered_set<std::shared_ptr<ProcedureNode>> procedureSet;
    std::set<std::shared_ptr<StmtNode>> stmtSet;
    std::unordered_set<std::shared_ptr<ReadNode>> readSet;
    std::unordered_set<std::shared_ptr<PrintNode>> printSet;
    std::unordered_set<std::shared_ptr<AssignNode>> assignSet;
    std::unordered_set<std::shared_ptr<CallNode>> callSet;
    std::unordered_set<std::shared_ptr<WhileNode>> whileSet;
    std::unordered_set<std::shared_ptr<IfNode>> ifSet;
    std::unordered_set<std::string> variableSet;
    std::unordered_set<int> constantSet;

    void insertProcedure(std::shared_ptr<ProcedureNode> node) override {
        procedureSet.insert(node);
    };

    void insertStatement(std::shared_ptr<StmtNode> node) override {
        stmtSet.insert(node);
    };

    void insertReadStatement(std::shared_ptr<ReadNode> node) override {
        readSet.insert(node);
    };

    void insertPrintStatement(std::shared_ptr<PrintNode> node) override {
        printSet.insert(node);
    };
    void insertAssignStatement(std::shared_ptr<AssignNode> node) override {
        assignSet.insert(node);
    };

    void insertCallStatement(std::shared_ptr<CallNode> node) override {
        callSet.insert(node);
    };

    void insertWhileStatement(std::shared_ptr<WhileNode> node) override {
        whileSet.insert(node);
    };

    void insertIfStatement(std::shared_ptr<IfNode> node) override {
        ifSet.insert(node);
    };

    void insertName(const std::string &name) override {
        variableSet.insert(name);
    };

    void insertConstant(const int &integer) override {
        constantSet.insert(integer);
    };

};