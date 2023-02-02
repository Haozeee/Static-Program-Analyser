#pragma once
#include <string>
#include "RelationshipManager.h"

class UsesPManager : public RelationshipManager<std::string , std::string> { };
