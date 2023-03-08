#pragma once
#include <string>
#include "program_knowledge_base/relationship/RelationshipManager.h"

class CallsSManager : public RelationshipManager<int, std::string> { };
