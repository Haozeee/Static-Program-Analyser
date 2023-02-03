#pragma once

#include <memory>
#include "source_processor/node/ProgramNode.h"
#include "source_processor/node/ProcedureNode.h"
#include "source_processor/node/StmtListNode.h"

class AbstractSyntaxTreeExtractor {
 protected:
    int stmtNo = 0;
 public:
    virtual void extractProgram(std::shared_ptr<ProgramNode> node);
    virtual void extractProcedure(std::shared_ptr<ProcedureNode> node);
    virtual void extractStmtList(std::shared_ptr<StmtListNode> node);
    virtual void extractStmt(std::shared_ptr<StmtNode> node);
    virtual void extractRead() = 0;
    virtual void extractPrint() = 0;
    virtual void extractAssign() = 0;
    virtual void extractCall() = 0;
    virtual void extractIf() = 0;
    virtual void extractWhile() = 0;
    virtual void extractCondExpr() = 0;
    virtual void extractExpr() = 0;
};
