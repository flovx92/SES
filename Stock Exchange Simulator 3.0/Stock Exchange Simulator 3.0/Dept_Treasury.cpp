//
//  Dept_Treasure.cpp
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 30/10/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#include "Dept_Treasury.h"
#include "General.h"

Treasure::Treasure(double aim_rate, double aim_demand, double low, double high, int period, int maturity)
{
    _aim_demand = aim_demand;
    _aim_rate = aim_rate;
    _low = low;
    _high = high;
    _period = period;
    _demand = vector<double> (2); //the second spot will be completed when agents will buy bonds
    _demand[0] = aim_demand;
    _rate = vector<double> (1);
    _rate[0] = aim_rate;
    _cash = 0;
    _maturity = maturity;
}

void Treasure::Display()
{
    unsigned long n = _demand.size();
    cout << "Department of Treasury :" << "\n";
    cout << "the last demand was : $ " << _demand[n-2] << "\n";
    cout << "the no risk rate is : " << _rate[n-2] << "%" << "\n";
    cout << "\n";
}

double Treasure::GetRate()
{
    unsigned long n = _rate.size();
    return _rate[n-1];
}

double Treasure::GetDemand()
{
    unsigned long n = _demand.size();
    return _demand[n-1];
}




int Treasure::GetMaturity()
{
    return _maturity;
}

void Treasure::GetNewRate()
{
    int n = _demand.size();
    double D=0;
    if (n>_period)
    {
        for (int i = 0; i<_period; i++)
        {
            D = D +(_demand[n-1-i]/_period);
        }
    }
    else
    {
        for (int i=0; i< n; i++)
        {
            D = D + (_demand[i]/(n));
        }
    }
    
    double delta_D = (_aim_demand/D) - 1;
    
    double r = (this -> GetRate());
    double delta_r = (_aim_rate/r) - 1;
    
    
    double coef_r = absval(delta_r);
    double coef_D = absval(delta_D);
    double sum = coef_r + coef_D;
    double new_r=0;
    
    if (sum == 0)
    {
        new_r = _aim_rate;
    }
    else
    {
        double x = (coef_r * delta_r + coef_D * delta_D)/sum;
        new_r = r*(1+x);
    }

    //Comparisons high/low
    if (new_r < _low)
    {
        new_r = _low;
    }
    else
    {
        if (new_r > _high)
        {
            new_r = _high;
        }
    }
    
    //updating vectors
    _rate.push_back(new_r);
    _demand.push_back(0);
    
};

void Treasure::AddDemand(double price)
{
    unsigned long n = _demand.size();
    _demand[n-1] += price;
    _cash += price;
    
}

void Treasure::SetCash(double delta)
{
    _cash += delta;
}
