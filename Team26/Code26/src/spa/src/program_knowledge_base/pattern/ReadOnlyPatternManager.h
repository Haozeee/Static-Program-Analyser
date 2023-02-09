#pragma once

class ReadOnlyPatternManager {
 public:
    virtual bool isEmptyLhsVector() = 0;
    virtual bool isEmptyRhsVector() = 0;
    virtual bool isEmptyIndexStmtMap() = 0;
    virtual bool isEmptyReversedIndexStmtMap() = 0;
    virtual bool containsLhsVector(const std::string&) = 0;
    virtual bool containsRhsVector(const std::string&) = 0;
    virtual bool containsIndexStmtMap(int, int) = 0;
    virtual bool containsReversedIndexStmtMap(int, int) = 0;
    virtual std::vector<std::string> getAllLhsPatternEntries() = 0;
    virtual std::vector<std::string> getAllRhsPatternEntries() = 0;
    virtual std::unordered_map<int, int> getAllPatternEntries() = 0;
    virtual std::unordered_map<int, int> getAllReversedPatternEntries() = 0;
};
