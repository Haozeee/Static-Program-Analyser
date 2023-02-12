#pragma once

#include <memory>
#include <string>
#include "source_processor/design_extractor/extractor/BaseExtractor.h"
#include "source_processor/node/statement_node/ReadNode.h"
#include "source_processor/storage/EntityStore.h"
#include "source_processor/design_extractor/interface/IEntityExtractor.h"

class EntityExtractor : public BaseExtractor, IEntityExtractor {
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
    void extractIf(std::shared_ptr<IfNode> node) override;
    void extractWhile(std::shared_ptr<WhileNode> node) override;
    void extractCall(std::shared_ptr<CallNode> node) override;
};
