#pragma once

#include <memory>
#include <vector>
#include <string>
#include <ostream>
#include <variant>
#include "Synonym.h"
#include "query_processing_system/parser/clause/with_clause/AttributeReference.h"

using SelectClauseItem = std::variant<std::shared_ptr<Synonym>, AttributeReference>;

enum class SelectClauseReturnType {
    BOOLEAN,
    SYNONYM,
};

class SelectClause {
 private:
    std::shared_ptr<std::vector<SelectClauseItem>> selectClauseItems =
            std::make_shared<std::vector<SelectClauseItem>>();
    SelectClauseReturnType selectClauseReturnType;

 public:
    /**
     * Compares two SelectClause objects.
     *
     * @param other Second SelectClause object to be compared against.
     * @return Returns true if both SelectClause objects are the same, false otherwise.
     */
    bool operator==(const SelectClause& other) const;

    /**
     * Overloading operator<< to output SelectClause as a stream object.
     *
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
     * Gets the Synonym of the Select Clause Item.
     *
     * @param selectClauseItem The Select Clause Item that is passed.
     * @return Returns the Synonym in the passed Select Clause Item.
     */
    static std::string getSynonym(SelectClauseItem selectClauseItem);

    /**
     * Get the string value of the Select Clause Item. If select clause
     * item is a synonym, simply get the identity of the synonym.
     * If it is an attribute reference, get its synonym identity + "." + attribute name.
     */
    static std::string getString(SelectClauseItem selectClauseItem);

    /**
     * Given a select clause item, check if it refers to a attribute reference
     * @return True if it is an attribute. Otherwise, return false.
     */
    static bool isAttribute(SelectClauseItem selectClauseItem);

    SelectClauseReturnType getSelectClauseReturnType();

    /**
     * Constructor for the SelectClause.
     *
     * @param selectClauseItems stored in a list of Synonym objects.
     */
    explicit SelectClause(std::shared_ptr<std::vector<SelectClauseItem>> selectClauseItems,
                          SelectClauseReturnType selectClauseReturnType);

    explicit SelectClause(SelectClauseReturnType selectClauseReturnType);
};
