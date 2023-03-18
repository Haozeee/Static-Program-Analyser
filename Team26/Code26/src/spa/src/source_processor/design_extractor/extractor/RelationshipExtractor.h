#pragma once
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "source_processor/design_extractor/extractor/BaseExtractor.h"
#include "source_processor/storage_writer/interface/IRelationshipStore.h"
#include "source_processor/design_extractor/interface/IRelationshipExtractor.h"
#include "program_knowledge_base/StorageManager.h"

class RelationshipExtractor : public BaseExtractor, IRelationshipExtractor {
 private:
    std::shared_ptr<IRelationshipStore> relationshipStore;

    // Relationships
    std::string currProcedureName;

    std::unordered_map<std::string, std::unordered_set<std::string>> usesPRelationships;
    std::unordered_map<std::string, std::unordered_set<std::string>> modifiesPRelationships;
    std::unordered_map<std::string, std::unordered_set<std::string>> callPReversedRelationships;

    std::unordered_map<std::string, int> procedureUniqueCallCount;
    std::unordered_map<std::string, std::unique_ptr<std::unordered_set<int>>> procedureCalledList;

    // Follows, Parents
    std::vector<std::shared_ptr<std::vector<int>>> followsStack;
    std::vector<int> parentIndexStack;

    // Next Statements
    std::vector<int> statementStack;
    std::vector<int> whileStack;
    std::vector<int> ifStack;

    void insertFlow(int stmtIndex);
    void resetFlow(int stmtIndex);

    // Uses Statement
    void insertUsesGroup(const std::shared_ptr<VariableNameNode>& node);
    void insertModifiesGroup(const std::shared_ptr<VariableNameNode>& node);
    void insertExprUsesGroup(const std::unordered_set<std::string>& exprVariableList);
    void extractCondExpr(const std::shared_ptr<CondExprNode>& node);

    // Calls Statement
    void interlinkRelationships(const std::string& procedureName);
    void interlinkSRelationships(const std::string& procedureName);
    void interlinkPRelationships(const std::string& procedureName);

    void extractProcedure(const std::shared_ptr<ProcedureNode>& node) override;
    void extractStmtList(const std::shared_ptr<StmtListNode>& node) override;
    void extractStmt(const std::shared_ptr<StmtNode>& node) override;
    void extractRead(std::shared_ptr<ReadNode> node) override;
    void extractPrint(std::shared_ptr<PrintNode> node) override;
    void extractAssign(std::shared_ptr<AssignNode> node) override;
    void extractCall(std::shared_ptr<CallNode> node) override;
    void extractWhile(std::shared_ptr<WhileNode> node) override;
    void extractIf(std::shared_ptr<IfNode> node) override;

 public:
    explicit RelationshipExtractor(std::shared_ptr<IRelationshipStore> relationshipStore);
    void extractProgram(const std::shared_ptr<ProgramNode>& node) override;
};
