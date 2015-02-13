#ifndef BONDWINDOW_H
#define BONDWINDOW_H

#include <QWidget>
#include <QStandardItemModel>
class Treasure;
class Bond;
#include <vector>
#include <QLabel>
using namespace std;

class BondWindow : public QWidget
{
    Q_OBJECT
public:
    explicit BondWindow(Treasure* ptres);
    void Update(vector<Bond>,Treasure*);
    ~BondWindow();

private:
    QStandardItemModel* _model;
    QLabel* _rate_lab;
signals:

public slots:
};

#endif // BONDWINDOW_H
