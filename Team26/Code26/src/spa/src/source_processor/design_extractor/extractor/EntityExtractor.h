#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include "source_processor/design_extractor/extractor/BaseExtractor.h"
#include "source_processor/design_extractor/interface/IEntityExtractor.h"
#include "source_processor/storage_writer/interface/IEntityStore.h"
#include "source_processor/storage_writer/interface/IPatternStore.h"

class EntityExtractor : public BaseExtractor, public IEntityExtractor {
 private:
    std::shared_ptr<IEntityStore> entityStore;
    std::shared_ptr<IPatternStore> patternStore;

    void extractProcedure(const std::shared_ptr<ProcedureNode>& node) override;
    void extractStmt(const std::shared_ptr<StmtNode>& node) override;
    void extractRead(std::shared_ptr<ReadNode> node) override;
    void extractPrint(std::shared_ptr<PrintNode> node) override;
    void extractAssign(std::shared_ptr<AssignNode> node) override;
    void extractIf(std::shared_ptr<IfNode> node) override;
    void extractWhile(std::shared_ptr<WhileNode> node) override;
    void extractCall(std::shared_ptr<CallNode> node) override;

    void insertConstants(const std::unordered_set<int>& constants);

 public:
    ~EntityExtractor() override = default;;
    explicit EntityExtractor(std::shared_ptr<IEntityStore> entityStore, std::shared_ptr<IPatternStore> patternStore);
    void extractProgram(const std::shared_ptr<ProgramNode>& node) override;
};
