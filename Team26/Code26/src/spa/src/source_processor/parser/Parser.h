#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include "common/parser/AbstractParser.h"
#include "common/tokenizer/token/Token.h"
#include "source_processor/node/ProgramNode.h"
#include "source_processor/node/ProcedureNode.h"
#include "source_processor/node/StmtListNode.h"
#include "source_processor/node/statement_node/ReadNode.h"
#include "source_processor/node/statement_node/PrintNode.h"
#include "source_processor/node/statement_node/CallNode.h"
#include "source_processor/node/statement_node/AssignNode.h"
#include "source_processor/node/statement_node/WhileNode.h"
#include "source_processor/node/statement_node/IfNode.h"

enum class HelperNode {
    ExprHelper,
    CondExprHelper
};

class Parser : public AbstractParser {
 private:
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
    std::shared_ptr<CondExprNode> parseConditional(
            const std::shared_ptr<std::unordered_set<std::string>>& exprVariables,
            const std::shared_ptr<std::unordered_set<int>>& exprConstants);
    void popExprHelper(std::stack<HelperNode>& result);
    void continueExprHelper(std::stack<HelperNode>& result);
    void popCondExprHelper(std::stack<HelperNode>& result);
    void continueCondExprHelper(std::stack<HelperNode>& result);
    void checkStackSize(std::stack<HelperNode>& result);
    void handleEndBrackets(std::stack<std::shared_ptr<Token>>& opStack, std::queue<std::shared_ptr<Token>>& postfix,
                           bool& isRelExpr, const std::unordered_set<std::string>& relOp,
                           const std::vector<std::shared_ptr<Token>>& tokens, int index);

 public:
    explicit Parser(std::vector<std::shared_ptr<Token>> tokens);

    void parse() override;

    std::shared_ptr<ProgramNode> getProgramNode();
};
