#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qmessagebox.h"
#include <QMainWindow>
#include <QPushButton>
#include <QMouseEvent>
#include <QTimer>
#include "einstellung.h"


// Struktur zur Speicherung der Statistik pro (n, m, k)
struct StatRecord {
    int gamesPlayed = 0;
    int gamesWon = 0;
    int gamesLost = 0;
    int bestTime = -1; // -1 bedeutet: noch kein Sieg
};


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


    struct Cell {
        bool isMine = false;
        bool isRevealed = false;
        bool isFlagged = false;
        int adjacentMines = 0;
    };


    // Datenstruktur für unsere Statistik
    std::map<std::tuple<int,int,int>, StatRecord> statsMap;

    // *** ACHTUNG ***
    // mit ROWS und COLS als variablen Werten können statische 2D-Arrays problematisch werden.
    // Du müsstest "Cell**" oder std::vector<std::vector<Cell>> verwenden.
    // Fürs DEMO belassen wir hier ein gewisses Maximum z. B. 50 x 50.
    static const int MAX_SIZE = 100;
    Cell board[MAX_SIZE][MAX_SIZE];
    QPushButton* buttons[MAX_SIZE][MAX_SIZE];

    // Labels für die Statuszeile:
    QLabel *labelMines;   // Zeigt die Gesamtanzahl der Minen
    QLabel *labelFlags;   // Zeigt die Anzahl gesetzter Flaggen
    QLabel *labelTime;    // Zeigt die vergangene Spielzeit

    // Zeit-Tracking:
    QTimer *timer;        // Timer, der jede Sekunde ein Signal sendet
    int elapsedSeconds;   // Variable, in der wir die vergangene Zeit zählen

    // Speichern, wie viele Minen tatsächlich gesetzt wurden
    int ROWS;
    int COLS;
    int totalMines;
    bool isPaused;  // merkt sich, ob das Spiel gerade pausiert ist

    void setupBoard();
    void placeMines();
    void calculateAdjacents();
    int countAdjacentMines(int row, int col);

    void revealCell(int row, int col);
    void revealAdjacentEmpty(int row, int col);
    void updateButtonAppearance(int row, int col);
    void gameOver();
    void resetGame();
    bool checkWinCondition();

    // Hilfsfunktionen, um Statuszeile zu aktualisieren
    void updateStatusBar();
    void onTimerTick();
    // Updatet das gesamte Board auf neue Dimensionen
    void updateBoard(int newRows, int newCols, int newMines);

    // --- Methoden zum Speichern/Laden der Statistik ---
    void loadStats();
    void saveStats();
    // Methode, um die Statistik nach jedem Spiel zu aktualisieren
    void updateStats(int n, int m, int k, bool isWon, int timeElapsed);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void handleLeftClick(int row, int col);
    void handleRightClick(int row, int col);

    // Klicks auf Buttons
    void onNeuClicked();
    void onPauseClicked();    // Slot für den Pause-Button
    void onBeendenClicked();  // Slot für den Beenden-Button

    // Menü-Aktionen
    void openEinstellungen(); // Slot, um den Einstellungsdialog zu öffnen
    void openStatistik();
};

#endif // MAINWINDOW_H
