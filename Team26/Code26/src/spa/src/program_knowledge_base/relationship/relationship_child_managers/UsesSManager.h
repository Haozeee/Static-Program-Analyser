#pragma once
#include <string>
#include "program_knowledge_base/relationship/RelationshipManager.h"

class UsesSManager : public RelationshipManager<int, std::string> { };
