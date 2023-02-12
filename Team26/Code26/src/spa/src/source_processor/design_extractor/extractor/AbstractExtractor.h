#pragma once

#include <memory>
#include <string>
#include "source_processor/node/ProgramNode.h"
#include "source_processor/node/ProcedureNode.h"
#include "source_processor/node/StmtListNode.h"

#include "program_knowledge_base/WriteOnlyStorage.h"
#include "source_processor/node/CondExprNode.h"


class AbstractExtractor {
 protected:
    int currentStmtNo = -1;
 public:
    AbstractExtractor();

    /**
     * General looping of nodes that contains statement lists.
     * */
    virtual void extractProgram(std::shared_ptr<ProgramNode> node);
    virtual void extractProcedure(std::shared_ptr<ProcedureNode> node);
    virtual void extractStmtList(std::shared_ptr<StmtListNode> node);
    virtual void extractStmt(std::shared_ptr<StmtNode> node);

    /**
     * For expressions and conditional expression.
     * */
    virtual void extractExpr(std::shared_ptr<ExprNode> node);
    virtual void extractCondExpr(std::shared_ptr<CondExprNode> node);
};
