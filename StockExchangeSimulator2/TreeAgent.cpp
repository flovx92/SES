#include "TreeAgent.h"
#include "General.h"
#include "Bond.h"
#include "Option.h"
#include "Stock.h"
#include "Portfolio.h"
#include "Treasure.h"
#include "Stat.h"
#include "Agent.h"
#include <QGlobal.h>
#include <QTime>
#include <cmath>
#include <vector>
#include <iostream>


TreeAgent::TreeAgent(int id, double cash, vector<double> stock_prices, double margin):Agent(id, cash, stock_prices)
{
    _margin = margin;
}

void TreeAgent::Do(int time, vector<Stock> stocks, vector<Option*> options, Treasure* tres, vector<Company*> companies, vector<Stat*> stats)
{
    QTime qtime = QTime::currentTime();
    qsrand((uint)qtime.msec()+_id);
    cout << "I am tree"<<_id;
    //cout << _options.size() << "\n";
    if(_id!=0)
    {
        int n = options.size();
        if(n>0)
        {

            int random = qrand()%n;
            Option* option = options[random];
            double mat=option->GetMaturity();
            int stock_id = option->GetIdStock();
            double S = stocks[stock_id].GetPrice();
            Stat* stat=GetStat(stats,mat);
            double sigma = sqrt((stat->GetCovar()[stock_id][stock_id]));

            double option_price_call_EB=option_price_call_european_binomial(S,option->GetStrike(),tres->GetRate(),sigma,2);
            //cout<<"Me : " << 100*option_price_call_EB << " vs. "<<option->GetPrice()<<"\n";

            //if(100*option_price_call_EB > option->GetPrice()*(1+_margin))
            if(true)//because the evaluation did not work
            {
                double seller=option->GetIdSeller();
                double id=option->GetId();
                BuyOption(time,id,seller,option->GetPrice()*(1+_margin),options);

            }


            int m= _options.size();
            for (int i=0;i<m;i++)
            {
                Option* option = _options[i];
                        double time_option = option->GetTime();
                        double mat = option->GetMaturity();
                        if (time_option+mat-1<=time)
                        {

                            double pay_off=stocks[option->GetIdStock()].GetPrice() - option->GetStrike();
                            if(option->GetIsCall()==false)
                            {
                                pay_off = -pay_off;
                            }
                            if (pay_off>=0)
                            {
                                option->Exercice();
                            }
                        }
            }

        }
    }
}


double option_price_call_european_binomial (double S, double K, double r, double sigma, int steps) {

    double R=exp((1/(double) steps)*log(1+r))-1;
    double Rinv = 1.0/R;
    double u = 1+sigma;
    double uu=u*u;
    double d=1.0/u;
    double p_up = (R-d)/(u-d);
    double p_down = 1.0-p_up;
    vector <double> prices(steps+1);
    prices[0]=S*pow(d,steps);
    for (int i=1; i<=steps;++i)
    {
        prices[i]=uu*prices[i-1];
    }
    vector <double> call_values(steps+1);
    for (int i=0;i<=steps;++i)
    {
        call_values[i]=max(0.0,(prices[i]-K));
    }
    for (int step=steps-1; step>=0;step--)
    {
        for (int i=0; i<=step; i++)
        {
            call_values[i]=(p_up*call_values[i+1]+p_down*call_values[i])*Rinv;
        }
    }
    return call_values[0];

};



TreeAgent::~TreeAgent(void)
{
}





