#include "knight.h"

#include <iostream>

Knight::Knight(const std::pair<int, int>& coordinates, enum Side side) : AbstractFigure(Type::Knight, coordinates, side) {}

Turn Knight::checkMove(std::array<std::array<AbstractFigure *, 8>, 8>& field,
                          const std::pair<int, int>& coords) {
    if (m_coords.first > 7 || m_coords.second > 7)
        return {Outcome::Invalid, nullptr};
    if ((m_coords.first == coords.first + 2 && m_coords.second == coords.second + 1) ||
        (m_coords.first == coords.first + 1 && m_coords.second == coords.second + 2) ||
        (m_coords.first == coords.first + 2 && m_coords.second == coords.second - 1) ||
        (m_coords.first == coords.first + 1 && m_coords.second == coords.second - 2) ||
        (m_coords.first == coords.first - 2 && m_coords.second == coords.second + 1) ||
        (m_coords.first == coords.first - 1 && m_coords.second == coords.second + 2) ||
        (m_coords.first == coords.first - 2 && m_coords.second == coords.second - 1) ||
        (m_coords.first == coords.first - 1 && m_coords.second == coords.second - 2)) {
        
        if (field[coords.second][coords.first] && field[coords.second][coords.first]->getSide() != m_side)
            return {Outcome::Eat, &coords};
        else if (!field[coords.second][coords.first])
            return {Outcome::Move, nullptr};
    }

    return {Outcome::Invalid, nullptr};
}