#pragma once
//
//  Dept_Treasure.h
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 30/10/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#ifndef __Stock_Exchange_Simulator__Dept_Treasure__
#define __Stock_Exchange_Simulator__Dept_Treasure__


#include <iostream>
#include <vector>
using namespace std;

class Treasure
{
private:
    vector<double> _rate;
    vector<double> _demand; //money loaned to the Dpt treasure
    double _low; //standard values = 0 or 0.1%
    double _high;
    double _aim_rate;
    double _aim_demand;
    int _maturity;//time for the bondto mature
    double _cash; //for accounting purposes
    int _period;//moving mean period for the observation of the demand
public :
    Treasure(double aim_rate, double aim_demand, double low, double high, int maturity, int period);
    void Display();
    double GetRate();
    double GetDemand();
    int GetMaturity();
    void GetNewRate();
    void AddDemand(double price);//increase demand when a bound is bought
    void SetCash(double delta);

    
};

double abs(double);
#endif /* defined(__Stock_Exchange_Simulator__Dept_Treasure__) */
