#pragma once
#include <string>
#include "program_knowledge_base/relationship/RelationshipManager.h"

class CallsTManager : public RelationshipManager<std::string, std::string> { };
