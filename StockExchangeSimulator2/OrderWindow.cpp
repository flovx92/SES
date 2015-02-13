#include "OrderWindow.h"
#include <QVBoxLayout>
#include <QTableView>
#include <QStandardItem>
#include "PortfolioWindow.h"
#include "Window.h"

OrderWindow::OrderWindow() : QWidget()
{

    setFixedSize(646,200);
    setWindowTitle("Orders");


    QVBoxLayout* layout = new QVBoxLayout;

    QStringList col_label;
    col_label << "ID" << "Stock ID" << "Type" << "Number" << "Price";

    _model = new QStandardItemModel(5, 3);
    _model->setHorizontalHeaderLabels(col_label);


    QTableView *vue = new QTableView;
    vue->setModel(_model);

    layout->addWidget(vue);

    setLayout(layout);
}

void OrderWindow::Update(vector<Order> orders)
{
    int n = orders.size();
    _model->setRowCount(n);
    for(int i = 0; i < n; i++)
    {
        Order order = orders[i];

        int id = order.GetId();
        QStandardItem* item = CreateItem(id);
        _model->setItem(i,0,item);

        int stock_id = order.GetStockId();
        QStandardItem* item2 = CreateItem(stock_id);
        _model->setItem(i,1,item2);

        bool is_buy = order.GetIsBuy();
        QStandardItem* item3 = new QStandardItem();
        if(is_buy)
        {
            item3->setText("Buy");
        }
        else
        {
            item3->setText("Sell");
        }
        _model->setItem(i,2,item3);

        int number = order.GetNumber();
        QStandardItem* item4 = CreateItem(number);
        _model->setItem(i,3,item4);

        double price = order.GetPrice();
        QStandardItem* item5 = CreateItem(price);
        _model->setItem(i,4,item5);

    }
}

OrderWindow::~OrderWindow()
{

}

