#include "SelectClause.h"

#include <utility>

SelectClause::SelectClause(std::shared_ptr<std::vector<SelectClauseItem>> selectClauseItems,
                           SelectClauseReturnType selectClauseReturnType) :
        selectClauseItems(std::move(selectClauseItems)), selectClauseReturnType(selectClauseReturnType) {}

SelectClause::SelectClause(SelectClauseReturnType selectClauseReturnType) :
        selectClauseReturnType(selectClauseReturnType) {}

bool SelectClause::operator==(const SelectClause &other) const {
    if (this->selectClauseReturnType != other.selectClauseReturnType) {
        return false;
    }

    if (this->selectClauseReturnType == SelectClauseReturnType::BOOLEAN) {
        return true;
    }

    for (int i = 0; i < this->selectClauseItems->size(); i++) {
        if (this->selectClauseItems->at(i) == other.selectClauseItems->at(i)) {
            continue;
        } else {
            return false;
        }
    }

    return true;
}

std::ostream& operator << (std::ostream& os, const SelectClause& selectClause) {
    for (SelectClauseItem item : *selectClause.selectClauseItems) {
        if (std::holds_alternative<std::shared_ptr<Synonym>>(item)) {
            std::shared_ptr<Synonym> synonym = std::get<std::shared_ptr<Synonym>>(item);
            os << (*synonym);
        } else {
            AttributeReference attributeReference = std::get<AttributeReference>(item);
            std::string synonym = attributeReference.getSynonym();
            os << (synonym);
        }
    }

    return os;
}

std::shared_ptr<std::vector<SelectClauseItem>> SelectClause::getSelectClauseItems() {
    return this->selectClauseItems;
}

std::string SelectClause::getSynonym(SelectClauseItem selectClauseItem) {
    if (std::holds_alternative<std::shared_ptr<Synonym>>(selectClauseItem)) {
        std::shared_ptr<Synonym> synonym = std::get<std::shared_ptr<Synonym>>(selectClauseItem);
        return synonym->ident;
    } else {
        AttributeReference attributeReference = std::get<AttributeReference>(selectClauseItem);
        std::string synonym = attributeReference.getSynonym();
        return synonym;
    }
}

SelectClauseReturnType SelectClause::getSelectClauseReturnType() {
    return this->selectClauseReturnType;
}
