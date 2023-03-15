#include "AssignNode.h"

#include <utility>
#include "source_processor/design_extractor/interface/statement_extractor/IStmtExtractor.h"

AssignNode::AssignNode(int stmtIndex, std::string varName,
                       std::shared_ptr<ShuntNode> shutNode,
                       std::unordered_set<std::string> exprVariables,
                       std::unordered_set<int> exprConstants)
    : VariableNameNode(stmtIndex, std::move(varName), StmtType::STMT_ASSIGN) ,
      shutNode(std::move(shutNode)), exprVariables(std::move(exprVariables)), exprConstants(std::move(exprConstants)) {}

void AssignNode::evaluate(IStmtExtractor &extractor) {
    extractor.extractAssign(this->shared_from_this());
}
