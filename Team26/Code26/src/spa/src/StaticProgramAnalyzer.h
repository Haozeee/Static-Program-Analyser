#pragma once
#include <string>
#include <list>

class StaticProgramAnalyzer {
 public:
        void readProgramFromFile(std::string filename);
        void evalauteInputQuery(std::string query, std::list<std::string>& results);
};
