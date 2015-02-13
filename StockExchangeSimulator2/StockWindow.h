#ifndef STOCKWINDOW_H
#define STOCKWINDOW_H

#include <QWidget>
class QLabel;
class QLCDNumber;
class StockExchange;
class StockWidget;
#include <vector>
using namespace std;

class StockWindow : public QWidget
{

    Q_OBJECT
private:
    StockExchange* _pse;
    QLCDNumber* _date;
    vector<QLabel*> _price;
    vector<QLabel*> _buy;
    vector<QLabel*> _sell;
public slots:
    void Update();
public:
    StockWindow(StockExchange* pdata);
    ~StockWindow();

};

#endif // STOCKWINDOW_H
