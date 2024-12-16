#ifndef STATISTIK_H
#define STATISTIK_H

#include <QDialog>
#include <map>
#include <tuple>

#include "mainwindow.h"


namespace Ui {
class Statistik;
}

class Statistik : public QDialog
{
    Q_OBJECT

public:
    explicit Statistik(QWidget *parent = nullptr);
    ~Statistik();
    // Übergibt man die gesammelte Statistik (Map) an den Dialog:
    void setStatMap(const std::map<std::tuple<int,int,int>, StatRecord> &stats);

private:
    Ui::Statistik *ui;
    // Lokale Kopie der Statistikdaten
    std::map<std::tuple<int,int,int>, StatRecord> m_stats;

    void populateTable(); // Füllt das QTableWidget mit Daten
};

#endif // STATISTIK_H
