#pragma once

#include <tuple>
#include <vector>

class TestSourceParserUtil {
public:
    static std::vector<std::tuple<int, int, int>> generatePermutations(int num1, int num2, int num3) {
        std::vector<std::tuple<int, int, int>> triples;
        if (num1 < 1 || num2 < 1 || num3 < 1) {
            return triples;
        }

        for (int i = 1; i < num1; i++) {
            for (int j = 1; j < num2; j++) {
                for (int k = 1; k < num3; k++) {
                    triples.emplace_back(std::make_tuple(i, j, k));
                }
            }
        }

        return triples;
    }
};