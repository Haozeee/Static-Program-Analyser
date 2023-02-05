#pragma once

template <typename T>
class WriteOnlyEntityManager {
 public:
    virtual bool insertEntity(T name_or_stmtNo) = 0;
};
