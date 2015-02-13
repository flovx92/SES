#include "Window.h"
#include "Database.h"
#include <QPushButton>
#include <QWidget>
#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include "StockWindow.h"

#include "QMdiArea"
#include "QMdiSubWindow"
#include <QStatusBar>
#include "Agent.h"
#include "Portfolio.h"
#include "PortfolioWindow.h"
#include <vector>
#include "StockExchange.h"
#include "OrderWindow.h"
#include "MyOptionStoreWindow.h"
#include "MyOptionsWindow.h"
#include "OptionsStoreWindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QContextMenuEvent>
using namespace std;


Window::Window(Database* pdata) : QMainWindow()
{
    setFixedSize(1250,750);
    setWindowTitle("Stock Exchange Simulator");

/*
    //menu
    QMenuBar* menubar= new QMenuBar(0);
    QMenu* menu = new QMenu(0);
    menu->setTitle("Fichier");
    menubar->addMenu(menu);
    this->setMenuBar(menubar);
*/

    _pdata = pdata;
     //creating the different windows
    QMdiArea* center = new QMdiArea(this);

    StockExchange* pse = _pdata->GetStockExchange();
    _stockwind = new StockWindow(pse);

    Agent* user = pdata->GetAgent(0);
    _portwind = new PortfolioWindow(user->GetPortfolio(),pse->GetStocks());

    _orderwind = new OrderWindow();

    _myoptionstorewind = new MyOptionStoreWindow();

    _myoptionswind = new MyOptionsWindow();

    _optionsstorewind = new OptionsStoreWindow();

    _bondwind = new BondWindow(pdata->GetTreasure());

    center->addSubWindow(_stockwind);
    center->addSubWindow(_portwind);
    center->addSubWindow(_orderwind);
    center->addSubWindow(_myoptionstorewind);
    center->addSubWindow(_myoptionswind);
    center->addSubWindow(_optionsstorewind);
    center->addSubWindow(_bondwind);
    setCentralWidget(center);

    //creation of the status bar
    Agent* agent = _pdata->GetAgent(0);
    vector<Stock> stocks = (_pdata->GetStockExchange())->GetStocks();
    _status = new QStatusBar();
    this->setStatusBar(_status);
    QString cash;
    cash.setNum(user->GetCash());
    double tot = agent->GetCash();
    vector<Portfolio*> portfolio = agent->GetPortfolio();
    for(int i = 0; i< (int) portfolio.size(); i++)
    {
        Portfolio* port = portfolio[i];
        tot+=port->GetNumber()*stocks[i].GetPrice();
    }
    QString total;
    total.setNum(tot);
    _status->showMessage("Cash : $"+cash+" Total value : $"+total);



}

void Window::Update()
{
    _stockwind->Update();
    Agent* agent =  _pdata -> GetAgent(0);
    vector<Stock> stocks = _pdata->GetStockExchange()->GetStocks();
    _portwind->Update(agent->GetPortfolio(), stocks);
    vector<Order> orders = agent->GetOrders();
    _orderwind->Update(orders);
    _myoptionstorewind->Update(agent->GetOptionStore());

    _myoptionswind->Update(agent->GetOptions());
    //cout <<"Pb Window: "<<agent->GetOptions().size()<<"\n";
    _optionsstorewind->Update(_pdata->GetStockExchange()->GetOptions());
    _bondwind->Update(agent->GetBonds(), _pdata->GetTreasure());
    //updating the status bar

    QString cash;
    cash.setNum(agent->GetCash());
    double tot = agent->GetCash();
    vector<Portfolio*> portfolio = agent->GetPortfolio();
    for(int i = 0; i< (int) portfolio.size(); i++)
    {
        Portfolio* port = portfolio[i];
        tot+=port->GetNumber()*stocks[i].GetPrice();
    }

    vector<Option*> options = agent->GetOptions();
    for(int i = 0; i< (int) options.size(); i++)
    {
        tot+=options[i]->GetPrice();
    }

    vector<Option*> options_store = agent->GetOptionStore();
    for(int i = 0; i< (int) options_store.size(); i++)
    {
        if(options_store[i]->GetSold())
        {
            tot-=options_store[i]->GetPrice();
        }
    }

    vector<Bond> bonds = agent->GetBonds();
    for(int i = 0; i<(int) bonds.size(); i++)
    {
        tot+=bonds[i].GetPrice();
    }
    QString total;
    total.setNum(tot);
    _status->showMessage("Cash : $"+cash+" Total value : $"+total);

}

Window::~Window()
{
    delete _pdata;
    delete _date;
}

QStandardItem* CreateItem(double num)
{
    QString string;
    string.setNum(num);
    QStandardItem* item = new QStandardItem();
    item -> setText(string);
    return item;
}
