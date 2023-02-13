#pragma once

#include <memory>
#include <string>
#include "source_processor/node/ProcedureNode.h"
#include "source_processor/node/statement_node/ReadNode.h"
#include "source_processor/node/statement_node/PrintNode.h"
#include "source_processor/node/statement_node/AssignNode.h"
#include "source_processor/node/statement_node/CallNode.h"
#include "source_processor/node/statement_node/WhileNode.h"
#include "source_processor/node/statement_node/IfNode.h"

class IEntityStore {
 public:
    virtual void insertProcedure(std::shared_ptr<ProcedureNode> node) = 0;
    virtual void insertStatement(std::shared_ptr<StmtNode> node) = 0;
    virtual void insertReadStatement(std::shared_ptr<ReadNode> node) = 0;
    virtual void insertPrintStatement(std::shared_ptr<PrintNode> node) = 0;
    virtual void insertAssignStatement(std::shared_ptr<AssignNode> node) = 0;
    virtual void insertCallStatement(std::shared_ptr<CallNode> node) = 0;
    virtual void insertWhileStatement(std::shared_ptr<WhileNode> node) = 0;
    virtual void insertIfStatement(std::shared_ptr<IfNode> node) = 0;
    virtual void insertName(std::string &name) = 0;
    virtual void insertConstant(int &integer) = 0;
};
