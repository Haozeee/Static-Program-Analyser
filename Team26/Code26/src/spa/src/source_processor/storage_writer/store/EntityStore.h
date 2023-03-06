#pragma once

#include <vector>
#include <memory>
#include <string>
#include "source_processor/storage_writer/interface/IEntityStore.h"
#include "program_knowledge_base/StorageManager.h"

class EntityStore : public IEntityStore {
 private:
    std::shared_ptr<IWriteEntityManager<std::string>> procedureManager;
    std::shared_ptr<IWriteEntityManager<int>> statementManager;
    std::shared_ptr<IWriteEntityManager<int>> readManager;
    std::shared_ptr<IWriteEntityManager<int>> printManager;
    std::shared_ptr<IWriteEntityManager<int>> assignManager;
    std::shared_ptr<IWriteEntityManager<int>> callManager;
    std::shared_ptr<IWriteEntityManager<int>> whileManager;
    std::shared_ptr<IWriteEntityManager<int>> ifManager;
    std::shared_ptr<IWriteEntityManager<std::string>> variableManager;
    std::shared_ptr<IWriteEntityManager<int>> constantManager;
    std::shared_ptr<IWriteEntityManager<std::string>> readVariableManager;
    std::shared_ptr<IWriteEntityManager<std::string>> printVariableManager;

 public:
    explicit EntityStore(std::shared_ptr<WriteStorage> storage);

    void insertProcedure(std::shared_ptr<ProcedureNode> node) override;
    void insertStatement(std::shared_ptr<StmtNode> node)  override;
    void insertReadStatement(std::shared_ptr<ReadNode> node) override;
    void insertPrintStatement(std::shared_ptr<PrintNode> node) override;
    void insertAssignStatement(std::shared_ptr<AssignNode> node) override;
    void insertCallStatement(std::shared_ptr<CallNode> node) override;
    void insertWhileStatement(std::shared_ptr<WhileNode> node) override;
    void insertIfStatement(std::shared_ptr<IfNode> node) override;
    void insertVariableName(const std::string &name) override;
    void insertConstant(const int &integer) override;
};

