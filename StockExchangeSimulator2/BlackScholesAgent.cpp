#include "BlackScholesAgent.h"
#include"Stock.h"
#include "Portfolio.h"
#include "Agent.h"
#include <QGlobal.h>
#include <QTime>
#include "Option.h"
#include "General.h"
#include "Treasure.h"
#include "Stat.h"
#include <math.h>
#include "Company.h"

// We put into place an agent who will use BlackScholes formulas in order to price the options.

BlackScholesAgent::BlackScholesAgent(int id, double cash, vector<double> stock_prices, double margin):Agent(id, cash, stock_prices)
{
    _margin = margin;
    int n=_portfolio.size();
    for (int i=0; i<n; i++)
    {
        _delta.push_back(0);
    }
}

// First of all, we have to define the Normal Distribution that is needed in the BlackScholes formulas.
// In order to do that, we approximate the integral thanks to rectangles.

double Normal_distribution(double x)
{
    double n = 1000.;
    double result=0;
    double PI  =3.14159265358;

    if (absval(x)<.001)
    {
        return 0.5;
    }
    double h=x/n;

    for (double k=0; k<=n;k++)
    {
        double fh=exp(-pow(k*h,2)/2)/sqrt(2*PI);
        double rectangle =fh*h;
        result+=rectangle;
    }

    return (result+0.5);
}

// We define both the first and the second parameters (d1 et d2) found in BlackScholes.
// S=spot price, K=strike price, r=interest rate, rho=dividend rate, mat=maturity

double first_arg(double S, double K, double r, double rho, double sigma, int mat)
{
    double num = (r-rho+0.5*pow(sigma,2))*mat;
    double den = (sigma*sqrt(mat));
    //cout << "num : "<<num<<"\n";
    //cout << "den : "<<den<<"\n";
    return num/den;
}

double sec_arg(double sigma, int mat,double d1)
{
    return (d1-(sigma*sqrt(mat)));
}

// Given the parameters, the agent can therefore price the call.

double price_call_blacks(double S,double K, double r, double rho, int mat,double d1,double d2)
{
    double call_price = S*exp(-rho*mat)*Normal_distribution(d1)-K*exp(-r*mat)*Normal_distribution(d2);
    return call_price;
}

// To make the calculations easier, we use the call-put parity in order to price the put.

double price_put_blacks(double S,double K, double r, double rho, int mat,double call_price)
{
    double put_price = -S*exp(-rho*mat)+K*exp(-r*mat) + call_price;
    return put_price;
}

// The delta gives up the number of stocks we have to buy and therefore have in our portfolio in order to hedge our position.

double delta_call(int mat,double rho, double d1)
{
    return exp(-rho*mat)*Normal_distribution(d1);
}

double delta_put(int mat, double rho, double d1)
{
    return -exp(-rho*mat)*Normal_distribution(-d1);
}

void BlackScholesAgent::Do(int time, vector<Stock> stocks, vector<Option*> options, Treasure* tres, vector<Company*> companies, vector<Stat*> stats)
{
    QTime qtime = QTime::currentTime();
    qsrand((uint)qtime.msec()+_id);

    EraseUsedOrders();
    int mat=tres->GetMaturity();

    // First step : the agent looks at all the options

    int nb_stock = companies.size();
    for(int i = 0; i<nb_stock; i++)
    {
        _delta[i]=0;
    }




    int n=_option_store.size();
/*
    for (int i=0;i<n;i++)
    {
        Option* option = _option_store[i];
        if (option->GetSold() or option->GetIdBuyer()!=_id)//the second expression is just a verification
        {
            int stock_id=option->GetIdStock();
            _delta[stock_id]+=option->GetDelta();
            if (option->GetTime()==time+1) // !!!!!!!!!!!!!!!!! ou time
            {
                double delta = option->GetDelta();
                double price_stock = stocks[stock_id].GetPrice();
                double price = option->GetPrice()-100*delta*price_stock;
                MakeBond(time,mat,tres,price);
            }
        }
        else
        {
                EraseOption(option->GetId());
        }
    }
    */
/*
    for (int i=0;i<n;i++)
    {
        double delta = _delta[i]*100;
        Stock stock = stocks[i];

        if (delta>0)
        {
            double price=stock.GetBuyPrice();
            MakeAnOrder(time,i,true,floor(absval((delta))),price);
        }
        else
        {
            double price=stock.GetSellPrice();
            MakeAnOrder(time,i,false,floor(absval(delta)),price);
        }
    }
*/

    // Second step : option selling

    if(time>mat)
    {
        int nb_stocks = _portfolio.size();
        int id_stock = qrand()%nb_stocks;
        Stock stock = stocks[id_stock];

        double strike=stock.GetPrice();

        double price = stock.GetPrice();

        double r=tres->GetRate()/100.;
        Company* comp = companies[id_stock];
        double last_div = comp->GetDiv();
        int nb_stock = stock.GetNumber();
        double last_div_per_share = last_div/(double) nb_stock;
        int div_period = comp->GetDivPeriod();
        double rho = exp((1/(double) div_period)*log(1+last_div_per_share/(stock.GetPrice()))) - 1;
        //cout << "div : "<< rho << "&"<< r <<"\n";
        Stat* stat=GetStat(stats,mat);

        double sigma = sqrt((stat->GetCovar()[id_stock][id_stock]));
        //cout <<"sigma : "<<sigma<<"\n";
        double d1=first_arg(price,price,r,rho,sigma,mat);
        double d2=sec_arg(sigma,mat,d1);
        //cout << "d1 : " << d1 << "\n";
        //cout << "d2 : " << d2 << "\n";


        double delta_c=delta_call(mat,rho,d1);
        double delta_p=delta_put(mat,rho,d1);
        //cout << "delta_c : " << delta_c << "\n";
        //cout << "delta_p : " << delta_p << "\n";

        double call_price=price_call_blacks(price,price,r,rho,mat,d1,d2);
        double put_price=price_put_blacks(price,price,r,rho,mat,call_price);


        SellOption(id_stock,mat,strike,100*call_price*(1-_margin),true,delta_c);
        SellOption(id_stock,mat,strike,100*put_price*(1-_margin),false,delta_p);
    }

    //cout <<"Pb :"<< _options.size()<<"\n";


}



BlackScholesAgent::~BlackScholesAgent(void)
{
}
