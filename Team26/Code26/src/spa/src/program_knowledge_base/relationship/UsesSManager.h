#pragma once
#include <string>
#include "RelationshipManager.h"

class UsesSManager : public RelationshipManager<int, std::string> { };
