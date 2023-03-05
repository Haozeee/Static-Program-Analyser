#pragma once
#include <memory>
#include <string>
#include "program_knowledge_base/relationship/RelationshipManager.h"

class CallPManager : public RelationshipManager<std::string, std::string> { };
