#include "rook.h"

Rook::Rook(const std::pair<int, int>& coordinates, enum Side side) : AbstractFigure(Type::Rook, coordinates, side) {
    madeTurn = false;
}

Turn Rook::checkMove(std::array<std::array<AbstractFigure *, 8>, 8>& field,
                        const std::pair<int, int>& coords) {

    if ((coords.second == m_coords.second && coords.first != m_coords.first) ||
        (coords.first == m_coords.first && coords.second != m_coords.second)) {
        if (!checkObstacles(field, makeMoveVector(coords), coords))
            return {Outcome::Invalid, nullptr};
        madeTurn = true;
        if (field[coords.second][coords.first] && field[coords.second][coords.first]->getSide() != m_side)
            return {Outcome::Eat, &coords};
        else
            return {Outcome::Move, nullptr};
    }
    else 
        return {Outcome::Invalid, nullptr};
}

void Rook::setCoords(std::pair<int, int> coords) {
    m_coords = coords;
}

std::pair<int, int> Rook::makeMoveVector(const std::pair<int, int>& coords) const {
    if (coords.second == m_coords.second) {
        int x_delta = coords.first > m_coords.first ? 1 : -1;
        return std::make_pair<int, int>(std::move(x_delta), 0);
    }
    else {
        int y_delta = coords.second > m_coords.second ? 1 : -1;
        return std::make_pair<int, int>(0, std::move(y_delta));
    }
}
