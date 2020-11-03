#pragma once
#include "abstractfigure.h"

class AbstractFigure;

class Knight : public AbstractFigure {
public:
    Knight(const std::pair<int, int>& coordinates, enum Side side);

    virtual Turn checkMove(std::array<std::array<AbstractFigure *, 8>, 8>& field,
                            const std::pair<int, int>& coords);
};