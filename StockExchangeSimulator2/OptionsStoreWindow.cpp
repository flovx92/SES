#include "OptionsStoreWindow.h"

#include "Option.h"
#include <vector>
#include <QVBoxLayout>
#include <QTableView>
#include "Window.h"

OptionsStoreWindow::OptionsStoreWindow() : QWidget()
{
    setFixedSize(746,200);
    setWindowTitle("Option Store");

    QVBoxLayout* layout = new QVBoxLayout;

    QStringList col_label;
    col_label << "ID" << "Stock ID" << "Seller ID " << "Type" << "Strike" << "Maturity" << "Price";

    _model = new QStandardItemModel(5, 6);
    _model->setHorizontalHeaderLabels(col_label);


    QTableView *vue = new QTableView;
    vue->setModel(_model);

    layout->addWidget(vue);

    setLayout(layout);
}



void OptionsStoreWindow::Update(vector<Option*> options)
{
    int n = options.size();

    int record = 0;
    for(int i = 0; i < n; i++)
    {
        Option* option = options[i];
        if(option->GetIdSeller()!=0)//0 being user's ID
        {
            int line = i-record;

            int id = option->GetId();
            QStandardItem* item = CreateItem(id);
            _model->setItem(line,0,item);

            int stock_id = option->GetIdStock();
            QStandardItem* item2 = CreateItem(stock_id);
            _model->setItem(line,1,item2);

            int id_seller = option->GetIdSeller();
            QStandardItem* item3 = CreateItem(id_seller);
            _model->setItem(line,2,item3);

            bool is_call = option->GetIsCall();
            QStandardItem* item4 = new QStandardItem();
            if(is_call)
            {
                item4->setText("Call");
            }
            else
            {
                item4->setText("Put");
            }
            _model->setItem(line,3,item4);


            double strike = option->GetStrike();
            QStandardItem* item5 = CreateItem(strike);
            _model->setItem(line,4,item5);

            int maturity = option->GetMaturity();
            QStandardItem* item6 = CreateItem(maturity);
            _model->setItem(line,5,item6);

            double price = option->GetPrice();
            QStandardItem* item7 = CreateItem(price);
            _model->setItem(line,6,item7);
        }
        else
        {
            record++;
        }
    }
    _model->setRowCount(n-record);
}

OptionsStoreWindow::~OptionsStoreWindow()
{

}

