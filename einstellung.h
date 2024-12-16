#ifndef EINSTELLUNG_H
#define EINSTELLUNG_H

#include <QDialog>

namespace Ui {
class Einstellung;
}

class Einstellung : public QDialog
{
    Q_OBJECT

public:
    explicit Einstellung(QWidget *parent = nullptr);
    ~Einstellung();

// Getter für die User-Eingabe
    int rows() const;
    int cols() const;
    int mines() const;

// Getter für die User-Eingaben
    void setRows(int r);
    void setCols(int c);
    void setMines(int m);

private:
    Ui::Einstellung *ui;
};

#endif // EINSTELLUNG_H
