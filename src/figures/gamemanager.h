#pragma once

#include "abstractfigure.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"

#include <vector>
#include <exception>

class GameManager {
    Side turn;
    std::array<std::array<AbstractFigure *, 8>, 8> field;
    std::vector<AbstractFigure *> white_figures;
    std::vector<AbstractFigure *> black_figures;

    King *white_king;
    King *black_king;

public:
    GameManager();
    std::array<std::array<AbstractFigure *, 8>, 8> getField(void) const;
    Side whoseTurn() const;
    Turn makeTurn(const std::pair<int, int>& from, const std::pair<int, int>& to);

private:
    void initField();
    bool checkMate(std::vector<AbstractFigure *> checkFigures, King *king);
    std::pair<int, int> chooseMoveVector(AbstractFigure *figure, std::pair<int, int> king_coords) const;
};
