#include "board.h"

#include <QDebug>

Board::Board(QObject *parent)
    : QObject{parent}
    , m_gameBoard(m_movesLeft, Figure::Empty)
{

}

Board::Figure Board::move(int index)
{
    Q_ASSERT(index >= 0 && index < m_gameBoard.size());

    if (m_gameBoard.at(index) != Figure::Empty) {
        return static_cast<Board::Figure>(m_gameBoard[index]);
    }

    m_gameBoard[index] = m_currentPlayer;
    m_movesLeft--;

    updateGameState();
    return static_cast<Board::Figure>(m_gameBoard[index]);
}

void Board::start()
{
    m_currentPlayer = Figure::Cross;
    m_movesLeft = m_size * m_size;
    m_gameBoard = std::vector<int>(m_movesLeft, Figure::Empty);
    m_gameState = GameState::Playing;
    emit gameStateChanged();
    emit currentPlayerChanged();
}

void Board::updateGameState()
{
    // check rows
    for (int i = 0; i < m_size * m_size; i+=5) {
        if (m_gameBoard[i + 0] == Figure::Cross &&
                m_gameBoard[i + 1] == Figure::Cross &&
                m_gameBoard[i + 2] == Figure::Cross &&
                m_gameBoard[i + 3] == Figure::Cross &&
                m_gameBoard[i + 4] == Figure::Cross ) {
            m_gameState = GameState::PlayerXWin;

            emit gameStateChanged();
            return;
        } else if (m_gameBoard[i + 0] == Figure::Zero &&
                   m_gameBoard[i + 1] == Figure::Zero &&
                   m_gameBoard[i + 2] == Figure::Zero &&
                   m_gameBoard[i + 3] == Figure::Zero &&
                   m_gameBoard[i + 4] == Figure::Zero) {
            m_gameState = GameState::PlayerOWin;

            emit gameStateChanged();
            return;
        }
    }

    // check columns
    for (int i = 0; i <  m_size * m_size; ++i) {
        if (m_gameBoard[i + 0] == Figure::Cross &&
                m_gameBoard[i + 5] == Figure::Cross &&
                m_gameBoard[i + 10] == Figure::Cross &&
                m_gameBoard[i + 15] == Figure::Cross &&
                m_gameBoard[i + 20] == Figure::Cross ) {
            m_gameState = GameState::PlayerXWin;

            emit gameStateChanged();
            return;
        } else if (m_gameBoard[i + 0] == Figure::Zero &&
                   m_gameBoard[i + 5] == Figure::Zero &&
                   m_gameBoard[i + 10] == Figure::Zero &&
                   m_gameBoard[i + 15] == Figure::Zero &&
                   m_gameBoard[i + 20] == Figure::Zero) {
            m_gameState = GameState::PlayerOWin;

            emit gameStateChanged();
            return;
        }
    }

    // check diagonals
    if ((m_gameBoard[0] == Figure::Cross &&
         m_gameBoard[6] == Figure::Cross &&
         m_gameBoard[12] == Figure::Cross &&
         m_gameBoard[18] == Figure::Cross &&
         m_gameBoard[24] == Figure::Cross ) ||
            (m_gameBoard[4] == Figure::Cross &&
             m_gameBoard[8] == Figure::Cross &&
             m_gameBoard[12] == Figure::Cross &&
             m_gameBoard[16] == Figure::Cross &&
             m_gameBoard[20] == Figure::Cross )) {
        m_gameState = GameState::PlayerXWin;

        emit gameStateChanged();
        return;
    } else if ((m_gameBoard[0] == Figure::Zero &&
                m_gameBoard[6] == Figure::Zero &&
                m_gameBoard[12] == Figure::Zero &&
                m_gameBoard[18] == Figure::Zero &&
                m_gameBoard[24] == Figure::Zero ) ||
               (m_gameBoard[4] == Figure::Zero &&
                m_gameBoard[8] == Figure::Zero &&
                m_gameBoard[12] == Figure::Zero &&
                m_gameBoard[16] == Figure::Zero &&
                m_gameBoard[20] == Figure::Zero )) {
        m_gameState = GameState::PlayerOWin;

        emit gameStateChanged();
        return;
    }

    if (m_movesLeft == 0) {
        m_gameState = GameState::Tie;
        emit gameStateChanged();
        return;
    }

    m_currentPlayer = m_currentPlayer == Figure::Cross ? Figure::Zero
                                                       : Figure::Cross;
    emit currentPlayerChanged();
}

