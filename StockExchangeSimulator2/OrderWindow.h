#ifndef ORDERWINDOW_H
#define ORDERWINDOW_H

#include <QWidget>
#include <QStandardItem>
#include "Order.h"
#include <vector>
using namespace std;

class OrderWindow : public QWidget
{
    Q_OBJECT
public:
    explicit OrderWindow();
    void Update(vector<Order>);
    ~OrderWindow();
private:
    QStandardItemModel* _model;


signals:

public slots:
};

#endif // ORDERWINDOW_H
