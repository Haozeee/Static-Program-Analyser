#include "EntityExtractor.h"

EntityExtractor::EntityExtractor(std::shared_ptr<WriteOnlyStorage> storage) : AbstractSyntaxTreeExtractor(storage) {}

void EntityExtractor::extractProcedure(std::shared_ptr<ProcedureNode> node) {


    AbstractSyntaxTreeExtractor::extractProcedure(node);
}

void EntityExtractor::extractStmtList(std::shared_ptr<StmtListNode> node) {
    AbstractSyntaxTreeExtractor::extractStmtList(node);
}

void EntityExtractor::extractStmt(std::shared_ptr<StmtNode> node) {
    AbstractSyntaxTreeExtractor::extractStmt(node);
}

void EntityExtractor::extractRead() {

}

void EntityExtractor::extractPrint() {

}

void EntityExtractor::extractAssign() {

}

void EntityExtractor::extractCall() {

}

void EntityExtractor::extractIf() {

}

void EntityExtractor::extractWhile() {

}

void EntityExtractor::extractCondExpr() {

}

void EntityExtractor::extractExpr() {

}
