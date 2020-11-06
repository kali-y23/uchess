#pragma once

#include "abstractfigure.h"
#include "rook.h"

#include <vector>

class Rook;

class King : public AbstractFigure {
    bool madeTurn;
public:
    King(const std::pair<int, int>& coordinates, enum Side side);

    virtual Turn checkMove(std::array<std::array<AbstractFigure *, 8>, 8>& field,
                           const std::pair<int, int>& coords);
    std::vector<AbstractFigure *> checkCheckWrapper(std::array<std::array<AbstractFigure *, 8>, 8>& field,
                                                    const std::pair<int, int>& from,
                                                    const std::pair<int, int>& to);  

private:
    std::pair<int, int> checkCastling(std::array<std::array<AbstractFigure *, 8>, 8>& field,
                                      std::pair<int, int> to, int *sign);
    std::vector<AbstractFigure *> checkCheck(std::array<std::array<AbstractFigure *, 8>, 8>& field,
                                             const std::pair<int, int>& king_coords);

    // void swapFigures(std::pair<int, int> from,;
};