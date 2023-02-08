#pragma once

#include <memory>
#include <string>
#include <vector>
#include "common/parser/AbstractParser.h"
#include "common/tokenizer/token/Token.h"
#include "source_processor/node/ProgramNode.h"
#include "source_processor/node/ProcedureNode.h"
#include "source_processor/node/StmtListNode.h"
#include "source_processor/node/CondExprNode.h"
#include "source_processor/node/ExprNode.h"
#include "source_processor/node/TermNode.h"
#include "source_processor/node/statement_node/ReadNode.h"
#include "source_processor/node/statement_node/PrintNode.h"
#include "source_processor/node/statement_node/CallNode.h"
#include "source_processor/node/statement_node/AssignNode.h"
#include "source_processor/node/statement_node/WhileNode.h"
#include "source_processor/node/statement_node/IfNode.h"



class Parser : public AbstractParser {
 private:
    typedef AbstractParser Super;
    int stmtIndex;
    std::shared_ptr<ProcedureNode> parseProcedure();
    std::shared_ptr<StmtListNode> parseStmtList();
    std::shared_ptr<ReadNode> parseRead();
    std::shared_ptr<PrintNode> parsePrint();
    std::shared_ptr<CallNode> parseCall();
    std::shared_ptr<WhileNode> parseWhile();
    std::shared_ptr<IfNode> parseIf();
    std::shared_ptr<AssignNode> parseAssign(std::shared_ptr<Token> nameToken);
    std::shared_ptr<CondExprNode> parseCondExprNode(std::string condExpr);
    std::shared_ptr<RelExpr> parseRelExpr(std::string relExpr);
    std::shared_ptr<ExprNode> parseExprNode(std::string expr);
    std::shared_ptr<TermNode> parseTermNode(std::string term);
    std::shared_ptr<Factor> parseFactor(std::string factor);

 public:
    explicit Parser(std::vector<std::shared_ptr<Token>> tokens);
    std::shared_ptr<ProgramNode> parse();
};
