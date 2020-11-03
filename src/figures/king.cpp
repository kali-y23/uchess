#include "king.h"

#include <iostream>

King::King(const std::pair<int, int>& coordinates, enum Side side) : AbstractFigure(Type::King, coordinates, side) {
    madeTurn =  false;
}

Turn King::checkMove(std::array<std::array<AbstractFigure *, 8>, 8>& field,
                          const std::pair<int, int>& coords) {
    if (m_coords.first > 7 || m_coords.second > 7)
        return {Outcome::Invalid, nullptr};

    if (std::abs(coords.first - m_coords.first) <= 1 && std::abs(coords.second - m_coords.second) <= 1) {
        if (field[coords.second][coords.first] && field[coords.second][coords.first]->getSide() != m_side)
            return {Outcome::Eat, &coords};
        else if (!field[coords.second][coords.first])
            return {Outcome::Move, nullptr};
    }
    return {Outcome::Invalid, nullptr};
}
