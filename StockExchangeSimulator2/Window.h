#ifndef WINDOW_H
#define WINDOW_H

#include <QApplication>
#include <QWidget>
#include <QStatusBar>
#include <QPushButton>
#include <QLCDNumber>
#include "Database.h"
#include <QMainWindow>
#include "StockWindow.h"
#include "PortfolioWindow.h"
#include "OrderWindow.h"
#include "MyOptionStoreWindow.h"
#include "MyOptionsWindow.h"
#include "OptionsStoreWindow.h"
#include "BondWindow.h"
#include "QMenuBar"

class Database;

class Window : public QMainWindow
{
    Q_OBJECT
private:
    QLCDNumber* _date;
    Database* _pdata;
    StockWindow* _stockwind;
    PortfolioWindow* _portwind;
    OrderWindow* _orderwind;
    MyOptionStoreWindow* _myoptionstorewind;
    MyOptionsWindow* _myoptionswind;
    OptionsStoreWindow* _optionsstorewind;
    BondWindow* _bondwind;
    QStatusBar* _status;

public slots:
    void Update();
public:
    Window(Database* pdata);
    ~Window();
};

QStandardItem* CreateItem(double num);
#endif // WINDOW_H
