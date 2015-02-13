//
//  Company.cpp
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 05/10/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#include "Company.h"
#include "Agent.h"
#include "StockExchange.h"
#include "Stock.h"
#include "General.h"
#include "Portfolio.h"
#include <iostream>
#include <QGlobal.h>
#include <QTime>
#include <math.h>
#include <QString>

using namespace std;

Company::Company(int id, QString name, double cash, int paytime, int div_period, double initial_dividend, double initial_mu, double sigma, double alpha, double beta, double warning)
{
    _id = id;
    _name = name;
    

    //the different initialisations
    //t=0
    _cash.push_back(cash);
    _results.push_back(initial_mu*div_period);
    _objectives.push_back(initial_mu*div_period-initial_dividend);
    _paytime = paytime;
    _div_period = div_period;
    _dividends.push_back(initial_dividend);
    _investments.push_back(initial_mu*div_period-initial_dividend);
    _savings.push_back(0);
    _mu.push_back(initial_mu);
    
    //t=1
    _cash.push_back(cash);
    _objectives.push_back(initial_mu*div_period-initial_dividend);
    _mu.push_back(initial_mu);
    _results.push_back(0);

    for(int i = _paytime - div_period; i<0; i++)
    {
        UpdateResult();
    }
    
    //behavior parametres
    _sigma = sigma;
    _alpha = alpha;
    _beta = beta;
    _warning = warning;
    
}



int Company::GetId()
{
    return _id;
}

QString Company::GetName()
{
    return _name;
}



double Company::GetCash()
{
    int n = _cash.size();
    return _cash[n-1];
}

void Company::ChangeCash(double delta_cash)
{
    int n = _cash.size();
    _cash.push_back(delta_cash+_cash[n]);
}

double Company::GetDiv()
{
    int n = _dividends.size();
    return _dividends[n-1];
}

int Company::GetPaytime()
{
    return _paytime;
}

int Company::GetDivPeriod()
{
    return _div_period;
}

void Company::UpdateResult()
{
    int n = _mu.size();
    double N = Normal_generator(_mu[n-1], _sigma);
    _results[n-1]+=N;
}


void Company::UpdateCompany(int time, double rate, int nb_stock, vector<Agent*> pagents)
{
    UpdateResult();
    
    if (time == _paytime)
    {
        int n = _cash.size();
        _paytime+=_div_period;
        
        // calculating the deltas
    
        double result = convert_price(_results[n-1]);
        _results[n-1] = result;
        double obj = _objectives[n-1];
        double profit = result - obj;
        double savings = _savings[n-2];
        if (profit>0)
        {
            if (savings>=0)
            {
                double div0 = _dividends[0];
                if (profit < div0)
                {
                    _savings.push_back(0);
                    _investments.push_back(obj);
                    _dividends.push_back(profit);
                }
                else
                {
                    double div = convert_price(div0 +(profit-div0)/(1+_alpha*(1+(1/_beta))));
                    double sav = convert_price((profit - div0)/(1+_beta*(1+(1/_alpha))));
                    double inv = result - div - sav;
                    _dividends.push_back(div);
                    _savings.push_back(sav);
                    _investments.push_back(inv);
                }
            }
            else //savings<0
            {
                if (profit<rate*savings)
                {
                    _savings.push_back(profit);
                    _investments.push_back(obj);
                    _dividends.push_back(0);
                }
                else //paying back the loan more important than giving the min div D0
                {
                    double div= convert_price((profit - rate*savings)/(1+_alpha*(1+(1/_beta))));
                    double sav = convert_price(rate*savings + (profit - rate*savings)/(1+_beta*(1+(1/_alpha))));
                    double inv = result - div - sav;
                    _dividends.push_back(div);
                    _savings.push_back(sav);
                    _investments.push_back(inv);
                }
            }
        }
        else
        {
            _investments.push_back(result);
            if (max(obj,0) - max(result,0)> _warning*result)
            {
                _savings.push_back(-(max(obj,0)-result));
                _investments[n-1] += (max(obj,0)-result);
                _dividends.push_back(0);
            }
            else
            {
                _savings.push_back(0);
                _dividends.push_back(0);
            }
        }
        
        //cash, savings, mu evolution
        _cash[n-1]=_cash[n-1] - _dividends[n-1];
        double delta = _investments[0]/_cash[0];
        double k = _mu[0]/_investments[0];
        _savings[n-1]+=convert_price(_savings[n-2]*(1+rate));
        _cash.push_back(_investments[n-1]+_cash[n-1]*(1-delta));
        _objectives.push_back(convert_price((delta*(1-delta)*_cash[n])/(k*_div_period-delta)));
        _mu.push_back(k*_investments[n-1]);
        _results.push_back(0);
        
        //pay div to shareholders
        
        double div = convert_price(_dividends[n-1]/(double) nb_stock);
        if (div>0)
        {
            int nb_agents = pagents.size();
            for (int i = 0; i<nb_agents; i++)
            {
                Agent* pagent = pagents[i];
                Portfolio* pport = pagent -> GetPortfolio()[_id];
                int m = pport -> GetNumber();
                pagent -> ReceiveDividends(_id,m*div);
                
            }
        }
        
        
        
    }
}

