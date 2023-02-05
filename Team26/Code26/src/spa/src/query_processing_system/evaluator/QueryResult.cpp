#include "QueryResult.h"
#include <iostream>

QueryResult::QueryResult() {}

void QueryResult::addNewIdentity(std::string identity) {
    results.insert({identity, {}});
}

void QueryResult::addResultsToIdentity(std::string identity, std::unordered_set<std::string> toAdd) {
    auto it = results.find(identity);
    if (it != results.end()) {
        it->second = toAdd;
    }
}

void QueryResult::copyToQpsResult(std::list<std::string> &qpsResult) {
    for (auto const& item : results) {
        for (auto str : item.second) {
            qpsResult.push_back(str);
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
