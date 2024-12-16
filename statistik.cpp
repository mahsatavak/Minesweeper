#include "Statistik.h"
#include "mainwindow.h"
#include "ui_statistik.h"

Statistik::Statistik(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Statistik)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(7);
    QStringList headers = {"Zeilen (n)", "Spalten (m)", "Minen (k)",
                           "Gespielt", "Gewonnen", "Verloren", "Beste Zeit"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);
}



Statistik::~Statistik()
{
    delete ui;
}


void Statistik::setStatMap(const std::map<std::tuple<int,int,int>, StatRecord> &stats)
{
    m_stats = stats; // Kopie der übergebenen Daten
    populateTable();
}

void Statistik::populateTable()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(m_stats.size());

    int row = 0;
    for(const auto &pair : m_stats) {
        auto key = pair.first;        // std::tuple<int,int,int>
        auto record = pair.second;    // StatRecord

        int n = std::get<0>(key);
        int m = std::get<1>(key);
        int k = std::get<2>(key);

        // Je Eintrag (n,m,k) eine Zeile
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(n)));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(m)));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(k)));

        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(record.gamesPlayed)));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(record.gamesWon)));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(record.gamesLost)));

        QString bestTimeStr = (record.bestTime >= 0)
                                  ? QString("%1 s").arg(record.bestTime)
                                  : QString("-");
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(bestTimeStr));

        row++;
    }
}
