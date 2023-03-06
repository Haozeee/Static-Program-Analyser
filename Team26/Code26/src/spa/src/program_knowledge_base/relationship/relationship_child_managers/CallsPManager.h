#pragma once
#include <memory>
#include <string>
#include "program_knowledge_base/relationship/RelationshipManager.h"

class CallsPManager : public RelationshipManager<std::string, std::string> { };
