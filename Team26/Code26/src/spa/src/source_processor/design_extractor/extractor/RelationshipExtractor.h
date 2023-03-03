#pragma once
#include <memory>
#include <string>
#include <vector>
#include "source_processor/design_extractor/extractor/BaseExtractor.h"
#include "source_processor/storage_writer/interface/IRelationshipStore.h"
#include "source_processor/design_extractor/interface/IRelationshipExtractor.h"

class RelationshipExtractor : public BaseExtractor, IRelationshipExtractor {
 private:
    std::string currProcedureName;
    std::shared_ptr<IRelationshipStore> relationshipStore;
    std::vector<std::shared_ptr<std::vector<int>>> followsStack;
    std::vector<int> parentIndexStack;

    std::vector<int> statementStack;
    std::vector<int> whileStack;
    std::vector<int> ifStack;

    std::vector<int> ifThenStatementStack;
    std::vector<int> ifElseStatementStack;

    void insertFlow(int stmtIndex);
    void resetFlow(int stmtIndex);

    void insertUsesGroup(const std::shared_ptr<VariableNameNode>& node);
    void insertModifiesGroup(const std::shared_ptr<VariableNameNode>& node);
    void insertExprUsesGroup();

    void extractProcedure(std::shared_ptr<ProcedureNode> node) override;
    void extractStmtList(std::shared_ptr<StmtListNode> node) override;
    void extractStmt(std::shared_ptr<StmtNode> node) override;
    void extractRead(std::shared_ptr<ReadNode> node) override;
    void extractPrint(std::shared_ptr<PrintNode> node) override;
    void extractAssign(std::shared_ptr<AssignNode> node) override;
    void extractCall(std::shared_ptr<CallNode> node) override;
    void extractWhile(std::shared_ptr<WhileNode> node) override;
    void extractIf(std::shared_ptr<IfNode> node) override;
    void extractExpr(std::shared_ptr<ExprNode> node) override;
    void extractCondExpr(std::shared_ptr<CondExprNode> node) override;
 public:
    explicit RelationshipExtractor(std::shared_ptr<IRelationshipStore> storage);
};
