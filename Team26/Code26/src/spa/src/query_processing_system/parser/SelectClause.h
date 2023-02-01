#pragma once

#include <memory>
#include <vector>
#include <string>
#include "Synonym.h"

class SelectClause {
 private:
    std::shared_ptr<std::vector<Synonym>> selectClauseItems;

 public:
    explicit SelectClause(std::shared_ptr<std::vector<Synonym>> selectClauseItems);

    std::string toString();

    bool operator==(const SelectClause& other) const;

    friend std::ostream& operator << (std::ostream& os, const SelectClause& selectClause);

    std::shared_ptr<std::vector<Synonym>> getSelectClauseItems();
};
