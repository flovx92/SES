#include "BondWindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableView>
#include <QStandardItem>
#include <QLabel>
#include "Treasure.h"
#include "Bond.h"
#include "Window.h"

BondWindow::BondWindow(Treasure* ptres) : QWidget()
{
    setFixedSize(546,250);
    setWindowTitle("Bonds");

    QVBoxLayout* layout = new QVBoxLayout;

    QHBoxLayout* sublayout = new QHBoxLayout;
    QPushButton* rate = new QPushButton();
    QString mat;
    mat.setNum(ptres->GetMaturity());
    rate->setText("Bond rate for a period of : " + mat);
    _rate_lab = new QLabel;
    QString num;
    num.setNum(ptres->GetRate());
    _rate_lab->setText("Rate : " + num + "%");

    sublayout->addWidget(rate);
    sublayout->addWidget(_rate_lab);

    QStringList col_label;
    col_label << "ID" << "Begin" << "End" << "Rate" << "Price";

    _model = new QStandardItemModel(5, 5);
    _model->setHorizontalHeaderLabels(col_label);


    QTableView *vue = new QTableView;
    vue->setModel(_model);

    layout->addLayout(sublayout);
    layout->addWidget(vue);

    setLayout(layout);
}

void BondWindow::Update(vector<Bond> bonds, Treasure* tres)
{
    QString num;
    num.setNum(tres->GetRate());
    _rate_lab->setText("Rate : " + num + "%");
    int n = bonds.size();
    _model->setRowCount(n);
    for(int i = 0; i<n; i++)
    {
        Bond bond = bonds[i];

        QStandardItem* item1 = CreateItem(i);
        _model->setItem(i,0,item1);

        int time = bond.GetTime();
        QStandardItem* item2 = CreateItem(time);
        _model->setItem(i,1,item2);

        QStandardItem* item3 = CreateItem(bond.GetMaturity() + time);
        _model->setItem(i,2,item3);

        QStandardItem* item4 = CreateItem(bond.GetRate());
        _model->setItem(i,3,item4);

        QStandardItem* item5 = CreateItem(bond.GetPrice());
        _model->setItem(i,4,item5);
    }

}

BondWindow::~BondWindow()
{

}

