#pragma once

#include <memory>
#include "source_processor/design_extractor/extractor/AbstractSyntaxTreeExtractor.h"
#include "source_processor/node/statement_node/ReadNode.h"

class EntityExtractor : public AbstractSyntaxTreeExtractor {
 public:
    explicit EntityExtractor(std::shared_ptr<WriteOnlyStorage> storage);
    void extractProcedure(std::shared_ptr<ProcedureNode> node) override;
    void extractStmtList(std::shared_ptr<StmtListNode> node) override;
    void extractStmt(std::shared_ptr<StmtNode> node) override;
    void extractRead(std::shared_ptr<ReadNode> node) override;
    void extractPrint(std::shared_ptr<PrintNode> node) override;
    void extractAssign(std::shared_ptr<AssignNode> node) override;
    void extractCall(std::shared_ptr<CallNode> node) override;
    void extractIf() override;
    void extractWhile() override;
    void extractCondExpr() override;
    void extractExpr() override;

};
