#include "gamemanager.h"

#include <iostream>

GameManager::GameManager() {
    turn = Side::White;
    initField();
}

void GameManager::initField() {
    field[0][0] = new Rook(std::make_pair(0, 0), Side::Black);
    field[0][7] = new Rook(std::make_pair(7, 0), Side::Black);
    field[7][0] = new Rook(std::make_pair(0, 7), Side::White);
    field[7][7] = new Rook(std::make_pair(7, 7), Side::White);

    field[0][1] = new Knight(std::make_pair(1, 0), Side::Black);
    field[0][6] = new Knight(std::make_pair(6, 0), Side::Black);
    field[7][1] = new Knight(std::make_pair(1, 7), Side::White);
    field[7][6] = new Knight(std::make_pair(6, 7), Side::White);

    field[0][2] = new Bishop(std::make_pair(2, 0), Side::Black);
    field[0][5] = new Bishop(std::make_pair(5, 0), Side::Black);
    field[7][2] = new Bishop(std::make_pair(2, 7), Side::White);
    field[7][5] = new Bishop(std::make_pair(5, 7), Side::White);

    field[0][3] = new Queen(std::make_pair(3, 0), Side::Black);
    field[7][3] = new Queen(std::make_pair(3, 7), Side::White);

    white_king = new King(std::make_pair(4, 7), Side::White);
    black_king = new King(std::make_pair(4, 0), Side::Black);

    field[0][4] = black_king;
    field[7][4] = white_king;

    for (int i = 0; i < 8; ++i) {
        field[1][i] = new Pawn(std::make_pair(i, 1), Side::Black);
        field[6][i] = new Pawn(std::make_pair(i, 6), Side::White);
    }

    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 8; ++j)
            black_figures.push_back(field[i][j]);

    for (int i = 6; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            white_figures.push_back(field[i][j]);

    for (int i = 2; i < 6; ++i)
        for (int j = 0; j < 8; ++j)
            field[i][j] = nullptr;

}

std::array<std::array<AbstractFigure *, 8>, 8> GameManager::getField(void) const {
    return field;
}

Side GameManager::whoseTurn() const {
    return turn;
}

Turn GameManager::makeTurn(const std::pair<int, int>& from, const std::pair<int, int>& to) {
    if (!checkCheckWrapper(from, to).empty())
        return {Outcome::Invalid, nullptr};

    std::pair<int, int> *coords = new std::pair<int, int>(to);
    Turn turn_outcome = field[from.second][from.first]->move(field, *coords);

    if (turn_outcome.outcome == Outcome::Invalid)
        return turn_outcome;

    if (turn_outcome.outcome == Outcome::Eat) {
        std::vector<AbstractFigure *> figures = turn == Side::White ? black_figures : white_figures;
        for (auto it = figures.begin(); it != figures.end(); ++it)
            if (!(*it))
                figures.erase(it);
    }

    turn = turn == Side::White ? Side::Black : Side::White;
    King *king = turn == Side::White ? white_king : black_king;
    std::vector<AbstractFigure *> check_figures = checkCheckWrapper(king->getCoords(), king->getCoords());

    if (!check_figures.empty()) {
        if (checkMate(check_figures, king))
            return {Outcome::Mate, turn_outcome.eaten};
        else
            return {Outcome::Check, turn_outcome.eaten};
    }

    return turn_outcome;
}

std::vector<AbstractFigure *> GameManager::checkCheckWrapper(const std::pair<int, int>& from,
                                                             const std::pair<int, int>& to) {
    AbstractFigure *figure_from = field[from.second][from.first];
    AbstractFigure *figure_to = field[to.second][to.first];
    King *king = figure_from->getSide() == Side::White ? white_king : black_king;
    std::pair<int, int> king_coords = figure_from->getType() == Type::King ? to : king->getCoords();

    field[from.second][from.first] = nullptr;
    field[to.second][to.first] = figure_from;

    std::vector<AbstractFigure *> check_figures = checkCheck(king->getSide(), king_coords);

    field[from.second][from.first] = figure_from;
    field[to.second][to.first] = figure_to;

    return check_figures;
}

std::vector<AbstractFigure *> GameManager::checkCheck(Side side, const std::pair<int, int>& king_coords) {
    Turn turn;
    std::vector<AbstractFigure *> check_figures;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            AbstractFigure *figure = field[i][j];

            if (figure && figure->getSide() != side) {
                turn = figure->checkMove(field, king_coords);

                if (turn.outcome == Outcome::Eat)
                    check_figures.push_back(figure);
            }
        }
    }

    return check_figures;
}

bool GameManager::checkMate(std::vector<AbstractFigure *> checkFigures, King *king) {
    // check if king can move
    std::pair<int, int> king_coords = king->getCoords();

    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            std::pair<int, int> to = {king_coords.first + i, king_coords.second + j};
            if (to.first > 7 || to.first < 0 || to.second > 7 || to.second < 0)
                continue;
            Turn turn = king->checkMove(field, to);
            if (turn.outcome == Outcome::Move || turn.outcome == Outcome::Eat) {
                if (checkCheckWrapper(king_coords, to).empty())
                    return false;
            }
        }
    }

    // check if other figure can help
    std::vector<std::pair<int, int>> defence_tiles;
    for (AbstractFigure *figure : checkFigures) {
        if (figure->getType() == Type::Pawn || figure->getType() == Type::Knight)
            defence_tiles.push_back(figure->getCoords());
        else {
            std::pair<int, int> move_vector = chooseMoveVector(figure, king->getCoords());
            std::pair<int, int> coords = figure->getCoords();

            while (coords.first != king_coords.first && coords.second != king_coords.second) {
                defence_tiles.push_back(coords);
                coords.first += move_vector.first;
                coords.second += move_vector.second;
            }
        }
    }

    std::vector<AbstractFigure *> figures = turn == Side::White ? white_figures : black_figures;
    for (AbstractFigure *figure : figures) {
        for (const auto& tile : defence_tiles) {
            Turn turn = figure->checkMove(field, tile);
            if (turn.outcome == Outcome::Move || turn.outcome == Outcome::Eat) {
                if (checkCheckWrapper(figure->getCoords(), tile).empty())
                    return false;
            }
        }
    }

    return true;
}

std::pair<int, int> GameManager::chooseMoveVector(AbstractFigure *figure,
                                                  std::pair<int, int> king_coords) const {
    if (figure->getType() == Type::Bishop)
        return reinterpret_cast<Bishop *>(figure)->makeMoveVector(king_coords);
    else if (figure->getType() == Type::Rook)
        return reinterpret_cast<Rook *>(figure)->makeMoveVector(king_coords);
    else if (figure->getType() == Type::Queen)
        return reinterpret_cast<Queen *>(figure)->makeMoveVector(king_coords);
    else {
        throw std::invalid_argument("WTF chooseMoveVector with wrong figure type");
    }
}
