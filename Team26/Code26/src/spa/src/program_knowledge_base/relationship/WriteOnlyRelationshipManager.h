#pragma once

template <typename T, typename U>
class WriteOnlyRelationshipManger {
 public:
    virtual bool insertRelationship(T first_param, U second_param) = 0;
    virtual bool insertRelationship(T first_param, U second_param,
                                    std::shared_ptr<WriteOnlyRelationshipManger<T, U>> manager) = 0;
};
