#pragma once

#include <memory>
#include <string>
#include "source_processor/node/ProgramNode.h"
#include "source_processor/node/ProcedureNode.h"
#include "source_processor/node/StmtListNode.h"
#include "source_processor/node/statement_node/ReadNode.h"
#include "source_processor/node/statement_node/PrintNode.h"
#include "source_processor/node/statement_node/AssignNode.h"
#include "source_processor/node/statement_node/CallNode.h"
#include "program_knowledge_base/WriteOnlyStorage.h"
#include "source_processor/node/CondExprNode.h"
#include "source_processor/node/statement_node/WhileNode.h"
#include "source_processor/node/statement_node/IfNode.h"

class AbstractExtractor {
 protected:
    int currentStmtNo = -1;
 public:
    AbstractExtractor();

    virtual void extractProgram(std::shared_ptr<ProgramNode> node);
    virtual void extractProcedure(std::shared_ptr<ProcedureNode> node);
    virtual void extractStmtList(std::shared_ptr<StmtListNode> node);
    virtual void extractStmt(std::shared_ptr<StmtNode> node);
    virtual void extractRead(std::shared_ptr<ReadNode> node) = 0;
    virtual void extractPrint(std::shared_ptr<PrintNode> node) = 0;
    virtual void extractAssign(std::shared_ptr<AssignNode> node) = 0;
    virtual void extractCall(std::shared_ptr<CallNode> node) = 0;
    virtual void extractIf(std::shared_ptr<IfNode> node) = 0;
    virtual void extractWhile(std::shared_ptr<WhileNode> node) = 0;
    virtual void extractCondExpr(std::shared_ptr<CondExprNode> node);
    virtual void extractExpr(std::shared_ptr<ExprNode> node);
};
