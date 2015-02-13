#ifndef STOCKWIDGET_H
#define STOCKWIDGET_H

#include <QWidget>
class Stock;
class QLabel;
class QWidget;

class StockWidget : public QWidget
{
private:
    QLabel* _price;
    QLabel* _buy;
    QLabel* _sell;
public:
    StockWidget(Stock stock);
    void Update(double price);
    ~StockWidget();
};

#endif // STOCKWIDGET_H
