#include "catch.hpp"
#include "query_processing_system/parser/SelectClause.h"

TEST_CASE("Select Clause Class") {
    auto synonym = std::make_shared<Synonym>("v");
    SelectClauseItem selectClauseItem = synonym;
    auto selectClauseItems = std::make_shared<std::vector<SelectClauseItem>>();
    selectClauseItems->push_back(selectClauseItem);
    SelectClause selectClause = SelectClause(selectClauseItems, SelectClauseReturnType::SYNONYM);

    SECTION("bool == operator SYNONYM") {
        SelectClauseItem selectClauseItemTest = synonym;
        auto selectClauseItemsTest = std::make_shared<std::vector<SelectClauseItem>>();
        selectClauseItemsTest->push_back(selectClauseItemTest);
        SelectClause selectClauseTest = SelectClause(selectClauseItemsTest, SelectClauseReturnType::SYNONYM);
        REQUIRE(selectClause == selectClauseTest);
    }

    SECTION("bool != operator SYNONYM") {
        SelectClauseItem selectClauseItemTest = std::make_shared<Synonym>("v");
        auto selectClauseItemsTest = std::make_shared<std::vector<SelectClauseItem>>();
        selectClauseItemsTest->push_back(selectClauseItemTest);
        SelectClause selectClauseTest = SelectClause(selectClauseItemsTest, SelectClauseReturnType::SYNONYM);
        REQUIRE_FALSE(selectClause == selectClauseTest);
    }

    SelectClause selectClauseBoolean = SelectClause(SelectClauseReturnType::BOOLEAN);
    SECTION("bool == operator BOOLEAN") {
        SelectClause selectClauseBooleanTest = SelectClause(SelectClauseReturnType::BOOLEAN);
        REQUIRE(selectClauseBoolean == selectClauseBooleanTest);
    }

    SECTION("bool != operator BOOLEAN") {
        SelectClause selectClauseBooleanTest = SelectClause(SelectClauseReturnType::BOOLEAN);
        REQUIRE_FALSE(selectClause == selectClauseBooleanTest);
    }

    SECTION("isAttribute") {
        REQUIRE_FALSE(SelectClause::isAttribute(selectClauseItem));
    }

    SECTION("getString Synonym") {
        REQUIRE(SelectClause::getString(selectClauseItem) == "v");
    }

    SECTION("getString AttributeReference") {
        AttributeReference attributeReference = AttributeReference(DesignEntity::VARIABLE, "v", varName);
        REQUIRE(SelectClause::getString(attributeReference) == "v.varName");
    }
}
