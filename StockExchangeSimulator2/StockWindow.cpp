#include "StockWindow.h"
#include "StockExchange.h"
#include <QLCDNumber>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include <Stock.h>
#include <QString>
#include <vector>
#include <QList>

using namespace std;

StockWindow::StockWindow(StockExchange* pse) : QWidget()
{


    setFixedSize(450,550);
    setWindowTitle("Stocks");

    _pse = pse;
    _date = new QLCDNumber(this);
    _date->display(0);
    _date->setSegmentStyle(QLCDNumber::Flat);

    QLabel* time_label = new QLabel();
    time_label -> setText("Time :");
    QLabel* stock_label = new QLabel();
    stock_label -> setText("Stocks :");


    QGridLayout* layout = new QGridLayout;
    layout->addWidget(time_label,0,0);
    layout->addWidget(_date,0,1);
    layout->addWidget(stock_label,2,0);

    int nb = _pse->GetStocks().size();


    for(int i = 0;i<nb;i++)
    {

        Stock stock = _pse->GetStocks()[i];

        QPushButton* name = new QPushButton();
        name->setText(stock.GetCompanyName());

        QString id;
        id.setNum((stock.GetCompanyID()));
        QLabel* id_lab = new QLabel();
        id_lab -> setText("Stock ID : " + id);

        QString price;
        price.setNum(stock.GetPrice());
        QLabel* price_lab = new QLabel();
        _price.push_back(price_lab);
        _price[i] -> setText("Price : $" + price);


        QString buy;
        buy.setNum(stock.GetBuyPrice());
        QLabel* buy_lab = new QLabel();
        _buy.push_back(buy_lab);
        _buy[i] -> setText("Buy : $"+ buy);

        QString sell;
        sell.setNum(stock.GetSellPrice());
        QLabel* sell_lab = new QLabel();
        _sell.push_back(sell_lab);
        _sell[i] -> setText("Sell : $"+ sell);

        layout-> addWidget(name,2*i+3,0);
        layout-> addWidget(id_lab,2*i+3,1);
        layout-> addWidget(_price[i],2*i+4,1);
        layout-> addWidget(_buy[i],2*i+4,2);
        layout-> addWidget(_sell[i],2*i+4,3);

    }

    this->setLayout(layout);
}

void StockWindow::Update()
{

    int date = _pse->GetTime();
    _date->display(date);

    int nb = _price.size();
    for(int i = 0; i<nb; i++)
    {
        Stock stock = _pse->GetStocks()[i];
        QString price;
        price.setNum(stock.GetPrice());
        _price[i]->setText("Price : $" + price);
        QString buy;
        buy.setNum(stock.GetBuyPrice());
        _buy[i]->setText("Buy : $" + buy);
        QString sell;
        sell.setNum(stock.GetSellPrice());
        _sell[i]->setText("Sell : $" + sell);
    }



}

StockWindow::~StockWindow()
{
    delete _pse;
    delete _date;


}

