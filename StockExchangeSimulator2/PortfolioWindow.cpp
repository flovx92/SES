#include "PortfolioWindow.h"
#include "Portfolio.h"
#include <vector>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QTableView>
#include <QLabel>
#include "Stock.h"
#include "Window.h"
using namespace std;

PortfolioWindow::PortfolioWindow(vector<Portfolio*> portfolio, vector<Stock> stocks) : QWidget()
{
    setFixedSize(646,200);
    setWindowTitle("Portfolio");


    QVBoxLayout* layout = new QVBoxLayout;

    QStringList col_label;
    col_label << "Quantity" << "Medium Price" << "P&L" << "Earnings" << "Dividends";

    QStringList row_label;
    int nb_stocks = stocks.size();

    for(int i = 0;i < nb_stocks;i++)
    {
        row_label << (stocks[i]).GetCompanyName();
    }

    _model = new QStandardItemModel(5, 3);
    _model->setHorizontalHeaderLabels(col_label);
    _model->setVerticalHeaderLabels(row_label);

    for(int i = 0; i < nb_stocks; i++)
    {
        Portfolio* port = portfolio[i];

        double number = port->GetNumber();
        QStandardItem* item_i_1 = CreateItem(number);
        _model->setItem(i,0,item_i_1);

        QStandardItem* item_i_2 = CreateItem(port->GetMedPrice());
        _model->setItem(i,1,item_i_2);

        QStandardItem* item_i_3 = CreateItem(0);
        _model->setItem(i,2,item_i_3);

        QStandardItem* item_i_4 = CreateItem(0);
        _model->setItem(i,3,item_i_4);

        QStandardItem* item_i_5 = CreateItem(0);
        _model->setItem(i,4,item_i_5);
    }

    QTableView *vue = new QTableView;
    vue->setModel(_model);

    layout->addWidget(vue);

    setLayout(layout);
}

void PortfolioWindow::Update(vector<Portfolio*> portfolio,vector<Stock> stocks)
{
    for(int i = 0; i < (int) portfolio.size(); i++)
    {
        Portfolio* port = portfolio[i];
        double price = stocks[i].GetPrice();

        double number = port->GetNumber();
        QStandardItem* item_i_1 = CreateItem(number);
        _model->setItem(i,0,item_i_1);

        QStandardItem* item_i_2 = CreateItem(port->GetMedPrice());
        _model->setItem(i,1,item_i_2);

        double PL = number*(price - port->GetMedPrice());
        QStandardItem* item_i_3 = CreateItem(PL);
        _model->setItem(i,2,item_i_3);

        QStandardItem* item_i_4 = CreateItem(port->GetEarnings());
        _model->setItem(i,3,item_i_4);

        QStandardItem* item_i_5 = CreateItem(port->GetDividends());
        _model->setItem(i,4,item_i_5);
    }

}


PortfolioWindow::~PortfolioWindow()
{

}

