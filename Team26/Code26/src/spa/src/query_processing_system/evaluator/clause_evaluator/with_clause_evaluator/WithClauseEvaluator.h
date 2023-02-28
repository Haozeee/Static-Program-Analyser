#pragma once
#include <string>
#include <unordered_set>
#include <utility>
#include "memory"
#include "../ClauseEvaluator.h"
#include "../../../parser/clause/with_clause/Reference.h"

using ReferenceValues = std::unordered_set<std::string>;

template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>;

class WithClauseEvaluator : public ClauseEvaluator {
 private:
    Reference leftRef;

    Reference rightRef;

    void evaluateAttributeAttribute(StoragePointer storage);

    static ReferenceValues getReferenceValues(Reference ref, StoragePointer storage = nullptr);

    static ReferenceValues getAttributeReferenceValues(AttributeReference ref, StoragePointer storage);


 public:
    WithClauseEvaluator(Reference left, Reference right);

    std::shared_ptr<ResultTable> evaluateClause(StoragePointer storage) override;
};
