#pragma once

#include <vector>
#include <memory>
#include <string>
#include "source_processor/storage/interface/IEntityStore.h"
#include "program_knowledge_base/WriteOnlyStorage.h"

class EntityStore : public IEntityStore {
 private:
    std::shared_ptr<WriteOnlyEntityManager<std::string>> procedureManager;
    std::shared_ptr<WriteOnlyEntityManager<int>> statementManager;
    std::shared_ptr<WriteOnlyEntityManager<int>> readManager;
    std::shared_ptr<WriteOnlyEntityManager<int>> printManager;
    std::shared_ptr<WriteOnlyEntityManager<int>> assignManager;
    std::shared_ptr<WriteOnlyEntityManager<int>> callManager;
    std::shared_ptr<WriteOnlyEntityManager<int>> whileManager;
    std::shared_ptr<WriteOnlyEntityManager<int>> ifManager;
    std::shared_ptr<WriteOnlyEntityManager<std::string>> variableManager;
    std::shared_ptr<WriteOnlyEntityManager<int>> constantManager;


 public:
    explicit EntityStore(std::shared_ptr<WriteOnlyStorage> storage);

    void insertProcedure(std::shared_ptr<ProcedureNode> node) override;
    void insertStatement(std::shared_ptr<StmtNode> node)  override;
    void insertReadStatement(std::shared_ptr<ReadNode> node) override;
    void insertPrintStatement(std::shared_ptr<PrintNode> node) override;
    void insertAssignStatement(std::shared_ptr<AssignNode> node) override;
    void insertCallStatement(std::shared_ptr<CallNode> node) override;
    void insertWhileStatement(std::shared_ptr<WhileNode> node) override;
    void insertIfStatement(std::shared_ptr<IfNode> node) override;
    void insertName(const std::string &name) override;
    void insertConstant(const int &integer) override;
};

