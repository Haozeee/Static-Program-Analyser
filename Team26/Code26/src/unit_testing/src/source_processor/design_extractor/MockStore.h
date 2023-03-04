#pragma once

#include "source_processor/storage_writer/interface/IEntityStore.h"
#include "source_processor/storage_writer/interface/IRelationshipStore.h"
#include "source_processor/storage_writer/interface/IPatternStore.h"
#include <unordered_set>
#include <set>
#include <unordered_map>
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

    void insertVariableName(const std::string &name) override {
        variableSet.insert(name);
    };

    void insertConstant(const int &integer) override {
        constantSet.insert(integer);
    };

};

class MockRelationshipStore : public IRelationshipStore {
 public:
    std::unordered_map<int, std::unordered_set<int>> followsStore;
    std::unordered_map<int, std::unordered_set<int>> parentsStore;
    std::unordered_map<int, std::unordered_set<std::string>> usesSStore;
    std::unordered_map<int, std::unordered_set<std::string>> modifiesSStore;
    std::unordered_map<int, std::unordered_set<int>> nextStore;

    void insertFollowsRelationship(const int &previousStmtNo, const int &currentStmtNo) override {
        followsStore[previousStmtNo].insert(currentStmtNo);
    };

    void insertParentsRelationship(const int &parentStmtNo, const int &childStmtNo) override {
        parentsStore[parentStmtNo].insert(childStmtNo);
    };

    void insertUsesSRelationship(const int &stmtNo, const std::string &variableName) override {
        usesSStore[stmtNo].insert(variableName);
    };

    void insertModifiesSRelationship(const int &stmtNo, const std::string &variableName) override {
        modifiesSStore[stmtNo].insert(variableName);
    };

    void insertUsesPRelationship(std::string  &procedureName, const std::string &variableName) override {
        //TODO(zt): Sprint 3
    };
    void insertModifiesPRelationship(std::string  &procedureName, const std::string &variableName) override {
        //TODO(zt): Sprint 3
    }

    void insertCallsRelationship(const int &stmtNo, const std::string &callerName, const std::string
    &calleeName) {

    };
    void insertNextRelationship(int previousStmtNo, int currStmtNo) override {
        nextStore[previousStmtNo].insert(currStmtNo);
    }

    bool findFollows(int x, int y) {
        auto curr = followsStore.find(x);
        return curr != followsStore.end() && curr->second.find(y) != curr->second.end();
    }

    bool findParents(int x, int y) {
        auto curr = parentsStore.find(x);
        return curr != parentsStore.end() && curr->second.find(y) != curr->second.end();
    }

    bool findUseS(int x, std::string y) {
        auto curr = usesSStore.find(x);
        return curr != usesSStore.end() && curr->second.find(y) != curr->second.end();
    }

    bool findModifiesS(int x, std::string y) {
        auto curr = modifiesSStore.find(x);
        return curr != modifiesSStore.end() && curr->second.find(y) != curr->second.end();
    }
};

class MockPatternStore : public IPatternStore {
 public:
    std::set<std::shared_ptr<AssignNode>> assignStore;
    void insertExpressionPattern(std::shared_ptr<AssignNode> node) {
        assignStore.insert(node);
    };
};
