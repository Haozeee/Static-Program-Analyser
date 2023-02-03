#pragma once

#include <memory>
#include <vector>
#include <string>
#include <ostream>
#include <variant>
#include "Synonym.h"

using SelectClauseItem = std::variant<std::shared_ptr<Synonym>>;

class SelectClause {
 private:
    std::shared_ptr<std::vector<SelectClauseItem>> selectClauseItems;

 public:
    /**
     * Compares two SelectClause objects.
     * @param other Second SelectClause object to be compared against.
     * @return Returns true if both SelectClause objects are the same, false otherwise.
     */
    bool operator==(const SelectClause& other) const;

    /**
     * Overloading operator<< to output SelectClause as a stream object.
     * @param ostream Output type for the object std::cout.
     * @param synonym SelectClause object to be output.
     * @return
     */
    friend std::ostream& operator << (std::ostream& os, const SelectClause& selectClause);

    /**
     * SelectClause items stored in a list of Synonym objects.
     * @return Returns the SelectClause items stored in a list of Synonym objects.
     */
    std::shared_ptr<std::vector<SelectClauseItem>> getSelectClauseItems();

    /**
     * Constructor for the SelectClause.
     * @param selectClauseItems stored in a list of Synonym objects.
     */
    explicit SelectClause(std::shared_ptr<std::vector<SelectClauseItem>> selectClauseItems);
};
