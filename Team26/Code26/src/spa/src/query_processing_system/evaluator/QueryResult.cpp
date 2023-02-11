#include "QueryResult.h"
#include <iterator>

QueryResult::QueryResult() {}

void QueryResult::addNewIdentity(std::string identity) {
    results.insert({identity, {}});
}

void QueryResult::copyToQpsResult(std::list<std::string> &qpsResult) {
    for (auto const& item : results) {
        for (auto str : item.second) {
            qpsResult.push_back(str);
        }
    }
}

void QueryResult::addClauseResultToQuery(std::shared_ptr<ClauseResult> clauseResult) {
    if (clauseResult->hasNoResults()) {
        // If a clause returns nothing, then the query has no results at all
        results = {};
    }
    for (auto const& [k, v] : clauseResult->getResults()) {
        auto it = results.find(k);
        if (it != results.end()) {
            std::unordered_set<std::string> res;
            PkbUtil::setIntersection(it->second, v, res);
            it->second = res;
        }
        std::cout << *this << "\n";
    }
}

bool QueryResult::operator ==(const QueryResult &other) const {
    return results == other.results;
}

