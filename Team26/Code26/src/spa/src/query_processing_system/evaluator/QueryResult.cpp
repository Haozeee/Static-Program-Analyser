#include "QueryResult.h"
#include <iostream>
#include <algorithm>
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
            it->second = PkbUtil::setIntersection(it->second, v);
        }
    }
}

bool QueryResult::operator ==(const QueryResult &other) const {
    return results == other.results;
}

std::ostream& operator <<(std::ostream& os, const QueryResult& queryResult) {
    os << "Displaying Query Result: \n";
    for (auto i : queryResult.results) {
        os << "Identity: " << i.first << "\n";
        os << "Results: ";
        for (auto j : i.second) {
            os << j << " ";
        }
        os << "\n";
    }
    return os;
}
