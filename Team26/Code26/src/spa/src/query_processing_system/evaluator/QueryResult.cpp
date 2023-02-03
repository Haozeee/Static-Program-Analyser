#include "QueryResult.h"

QueryResult::QueryResult() {};

void QueryResult::addNewIdentity(std::string identity) {
    auto iterator = results.find(identity);
    if (iterator == results.end()) {
        std::unordered_set<std::string> emptyResults;
        results.insert({identity, emptyResults});
    }
}

bool QueryResult::operator ==(const QueryResult &other) const {
    return results == other.results;
}

std::ostream& operator <<(std::ostream& os, const QueryResult& queryResult) {
    for (auto i : queryResult.results) {
        os << "Identity" << i.first << "\n";
        os << "Results:" << "\n";
        for (auto j : i.second) {
            os << j << "\n";
        }
        os << "\n";
    }
}
