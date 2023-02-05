#pragma once

template <typename Entity>
class WriteOnlyEntityManager {
 public:
    virtual bool insertEntity(Entity entity) = 0;
};
