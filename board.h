#ifndef BOARD_H
#define BOARD_H

#include <QObject>


class Board : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Figure currentPlayer MEMBER m_currentPlayer NOTIFY currentPlayerChanged)
    Q_PROPERTY(quint32 size MEMBER m_size CONSTANT)
    Q_PROPERTY(GameState gameState MEMBER m_gameState NOTIFY gameStateChanged)

public:
    enum Figure {
        Empty = -1,
        Zero = 0,
        Cross = 1
    };

    Q_ENUM(Figure)

    enum GameState {
        Idle,
        Playing,
        Tie,
        PlayerXWin,
        PlayerOWin
    };

    Q_ENUM(GameState)

    explicit Board(QObject *parent = nullptr);

    Q_INVOKABLE Figure move(int index);
    Q_INVOKABLE void start();

signals:
    void currentPlayerChanged();
    void gameStateChanged();

private:
    void updateGameState();

private:
    const int m_size = 5;
    Figure m_currentPlayer = Figure::Cross;
    int m_movesLeft = m_size * m_size;
    std::vector<int> m_gameBoard;
    GameState m_gameState = GameState::Idle;
};

#endif // BOARD_H
