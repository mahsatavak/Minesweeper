#include "mainwindow.h"
#include "einstellung.h"
#include "qdebug.h"
#include "statistik.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <ctime>
#include <cstdlib>
#include <QLabel>
#include <QTimer>
#include <QSettings>
#include <tuple>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    isPaused = false;
    // **Initialwerte** (Default), falls der User nichts ändert
    ROWS = 10;
    COLS = 10;
    totalMines = 15;

    // Das Layout des Scrollbereichs mit dem Inhalt verknüpfen
    ui->scrollAreaWidgetContents->setLayout(ui->gridLayout);
    // Scrollrichtlinien einstellen
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // -- NEU: Statusbar-Labels erstellen
    labelMines = new QLabel(this);
    labelFlags = new QLabel(this);
    labelTime  = new QLabel(this);


    // Wir fügen die drei Labels in die Statuszeile ein,
    // z.B. im Format: "Minen: 15 | Marken: 0 | Zeit: 0s"
    ui->statusbar->addWidget(labelMines);
    ui->statusbar->addWidget(labelFlags);
    ui->statusbar->addWidget(labelTime);

    // Timer erzeugen und verbinden
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::onTimerTick);
    // Initialwert für Zeit
    elapsedSeconds = 0;

    // Buttons erstellen und im Grid platzieren
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            QPushButton *btn = new QPushButton(this);
            btn->setFixedSize(30, 30);
            btn->installEventFilter(this); // Eventfilter für Rechtsklick
            //ui->scrollAreaWidgetContents->layout()->addWidget(btn);
            ui->gridLayout->addWidget(btn, r, c);
            buttons[r][c] = btn;

            // Linksklick: mit Lambda row,col "capturen"
            connect(btn, &QPushButton::clicked, this, [=]() {
                // Nur aufdecken, wenn nicht markiert oder bereits aufgedeckt
                if (!board[r][c].isFlagged && !board[r][c].isRevealed) {
                    handleLeftClick(r, c);
                }
            });
        }
    }

    //Größe des Scrollbereich-Inhalts aktualisieren
    ui->scrollAreaWidgetContents->adjustSize();


    // Spielfeld initialisieren
    setupBoard();

    // Button verbinden
    connect(ui->Neu, &QPushButton::clicked, this, &MainWindow::onNeuClicked);
    connect(ui->Pause, &QPushButton::clicked, this, &::MainWindow::onPauseClicked);
    connect(ui->Beenden, &QPushButton::clicked, this, &::MainWindow::onBeendenClicked);

    // Menü-Aktionen verbinden
    connect(ui->actionEinstellung, &QAction::triggered, this, &MainWindow::openEinstellungen);
    connect(ui->actionStatistik, &QAction::triggered, this, &MainWindow::openStatistik);

    // Timer starten, damit die Zeit hochgezählt wird
    timer->start(1000); // alle 1000ms -> 1 Sekunde
}

MainWindow::~MainWindow()
{
    // Bevor das Fenster schließt: Statistik speichern
    saveStats();
    delete ui;
}

void MainWindow::setupBoard() {
    for (int r = 0; r < MAX_SIZE; ++r) {
        for (int c = 0; c < MAX_SIZE; ++c) {
            board[r][c].isMine = false;
            board[r][c].isRevealed = false;
            board[r][c].isFlagged = false;
            board[r][c].adjacentMines = 0;
            //updateButtonAppearance(r, c);
        }
    }

    placeMines();
    calculateAdjacents();
    // Alles aktualisieren
    for(int r = 0; r < ROWS; ++r) {
        for(int c = 0; c < COLS; ++c) {
            updateButtonAppearance(r, c);
        }
    }
    // Nach der Initialisierung aktualisieren wir sofort unsere Statuszeile.
    updateStatusBar();
}

void MainWindow::placeMines() {

    srand((unsigned)time(nullptr));
    int placed = 0;
    while (placed < totalMines) {
        int r = rand() % ROWS;
        int c = rand() % COLS;
        if (!board[r][c].isMine) {
            board[r][c].isMine = true;
            placed++;
        }
    }
}

void MainWindow::calculateAdjacents() {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            if (!board[r][c].isMine) {
                board[r][c].adjacentMines = countAdjacentMines(r, c);
            }
        }
    }
}

int MainWindow::countAdjacentMines(int row, int col) {
    int mines = 0;
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue;
            int nr = row + dr;
            int nc = col + dc;
            if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLS) {
                if (board[nr][nc].isMine) mines++;
            }
        }
    }
    return mines;
}

void MainWindow::revealCell(int row, int col) {
    if (board[row][col].isRevealed || board[row][col].isFlagged) return;

    board[row][col].isRevealed = true;

    if (board[row][col].isMine) {
        // verlorenes Spiel
        // Mine aufgedeckt -> Spiel vorbei
        buttons[row][col]->setText("M");
        buttons[row][col]->setStyleSheet("color: red;");
        gameOver();
        return;
    }

    int adj = board[row][col].adjacentMines;
    if (adj > 0) {
        buttons[row][col]->setText(QString::number(adj));
    } else {
        // Keine angrenzenden Minen -> benachbarte Felder automatisch aufdecken
        buttons[row][col]->setText("");
        revealAdjacentEmpty(row, col);
    }

    updateButtonAppearance(row, col);

     // Win-Check
    if(checkWinCondition()) {
        // Alles richtig aufgedeckt/markiert => Spiel gewonnen
        timer->stop();
        updateStats(ROWS, COLS, totalMines, /*isWon=*/true, elapsedSeconds);
        QMessageBox::information(this, "Gewonnen!", "Herzlichen Glückwunsch, du hast gewonnen!");
        // Alle Felder deaktivieren
        for(int r=0; r<ROWS; ++r){
            for(int c=0; c<COLS; ++c){
                buttons[r][c]->setEnabled(false);
            }
        }
    }

}

void MainWindow::revealAdjacentEmpty(int row, int col) {
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue;
            int nr = row + dr;
            int nc = col + dc;
            if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLS) {
                if (!board[nr][nc].isRevealed && !board[nr][nc].isMine) {
                    revealCell(nr, nc);
                }
            }
        }
    }
}

void MainWindow::updateButtonAppearance(int row, int col) {
    QPushButton *btn = buttons[row][col];
    if (board[row][col].isRevealed) {
        btn->setEnabled(false);
        btn->setStyleSheet("background-color: lightgray;");
    } else {
        btn->setEnabled(true);
        btn->setStyleSheet("");
        if (board[row][col].isFlagged) {
            btn->setText("F");
        } else {
            btn->setText("");
        }
    }
}

void MainWindow::gameOver() {
    // Alle Minen anzeigen
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            if (board[r][c].isMine && !board[r][c].isRevealed) {
                board[r][c].isRevealed = true;
                buttons[r][c]->setText("M");
                buttons[r][c]->setStyleSheet("color: black; background-color: lightgray;");
            }
        }
    }
    // Spiel als verloren in Statistik eintragen:
    updateStats(ROWS, COLS, totalMines, /*isWon=*/false, /*timeElapsed=*/elapsedSeconds);

    QMessageBox::information(this, "Game Over", "Du bist auf eine Mine getreten!");
    // **Hier: Alle Felder deaktivieren, damit der Spieler nicht mehr weiterklicken kann**
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            buttons[r][c]->setEnabled(false);
        }
    }
    timer->stop();
}

bool MainWindow::checkWinCondition()
{
    for(int r = 0; r < ROWS; ++r) {
        for(int c = 0; c < COLS; ++c) {
            if(board[r][c].isMine) {
                // Wenn es eine Mine ist, MUSS sie geflaggt sein
                if(!board[r][c].isFlagged) {
                    return false;
                }
            } else {
                // Wenn es keine Mine ist, MUSS es aufgedeckt sein
                if(!board[r][c].isRevealed) {
                    return false;
                }
            }
        }
    }
    // Wenn wir hier ankommen, ist alles perfekt markiert bzw. aufgedeckt
    return true;
}


bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::RightButton) {
            // Herausfinden, welcher Button geklickt wurde
            for (int r = 0; r < ROWS; ++r) {
                for (int c = 0; c < COLS; ++c) {
                    if (buttons[r][c] == obj) {
                        handleRightClick(r, c);
                        return true;
                    }
                }
            }
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::handleLeftClick(int row, int col) {

    if (!board[row][col].isFlagged && !board[row][col].isRevealed) {
        revealCell(row, col);
    }
}

void MainWindow::handleRightClick(int row, int col) {
    if (board[row][col].isRevealed) return;
    board[row][col].isFlagged = !board[row][col].isFlagged;
    updateButtonAppearance(row, col);

    // Nach jeder Änderung Flaggen/Marken neu zählen und Status aktualisieren
    updateStatusBar();

    // Win-Check:
    if(checkWinCondition()) {
        timer->stop();
        updateStats(ROWS, COLS, totalMines, true, elapsedSeconds);
        QMessageBox::information(this, "Gewonnen!", "Herzlichen Glückwunsch, du hast gewonnen!");
        // Alle Felder deaktivieren
        for(int r=0; r<ROWS; ++r){
            for(int c=0; c<COLS; ++c){
                buttons[r][c]->setEnabled(false);
            }
        }
    }
}

void MainWindow::onNeuClicked() {
    resetGame();
}

void MainWindow::resetGame() {
    setupBoard();
    // Buttons zurücksetzen
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            buttons[r][c]->setText("");
            buttons[r][c]->setEnabled(true);
            buttons[r][c]->setStyleSheet("");
        }
    }
    // Timer zurücksetzen
    elapsedSeconds = 0;

    // optional: Timer neustarten (falls Du ihn während Game Over pausierst, z.B.)
    // timer->start(1000);

    // Statuszeile aktualisieren
    updateStatusBar();
}

/**
 * updateStatusBar
 * Aktualisiert die Anzeigen für Minenanzahl, gesetzte Flaggen und vergangene Zeit.
 */
void MainWindow::updateStatusBar()
{
    // Anzahl Minen
    labelMines->setText(QString("Minen: %1").arg(totalMines));

    // Anzahl Flaggen ermitteln
    int flagCount = 0;
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            if (board[r][c].isFlagged) {
                flagCount++;
            }
        }
    }

    // Flaggen-Anzeige, wenn flagCount > totalMines -> Text in Rot, sonst Blau
    QString flagsText = QString("Marken: %1").arg(flagCount);
    labelFlags->setText(flagsText);

    if (flagCount > totalMines) {
        labelFlags->setStyleSheet("color: red;");
    } else {
        labelFlags->setStyleSheet("color: blue;");
    }

    // Zeit
    labelTime->setText(QString("Zeit: %1s").arg(elapsedSeconds));
}

/**
 * onTimerTick
 * Wird jede Sekunde vom Timer aufgerufen. Erhöht die vergangene Zeit und aktualisiert die Statuszeile.
 */
void MainWindow::onTimerTick()
{
    elapsedSeconds++;
    updateStatusBar();
}

void MainWindow::onPauseClicked()
{
    isPaused = !isPaused;
    qDebug() << "Pause-Status:" << isPaused;
    if (isPaused) {

        qDebug() << "Pause-Button wurde geklickt.";
        ui->Pause->setText("Fortsetzen");   // Button-Beschriftung ändern

        // Timer anhalten, damit die Zeit in der Statuszeile "eingefroren" wird
        timer->stop();
        // Gesamtes Spielfeld verstecken
        ui->scrollArea->hide();

    } else {
        ui->Pause->setText("Pause"); // Button-Beschriftung wieder zurück
        // Timer wieder starten
        timer->start(1000);

        // Spielfeld wieder anzeigen
        ui->scrollArea->show();
    }
}


void MainWindow::onBeendenClicked()
{
    // Spiel wird "verloren" gewertet -> Timer stoppen
    timer->stop();

    // Alle Felder aufdecken
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {

            // Fall 1: Feld enthält eine Mine
            if (board[r][c].isMine) {
                if (board[r][c].isFlagged) {
                    // korrekt markierte Mine -> Farbe blau
                    buttons[r][c]->setText("F");
                    buttons[r][c]->setStyleSheet("color: blue; background-color: lightgray;");
                } else {
                    // Mine nicht geflaggt -> einfach "M" anzeigen
                    buttons[r][c]->setText("M");
                    buttons[r][c]->setStyleSheet("color: black; background-color: lightgray;");
                }
            }
            // Fall 2: Feld enthält keine Mine
            else {
                if (board[r][c].isFlagged) {
                    // falsch gesetzte Flagge -> rot
                    buttons[r][c]->setText("F");
                    buttons[r][c]->setStyleSheet("color: red; background-color: lightgray;");
                } else {
                    // Regulär aufdecken: Zahl oder leer
                    int adj = board[r][c].adjacentMines;
                    if (adj > 0) {
                        buttons[r][c]->setText(QString::number(adj));
                    } else {
                        buttons[r][c]->setText("");
                    }
                    buttons[r][c]->setStyleSheet("background-color: lightgray;");
                }
            }

            // Deaktiviere den Button, damit man nicht mehr weiterklicken kann
            buttons[r][c]->setEnabled(false);
            board[r][c].isRevealed = true;
        }
    }

    //Zählt immer als verloren
    updateStats(ROWS, COLS, totalMines, /*isWon=*/false, elapsedSeconds);
    QMessageBox::information(this, "Beendet", "Spiel wurde abgebrochen und als verloren gewertet.");

}


// Diese Methode reißt das alte Spielfeld ab und erstellt ein neues
void MainWindow::updateBoard(int newRows, int newCols, int newMines)
{
    // Timer stoppen, Zeit resetten
    timer->stop();
    elapsedSeconds = 0;

    // Alte Buttons entfernen
    for(int r = 0; r < ROWS; ++r) {
        for(int c = 0; c < COLS; ++c) {
            // Buttons aus Layout lösen und löschen
            ui->gridLayout->removeWidget(buttons[r][c]);
            // ui->scrollAreaWidgetContents->layout()->removeWidget(buttons[r][c]);
            delete buttons[r][c];
            buttons[r][c] = nullptr;
        }
    }

    // Neue Standardwerte setzen
    ROWS = newRows;
    COLS = newCols;
    totalMines = newMines;

    // Neue Buttons erstellen
    for(int r = 0; r < ROWS; ++r) {
        for(int c = 0; c < COLS; ++c) {
            QPushButton *btn = new QPushButton(this);
            btn->setFixedSize(30,30);
            btn->installEventFilter(this);
            ui->gridLayout->addWidget(btn, r, c);
            //ui->scrollAreaWidgetContents->layout()
            buttons[r][c] = btn;

            connect(btn, &QPushButton::clicked, this, [=](){
                if(!board[r][c].isFlagged && !board[r][c].isRevealed) {
                    revealCell(r, c);
                }
            });
        }
    }

    // Neues Setup
    setupBoard();
    // ÄNDERUNG: Scrollbereich-Inhalt anpassen
    ui->scrollAreaWidgetContents->adjustSize();

    // Timer wieder starten
    timer->start(1000);
    updateStatusBar();
}

// ---------------- Menü-Aktionen -----------------
void MainWindow::openEinstellungen()
{
    Einstellung dlg(this);

    // Hier optional: Defaultwerte für Rows, Cols, Mines setzen
    dlg.setRows(ROWS);     // Falls ROWS aktuell 10 ist
    dlg.setCols(COLS);     // Falls COLS aktuell 10 ist
    dlg.setMines(totalMines); // Falls wir z. B. 15 Minen haben

    // Zeige den Dialog modally
    if (dlg.exec() == QDialog::Accepted) {
        // Benutzer hat OK geklickt
        int newRows = dlg.rows();
        int newCols = dlg.cols();
        int newMines = dlg.mines();

        // Jetzt das Spielfeld entsprechend neu aufbauen
        updateBoard(newRows, newCols, newMines);
    }
}

void MainWindow::openStatistik()
{
    // Erzeuge den Statistikdialog
    Statistik dlg(this);
    // Übergebe unsere statsMap
    dlg.setStatMap(statsMap);
    dlg.exec();
}

// ---------------- Statistik-Funktionen ---------------

void MainWindow::updateStats(int n, int m, int k, bool isWon, int timeElapsed)
{
    auto key = std::make_tuple(n, m, k);
    StatRecord &rec = statsMap[key]; // falls nicht vorhanden, wird er angelegt

    rec.gamesPlayed++;
    if(isWon) {
        rec.gamesWon++;
        if(rec.bestTime == -1 || timeElapsed < rec.bestTime) {
            rec.bestTime = timeElapsed;
        }
    } else {
        rec.gamesLost++;
    }
}

// Speichern der Statistik in QSettings
void MainWindow::saveStats()
{
    // z.B. Organisations-/App-Name, kann beliebig sein
    QSettings settings("MeineFirma", "MinesweeperApp");

    // Damit alte Daten gelöscht werden (alternativ: clear vor dem Speichern)
    settings.beginGroup("Statistics");
    settings.remove(""); // alles in "Statistics" löschen

    int index = 0;
    for(const auto &pair : statsMap) {
        auto key = pair.first;
        auto rec = pair.second;

        int n = std::get<0>(key);
        int m = std::get<1>(key);
        int k = std::get<2>(key);

        // Wir speichern jeden Datensatz in einem "Unterordner"
        QString recordPrefix = QString("record%1/").arg(index++);
        settings.setValue(recordPrefix + "n", n);
        settings.setValue(recordPrefix + "m", m);
        settings.setValue(recordPrefix + "k", k);
        settings.setValue(recordPrefix + "gamesPlayed", rec.gamesPlayed);
        settings.setValue(recordPrefix + "gamesWon",    rec.gamesWon);
        settings.setValue(recordPrefix + "gamesLost",   rec.gamesLost);
        settings.setValue(recordPrefix + "bestTime",    rec.bestTime);
    }
    settings.endGroup();
}

// Laden der Statistik aus QSettings
void MainWindow::loadStats()
{
    statsMap.clear(); // Map leeren, dann aus Settings neu füllen

    QSettings settings("MeineFirma", "MinesweeperApp");
    settings.beginGroup("Statistics");

    // Jeder Datensatz heißt "record0", "record1", etc.
    // Wir müssen herausfinden, wie viele "recordXX" es gibt.
    QStringList childGroups = settings.childGroups();
    for(const QString &grp : childGroups) {
        settings.beginGroup(grp); // z. B. "record0"

        int n = settings.value("n", 10).toInt();
        int m = settings.value("m", 10).toInt();
        int k = settings.value("k", 15).toInt();

        StatRecord rec;
        rec.gamesPlayed = settings.value("gamesPlayed", 0).toInt();
        rec.gamesWon    = settings.value("gamesWon", 0).toInt();
        rec.gamesLost   = settings.value("gamesLost", 0).toInt();
        rec.bestTime    = settings.value("bestTime", -1).toInt();

        statsMap[std::make_tuple(n,m,k)] = rec;

        settings.endGroup(); // z. B. /record0
    }
    settings.endGroup();
}



