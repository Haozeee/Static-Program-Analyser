#pragma once

#include "Storage.h"
#include "entity/ReadOnlyEntityManager.h"
#include "relationship/ReadOnlyRelationshipManager.h"

class ReadOnlyStorage: public Storage<ReadOnlyRelationshipManager,
        ReadOnlyEntityManager> {};
