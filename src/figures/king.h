#pragma once
#include "abstractfigure.h"

class King : public AbstractFigure {
    bool madeTurn;
public:
    King(const std::pair<int, int>& coordinates, enum Side side);

    std::pair<int, int> *checkCheck(std::array<std::array<AbstractFigure *, 8>, 8>& field,
                                    const std::pair<int, int>& coords);
    virtual Turn checkMove(std::array<std::array<AbstractFigure *, 8>, 8>& field,
                           const std::pair<int, int>& coords);

private:
    // void swapFigures(std::pair<int, int> from,;
};