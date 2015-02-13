#ifndef PORTFOLIOWINDOW_H
#define PORTFOLIOWINDOW_H

#include <QWidget>
#include "Portfolio.h"
class Stock;
#include <vector>
using namespace std;
#include <QStandardItem>

class PortfolioWindow : public QWidget
{
    Q_OBJECT
public:
    explicit PortfolioWindow(vector<Portfolio*>,vector<Stock>);
    void Update(vector<Portfolio*>,vector<Stock>);
    ~PortfolioWindow();
private:
    QStandardItemModel* _model;

signals:

public slots:
};



#endif // PORTFOLIOWINDOW_H
