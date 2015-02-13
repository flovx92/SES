#include "StockWidget.h"
#include "Stock.h"
#include <QLabel>
#include <QGridLayout>
#include <QWidget>
#include <QPushButton>

StockWidget::StockWidget(Stock stock) : QWidget()
{
    vector<double> values =  stock.GetPrices();
    QPushButton* name = new QPushButton();
    name->setText(stock.GetCompanyName());
    QString price;
    _price = new QLabel();
    price.setNum(stock.GetPrice());
    _price -> setText("Price : $"+price);
    QString buy;
    _buy = new QLabel();
    buy.setNum(stock.GetBuyPrice());
    _buy -> setText("Buy : $"+buy);


    QGridLayout* layout = new QGridLayout;
    layout-> addWidget(name,0,0);
    layout-> addWidget(_price,1,1);
    layout->addWidget(_buy,1,2);
    this->setLayout(layout);
}

void StockWidget::Update(double price)
{

    QString price_tag;
    price_tag.setNum(price);
    _price -> setText("Price : $"+price_tag);


}

StockWidget::~StockWidget()
{

}

