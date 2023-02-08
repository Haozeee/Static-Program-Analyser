#pragma once

#include <memory>
#include <string>
#include <vector>
#include "common/Parser.h"
#include "common/tokens/Token.h"
#include "node/ProgramNode.h"
#include "node/ProcedureNode.h"
#include "node/StmtListNode.h"
#include "node/ExprNode.h"
#include "node/statement_node/ReadNode.h"
#include "node/statement_node/PrintNode.h"
#include "node/statement_node/CallNode.h"
#include "node/statement_node/AssignNode.h"
#include "node/statement_node/WhileNode.h"
#include "node/statement_node/IfNode.h"



class SourceParser : public Parser {
 private:
    typedef Parser Super;
    int stmtIndex;
    std::shared_ptr<ProcedureNode> parseProcedure();
    std::shared_ptr<StmtListNode> parseStmtList();
    std::shared_ptr<ReadNode> parseRead();
    std::shared_ptr<PrintNode> parsePrint();
    std::shared_ptr<CallNode> parseCall();
    std::shared_ptr<WhileNode> parseWhile();
    std::shared_ptr<AssignNode> parseAssign(std::shared_ptr<Token> nameToken);
    std::shared_ptr<CondExprNode> parseCondExprNode(std::string condExpr);
    std::shared_ptr<ExprNode> parseExpr(std::string expr);
    std::shared_ptr<Term> parseTerm(std::string term);

 public:
    explicit SourceParser(std::vector<std::shared_ptr<Token>> tokens);
    std::shared_ptr<ProgramNode> parse();
};
