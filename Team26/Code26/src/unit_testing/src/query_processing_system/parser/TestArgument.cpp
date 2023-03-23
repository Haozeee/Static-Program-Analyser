#include "catch.hpp"
#include "query_processing_system/parser/Argument.h"

TEST_CASE("Argument CLass") {
    Argument argument = Argument(ArgumentType::SYNONYM, "v", DesignEntity::VARIABLE);

    SECTION("bool == operator") {
        Argument argumentTest = Argument(ArgumentType::SYNONYM, "v", DesignEntity::VARIABLE);
        REQUIRE(argument == argumentTest);
    }
}
