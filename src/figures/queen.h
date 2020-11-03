#pragma once
#include "abstractfigure.h"

class Queen : public AbstractFigure {
public:
    Queen(const std::pair<int, int>& coordinates, enum Side side);

    virtual Turn checkMove(std::array<std::array<AbstractFigure *, 8>, 8>& field,
                           const std::pair<int, int>& coords);
    std::pair<int, int> makeMoveVector(const std::pair<int, int>& coords) const;
};