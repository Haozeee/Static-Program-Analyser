#pragma once

#include <memory>
#include <string>
#include "source_processor/design_extractor/extractor/AbstractExtractor.h"
#include "source_processor/node/statement_node/ReadNode.h"
#include "source_processor/storage/EntityStore.h"

class EntityExtractor : public AbstractExtractor {
 private:
    std::shared_ptr<EntityStore> entityStore;
 public:
    explicit EntityExtractor(std::shared_ptr<EntityStore> entityStore);

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
    void extractName(std::string ident) override;
    void extractInteger(std::string integer) override;
};
