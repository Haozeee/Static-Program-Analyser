#pragma once

template <typename T>
class IWriteEntityManager {
 public:
    virtual bool insertEntity(T name_or_stmtNo) = 0;
};
