#pragma once

template <typename T>
class IWriteEntityManager {
 public:
    virtual bool insertEntity(T nameOrStmtNo) = 0;
};
