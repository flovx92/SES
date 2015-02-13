#include <QApplication>
#include <iostream>
#include <vector>
#include <QtGlobal>
#include <QTime>
#include <QTimer>
#include <QObject>
#include "General.h"
#include "Database.h"
#include "Stock.h"
#include "Order.h"
#include "StockExchange.h"
#include "StockExchangeFunctions.h"
#include "Company.h"
#include "Agent.h"
#include "RandomAgent.h"
#include "TreeAgent.h"
#include "Treasure.h"
#include "Window.h"
#include "IntroWindow.h"
using namespace std;





int main(int argc, char *argv[])
{
    std::cout << "Hello, World!" << "\n";
    QApplication app(argc, argv);

/*
    //initialisation
    Database* pdata = Initialisation();

    Window* frame = new Window(pdata);

    frame -> show();
    pdata->Simulation(frame);
*/

    IntroWindow* introwind = new IntroWindow();
    introwind->show();

    return app.exec();

}

