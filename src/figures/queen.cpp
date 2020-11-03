#include "queen.h"

Queen::Queen(const std::pair<int, int>& coordinates, enum Side side) : AbstractFigure(Type::Queen, coordinates, side) {}

Turn Queen::checkMove(std::array<std::array<AbstractFigure *, 8>, 8>& field,
                        const std::pair<int, int>& coords) {
    if ((coords.second == m_coords.second && coords.first != m_coords.first) ||
        (coords.first == m_coords.first && coords.second != m_coords.second) ||
        (std::abs(m_coords.first - coords.first) == std::abs(m_coords.second - coords.second))) {
        if (!checkObstacles(field, makeMoveVector(coords), coords))
            return {Outcome::Invalid, nullptr};
        if (field[coords.second][coords.first] && field[coords.second][coords.first]->getSide() != m_side)
            return {Outcome::Eat, &coords};
        else
            return {Outcome::Move, nullptr};
    }
    else 
        return {Outcome::Invalid, nullptr};
}

std::pair<int, int> Queen::makeMoveVector(const std::pair<int, int>& coords) const {
    int x_delta = 0;
    int y_delta = 0;

    if (coords.second == m_coords.second)
        x_delta = coords.first > m_coords.first ? 1 : -1;
    else if (coords.first == m_coords.first)
        y_delta = coords.second > m_coords.second ? 1 : -1;
    else {
        x_delta = coords.first > m_coords.first ? 1 : -1;
        y_delta = coords.second > m_coords.second ? 1 : -1;
    }

    return std::make_pair<int, int>(std::move(x_delta), std::move(y_delta));
}