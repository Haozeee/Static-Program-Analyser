#pragma once

#include "source_processor/design_extractor/extractor/AbstractSyntaxTreeExtractor.h"

class EntityExtractor : public AbstractSyntaxTreeExtractor {
 public:
    explicit EntityExtractor(std::shared_ptr<WriteOnlyStorage> storage);
    void extractProcedure(std::shared_ptr<ProcedureNode> node) override;
    void extractStmtList(std::shared_ptr<StmtListNode> node) override;
    void extractStmt(std::shared_ptr<StmtNode> node) override;
    void extractRead() override;
    void extractIf() override;
    void extractWhile() override;
    void extractCondExpr() override;
    void extractExpr() override;
    void extractPrint() override;
    void extractAssign() override;
    void extractCall() override;
};
