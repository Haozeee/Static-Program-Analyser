#pragma once

#include <memory>
#include <string>
#include "source_processor/design_extractor/extractor/BaseExtractor.h"
#include "source_processor/design_extractor/interface/IEntityExtractor.h"
#include "source_processor/storage_writer/interface/IEntityStore.h"
#include "source_processor/storage_writer/interface/IPatternStore.h"

class EntityExtractor : public BaseExtractor, IEntityExtractor {
 private:
    std::shared_ptr<IEntityStore> entityStore;
    std::shared_ptr<IPatternStore> patternStore;

    void insertExprEntities();

    void extractProcedure(std::shared_ptr<ProcedureNode> node) override;
    void extractStmt(std::shared_ptr<StmtNode> node) override;
    void extractRead(std::shared_ptr<ReadNode> node) override;
    void extractPrint(std::shared_ptr<PrintNode> node) override;
    void extractAssign(std::shared_ptr<AssignNode> node) override;
    void extractIf(std::shared_ptr<IfNode> node) override;
    void extractWhile(std::shared_ptr<WhileNode> node) override;
    void extractCall(std::shared_ptr<CallNode> node) override;
    void extractExpr(std::shared_ptr<ExprNode> node) override;
    void extractCondExpr(std::shared_ptr<CondExprNode> node) override;

 public:
    explicit EntityExtractor(std::shared_ptr<IEntityStore> entityStore, std::shared_ptr<IPatternStore> patternStore);
    void extractProgram(std::shared_ptr<ProgramNode> node) override;
};
