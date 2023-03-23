#include "catch.hpp"
#include "query_processing_system/parser/Declaration.h"

TEST_CASE("Declaration CLass") {
    Synonym synonym = Synonym("v");
    Declaration declaration = Declaration(synonym, DesignEntity::VARIABLE);

    SECTION("bool == operator") {
        Declaration declarationTest = Declaration(synonym, DesignEntity::VARIABLE);
        REQUIRE(declaration == declarationTest);
    }
}