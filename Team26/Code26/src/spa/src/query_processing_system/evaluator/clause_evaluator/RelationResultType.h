#pragma once
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <string>
#include <memory>
#include "common/parser/ShuntNode.h"

using StmtStmtMap = std::unordered_map<int, std::unordered_set<int>>;
using StmtEntityMap = std::unordered_map<int, std::unordered_set<std::string>>;
using EntityStmtMap = std::unordered_map<std::string , std::unordered_set<int>>;
using EntityEntityMap = std::unordered_map<std::string , std::unordered_set<std::string>>;
using StmtSet = std::unordered_set<int>;
using EntitySet = std::unordered_set<std::string>;
/**
 * Contains the property fo an assign statement.
 */
using AssignStatements = std::unordered_map<int, std::pair<std::string, std::shared_ptr<ShuntNode>>>;
