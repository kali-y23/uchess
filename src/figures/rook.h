#pragma once
#include "abstractfigure.h"

class Rook : public AbstractFigure {
    bool madeTurn;
public:
    Rook(const std::pair<int, int>& coordinates, enum Side side);

    // this method is defined only for Rook for castling, other figures handle their
    // coords only via the move method and the constructor
    void setCoords(std::pair<int, int> coords);
    virtual Turn checkMove(std::array<std::array<AbstractFigure *, 8>, 8>& field,
                           const std::pair<int, int>& coords);
    std::pair<int, int> makeMoveVector(const std::pair<int, int>& coords) const;
};