#pragma once

#include "Storage.h"
#include "entity/WriteOnlyEntityManager.h"
#include "relationship/WriteOnlyRelationshipManager.h"

class WriteOnlyStorage : public Storage<WriteOnlyRelationshipManger,
        WriteOnlyEntityManager> {
};
