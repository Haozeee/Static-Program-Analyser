#pragma once

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>
#include "common/parser/AbstractParser.h"
#include "common/tokenizer/token/Token.h"
#include "source_processor/node/ProgramNode.h"
#include "source_processor/node/ProcedureNode.h"
#include "source_processor/node/StmtListNode.h"
#include "source_processor/node/CondExprNode.h"
#include "source_processor/node/ExprNode.h"
#include "source_processor/node/statement_node/ReadNode.h"
#include "source_processor/node/statement_node/PrintNode.h"
#include "source_processor/node/statement_node/CallNode.h"
#include "source_processor/node/statement_node/AssignNode.h"
#include "source_processor/node/statement_node/WhileNode.h"
#include "source_processor/node/statement_node/IfNode.h"



class Parser : public AbstractParser {
 private:
    std::shared_ptr<CondExprNode> parseCondExprNode(int startIndex, int endIndex);
    std::shared_ptr<ExprNode> parseFactor(int index, int endIndex);
    bool isBinaryCondOperator();
    bool isIllegalArithmeticSplChar();
    OperatorType getOperator();
    bool isExprOperator();
    bool isTermOperator();
    bool isFactor();

    std::shared_ptr<ProgramNode> programRoot;

    int stmtIndex;
    std::shared_ptr<ProgramNode> parseProgram();
    std::shared_ptr<ProcedureNode> parseProcedure();
    std::shared_ptr<StmtListNode> parseStmtList();
    std::shared_ptr<ReadNode> parseRead();
    std::shared_ptr<PrintNode> parsePrint();
    std::shared_ptr<CallNode> parseCall();
    std::shared_ptr<WhileNode> parseWhile();
    std::shared_ptr<IfNode> parseIf();
    std::shared_ptr<AssignNode> parseAssign(std::shared_ptr<Token> nameToken);
    std::shared_ptr<CondExprNode> parseConditional();

    std::shared_ptr<RelExpr> parseRelExpr(int startIndex, int endIndex);
    std::shared_ptr<ExprNode> parseExprNode(int startIndex, int endIndex);
    std::shared_ptr<ExprNode> parseTerm(int startIndex, int endIndex);
    std::string toString(int startIndex, int endIndex);

public:

    explicit Parser(std::vector<std::shared_ptr<Token>> tokens);

    void parse() override;

    std::shared_ptr<ProgramNode> getProgramNode();
};
