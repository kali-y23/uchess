#pragma once
#include "abstractfigure.h"

// enum class Type;
// enum class Side;
// enum class Outcome;

class Pawn : public AbstractFigure {
    bool m_first_turn = false;

public:
    Pawn(const std::pair<int, int>& coordinates, Side side);
    void setType(Type type);
    bool getFirstTurn() const;

    virtual Turn checkMove(std::array<std::array<AbstractFigure *, 8>, 8>& field,
                              const std::pair<int, int>& coords);

private:
    const std::pair<int, int> *enPassant(std::array<std::array<AbstractFigure *, 8>, 8>& field,
                                         const std::pair<int, int>& coords);
};
