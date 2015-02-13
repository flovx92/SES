#include "CompanyAgent.h"

#include"Stock.h"
#include "Portfolio.h"
#include "Agent.h"
#include <QGlobal.h>
#include <QTime>
#include "Option.h"
#include "General.h"
#include "Company.h"
#include "Treasure.h"


CompanyAgent::CompanyAgent(int id, double cash, vector<double> stock_prices, double margin):Agent(id, cash, stock_prices)
{
    _margin = margin;
}

void CompanyAgent::Do(int time, vector<Stock> stocks, vector<Option*> options, Treasure* tres,vector<Company*> companies ,vector<Stat*> stats)
{
    QTime qtime = QTime::currentTime();
    qsrand((uint)qtime.msec()+_id);

    EraseUsedOrders();

    int n = _portfolio.size();
    int id_stock = qrand()%n;
    Company* company = companies[id_stock];
    Stock stock = stocks[id_stock];
    double div_total = company->GetDiv();
    int number = stock.GetNumber();
    double div = div_total/(double) number;
    double rate = (tres->GetRate())/100.;
    int paytime = company->GetPaytime();
    int T = tres->GetMaturity();
    double power = 1-((paytime-time)/(double) T);

    double estimated_price = (div/rate)*exp(power*log(1+rate));
    double market_price = stock.GetPrice();

    bool buy;
    double price = 0;
    if (estimated_price>(1+_margin)*market_price)
    {
        buy = true;
        price = (1+_margin)*market_price;
    }
    else
    {
        if (estimated_price<(1-_margin)*market_price)
        {
            buy = false;
            price = (1-_margin)*market_price;
        }

    }
    if (price!=0)
    {
        NewOrder(time, id_stock, buy, 100, convert_price(price));
    }

}



CompanyAgent::~CompanyAgent()
{

}

