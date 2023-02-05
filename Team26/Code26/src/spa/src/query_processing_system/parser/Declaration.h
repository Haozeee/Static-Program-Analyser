#pragma once
#include "Synonym.h"
#include "DesignEntity.h"

class Declaration {
 private:
    Synonym synonym;
    DesignEntity designEntity;

 public:
    Declaration(Synonym synonym, DesignEntity designEntity);

    Synonym getSynonym();

    DesignEntity getDesignEntity();

    bool operator==(const Declaration& other) const;

    friend std::ostream& operator << (std::ostream& os, const Declaration& declaration);
};
