#include "catch.hpp"
#include "query_processing_system/parser/clause/with_clause/Reference.h"

#include <iostream>

TEST_CASE("Reference Class") {
    AttributeReference attributeReference = AttributeReference(DesignEntity::VARIABLE, "v", "varName");
    Reference reference = Reference::createReference(attributeReference);

    SECTION("getDesignEntity") {
        REQUIRE(reference.getAttributeIdentity() == "v");
    }

    SECTION("getAttributeDesignEntity") {
        REQUIRE(reference.getAttributeDesignEntity() == DesignEntity::VARIABLE);
    }

    SECTION("getReferenceType") {
        REQUIRE(reference.getReferenceType() == ReferenceType::ATTR_REF);
    }

    SECTION("getValue") {
        Reference referenceTest = Reference::createReference("v");
        if (std::holds_alternative<std::string>(referenceTest.getValue())) {
            REQUIRE(std::get<std::string>(referenceTest.getValue()) == "v");
        }
    }
}
