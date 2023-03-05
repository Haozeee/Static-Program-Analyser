#pragma once
#include <string>
#include "program_knowledge_base/relationship/RelationshipManager.h"

class CallsPSManager : public RelationshipManager<int, std::string> { };
