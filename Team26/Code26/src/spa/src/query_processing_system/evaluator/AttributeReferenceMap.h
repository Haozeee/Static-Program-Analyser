#pragma once
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "query_processing_system/parser/clause/with_clause/AttributeReference.h"
#include "query_processing_system/evaluator/clause_evaluator/StorageReader.h"


using StringVector = std::vector<std::string>;

/**
 * Given a synonym column e.g "c" in the results and an attribute ref "c.procName" in the select clause,
 * this function maps the results of c to c.procName.
 * @param attributeRef
 * @param synonymValues
 * @param storage
 */
void mapAttribute(const AttributeReference& attributeRef, StringVector &synonymValues,
                  std::shared_ptr<ISourceReader> storage);

void mapStatementToVariable(StringVector &synonymValues,
                            std::unordered_map<int, std::unordered_set<std::string>> &relationship);
