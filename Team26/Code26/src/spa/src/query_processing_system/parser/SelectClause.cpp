#include "SelectClause.h"

SelectClause::SelectClause(std::shared_ptr<std::vector<SelectClauseItem>> selectClauseItems) :
selectClauseItems(selectClauseItems) {}

bool SelectClause::operator==(const SelectClause &other) const {
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
        std::shared_ptr<Synonym> syn = std::get<std::shared_ptr<Synonym>>(item);
        os << *syn;
    }

    return os;
}

std::shared_ptr<std::vector<SelectClauseItem>> SelectClause::getSelectClauseItems() {
    return this->selectClauseItems;
}
