#include "BondAgent.h"
#include"Stock.h"
#include "Portfolio.h"
#include "Agent.h"
#include <QGlobal.h>
#include <QTime>
#include "Option.h"
#include "General.h"
#include "Treasure.h"
#include "Bond.h"

BondAgent::BondAgent(int id, double cash, vector<double> stock_prices, double margin, int mat):Agent(id, cash, stock_prices)
{
    _margin = margin;
    _maturity = mat;
}

void BondAgent::Do(int time, vector<Stock> stocks, vector<Option*> options, Treasure* tres, vector<Company*> companies, vector<Stat*> stats)
{

    QTime qtime = QTime::currentTime();
    qsrand((uint)qtime.msec()+_id);


    int mat_ref = tres->GetMaturity();
    double today_rate = tres->GetRate();



    for(int i = 0; i<(int) _bonds.size(); i++)
    {

        Bond* bond = &(_bonds[i]);

        double rate = bond->GetRate();
        int initial_time = bond->GetTime();
        int mat = bond->GetMaturity();
        double T = ((double) mat)/((double) mat_ref);
        double t =  ((double)(time - initial_time))/((double) mat);
        double denominator = exp((1-t)*T*log(1+today_rate/100.));
        double cash_flow = exp(T*log(1+rate/100.));
        double price = cash_flow/denominator;

        double on_going_revenu = exp(t*T*log(1+rate/100.));
        if(price>(1+_margin)*on_going_revenu)
        {
            bond->Sold();
        }

    }



    if(_cash>0)
    {
        double new_deposit = _cash*(15*(qrand()%1000)/1000.+10)/100.;
        MakeBond(time, _maturity,tres, new_deposit);
    }

}
