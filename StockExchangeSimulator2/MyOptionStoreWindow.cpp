#include "MyOptionStoreWindow.h"
#include "Option.h"
#include <vector>
#include <QVBoxLayout>
#include <QTableView>
#include "Window.h"

MyOptionStoreWindow::MyOptionStoreWindow() : QWidget()
{
    setFixedSize(746,200);
    setWindowTitle("My Option Store");

    QVBoxLayout* layout = new QVBoxLayout;

    QStringList col_label;
    col_label << "ID" << "Stock ID" << "Type" << "Strike" << "Maturity" << "Price" << "Sold ?";

    _model = new QStandardItemModel(5, 7);
    _model->setHorizontalHeaderLabels(col_label);


    QTableView *vue = new QTableView;
    vue->setModel(_model);

    layout->addWidget(vue);

    setLayout(layout);
}

void MyOptionStoreWindow::Update(vector<Option*> options)
{
    int n = options.size();
    _model->setRowCount(n);
    for(int i = 0; i < n; i++)
    {
        Option* option = options[i];

        int id = option->GetId();
        QStandardItem* item = CreateItem(id);
        _model->setItem(i,0,item);

        int stock_id = option->GetIdStock();
        QStandardItem* item2 = CreateItem(stock_id);
        _model->setItem(i,1,item2);

        bool is_call = option->GetIsCall();
        QStandardItem* item3 = new QStandardItem();
        if(is_call)
        {
            item3->setText("Call");
        }
        else
        {
            item3->setText("Put");
        }
        _model->setItem(i,2,item3);


        double strike = option->GetStrike();
        QStandardItem* item4 = CreateItem(strike);
        _model->setItem(i,3,item4);

        int maturity = option->GetMaturity();
        QStandardItem* item5 = CreateItem(maturity);
        _model->setItem(i,4,item5);

        double price = option->GetPrice();
        QStandardItem* item6 = CreateItem(price);
        _model->setItem(i,5,item6);

        bool is_sold = (option->GetIdBuyer()==option->GetIdSeller());
        QStandardItem* item7 = new QStandardItem();
        if (is_sold)
        {
            item7->setText("False");
        }
        else
        {
            item7->setText("True");
        }
        _model->setItem(i,6,item7);
    }
}

MyOptionStoreWindow::~MyOptionStoreWindow()
{

}

