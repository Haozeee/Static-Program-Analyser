#pragma once

#include <memory>
#include <string>
#include <vector>
#include "source_processor/exception/SourceException.h"
#include "source_processor/node/ProgramNode.h"
#include "source_processor/node/ProcedureNode.h"
#include "source_processor/node/StmtListNode.h"


class BaseExtractor {
 protected:
    int currentStmtNo = -1;
    std::vector<std::string> exprVariableList;

    /**
     * General looping of nodes that contains statements.
     * */
    void clearExprStack();
    virtual void extractProcedure(std::shared_ptr<ProcedureNode> node);
    virtual void extractStmtList(std::shared_ptr<StmtListNode> node);
    virtual void extractStmt(std::shared_ptr<StmtNode> node);

    /**
     * For expressions and conditional expression.
     * */

 public:
    BaseExtractor();

    virtual void extractProgram(std::shared_ptr<ProgramNode> node);
};
