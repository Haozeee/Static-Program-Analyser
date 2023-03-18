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

    /**
     * General looping of nodes that contains statements.
     * */
    virtual void extractProcedure(const std::shared_ptr<ProcedureNode>& node);
    virtual void extractStmtList(const std::shared_ptr<StmtListNode>& node);
    virtual void extractStmt(const std::shared_ptr<StmtNode>& node);

 public:
    BaseExtractor();

    virtual void extractProgram(const std::shared_ptr<ProgramNode>& node);
};
