#include "catch.hpp"
#include "query_processing_system/parser/clause/with_clause/AttributeReference.h"

TEST_CASE("Attribute Reference CLass") {
    AttributeReference attributeReference = AttributeReference(DesignEntity::VARIABLE, "v", "varName");

    SECTION("getDesignEntity") {
        REQUIRE(attributeReference.getDesignEntity() == DesignEntity::VARIABLE);
    }
}
