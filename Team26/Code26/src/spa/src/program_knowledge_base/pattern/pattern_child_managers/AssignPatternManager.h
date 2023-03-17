#pragma once
#include <memory>
#include <string>
#include "program_knowledge_base/pattern/PatternManager.h"

class AssignPatternManager : public PatternManager<std::string, std::shared_ptr<ShuntNode>> { };
