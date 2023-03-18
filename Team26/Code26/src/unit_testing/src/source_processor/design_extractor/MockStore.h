#pragma once

#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "source_processor/storage_writer/interface/IEntityStore.h"
#include "source_processor/storage_writer/interface/IRelationshipStore.h"
#include "source_processor/storage_writer/interface/IPatternStore.h"

class MockEntityStore : public IEntityStore {
 public:
    std::unordered_set<std::shared_ptr<ProcedureNode>> procedureSet;
    std::set<int> stmtSet;
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
    }

    void insertReadStatement(std::shared_ptr<ReadNode> node) override {
        readSet.insert(node);
    }

    void insertPrintStatement(std::shared_ptr<PrintNode> node) override {
        printSet.insert(node);
    }

    void insertAssignStatement(std::shared_ptr<AssignNode> node) override {
        assignSet.insert(node);
    }

    void insertCallStatement(std::shared_ptr<CallNode> node) override {
        callSet.insert(node);
    }

    void insertWhileStatement(std::shared_ptr<WhileNode> node) override {
        whileSet.insert(node);
    }

    void insertIfStatement(std::shared_ptr<IfNode> node) override {
        ifSet.insert(node);
    }

    void insertVariableName(const std::string &name) override {
        variableSet.insert(name);
    }

    void insertConstant(const int &integer) override {
        constantSet.insert(integer);
    }

    void insertStatement(int stmtIndex) override {
        stmtSet.insert(stmtIndex);
    }
};

class MockRelationshipStore : public IRelationshipStore {
 public:
    std::unordered_map<int, std::unordered_set<int>> followsStore;
    std::unordered_map<int, std::unordered_set<int>> parentsStore;

    std::unordered_map<int, std::unordered_set<int>> followsTStore;
    std::unordered_map<int, std::unordered_set<int>> parentsTStore;

    std::unordered_map<int, std::unordered_set<std::string>> usesSStore;
    std::unordered_map<int, std::unordered_set<std::string>> modifiesSStore;

    std::unordered_map<std::string, std::unordered_set<std::string>> usesPStore;
    std::unordered_map<std::string, std::unordered_set<std::string>> modifiesPStore;

    std::unordered_map<int, std::unordered_set<int>> nextStore;

    std::unordered_map<int, std::unordered_set<std::string>> callSStore;
    std::unordered_map<std::string, std::unordered_set<std::string>> callPStore;
    std::unordered_map<std::string, std::unordered_set<std::string>> callsTStore;

    void insertFollowsRelationship(const int &previousStmtNo, const int &currentStmtNo) override {
        followsStore[previousStmtNo].insert(currentStmtNo);
    }

    void insertParentsRelationship(const int &parentStmtNo, const int &childStmtNo) override {
        parentsStore[parentStmtNo].insert(childStmtNo);
    }

    void insertFollowsTRelationship(const int &previousStmtNo, const int &currentStmtNo) override {
        followsTStore[previousStmtNo].insert(currentStmtNo);
    }

    void insertParentsTRelationship(const int &parentStmtNo, const int &childStmtNo) override {
        parentsTStore[parentStmtNo].insert(childStmtNo);
    }

    void insertUsesSRelationship(const int &stmtNo, const std::string &variableName) override {
        usesSStore[stmtNo].insert(variableName);
    }

    void insertModifiesSRelationship(const int &stmtNo, const std::string &variableName) override {
        modifiesSStore[stmtNo].insert(variableName);
    }

    void insertUsesPRelationship(const std::string  &procedureName, const std::string &variableName) override {
        usesPStore[procedureName].insert(variableName);
    }

    void insertModifiesPRelationship(const std::string  &procedureName, const std::string &variableName) override {
        modifiesPStore[procedureName].insert(variableName);
    }

    void insertCallsRelationship(const int &stmtNo, const std::string &callerName, const std::string
    &calleeName) override {
        callSStore[stmtNo].insert(calleeName);
        callPStore[callerName].insert(calleeName);
    }

    void insertNextRelationship(int previousStmtNo, int currStmtNo) override {
        nextStore[previousStmtNo].insert(currStmtNo);
    }

    void insertCallsTRelationship(std::string caller, std::string callee) override {
        callsTStore[caller].insert(callee);
    }

    void invokePostReverseRelationship() override {
    }

    void invokePreReverseRelationship() override {
    }

    std::unordered_map<std::string, std::unordered_set<std::string>> getCallsPReversedRelationship() override {
    };

    std::unordered_map<std::string, std::unordered_set<std::string>> getCallsTRelationship() override {
        return callsTStore;
    };

    std::unordered_map<std::string, std::unordered_set<std::string>> getModifiesPRelationship() override {
        return modifiesPStore;
    };

    std::unordered_map<std::string, std::unordered_set<std::string>> getUsesPRelationship() override {
        return usesPStore;
    };

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
    std::unordered_map<int, std::unordered_set<std::string>> ifCondManager;
    std::unordered_map<int, std::unordered_set<std::string>> whileCondManager;

    void insertExpressionPattern(std::shared_ptr<AssignNode> node) override {
        assignStore.insert(node);
    }

    void insertCondExpressionIfStatement(int stmtIndex, std::string variableName) override {
        ifCondManager[stmtIndex].insert(variableName);
    }

    void insertCondExpressionWhileStatement(int stmtIndex, std::string variableName) override {
        whileCondManager[stmtIndex].insert(variableName);
    }

    void invokePostReversePattern() override {
    }
};
