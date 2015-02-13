#pragma once


#ifndef __Stock_Exchange_Simulator__Dept_Treasure__
#define __Stock_Exchange_Simulator__Dept_Treasure__


#include <iostream>
#include <vector>
using namespace std;

class Treasure
{
private:
    vector<double> _rate;//history of the different rates
    vector<double> _demand; //money loaned to the Dpt treasure
    double _low; //min rate
    double _high;//max rate
    double _aim_rate;//"normal" rate
    double _aim_demand;//"normal demand"
    int _maturity;//time for the bond to mature
    double _cash; //for accounting purposes
    int _period;//moving mean period for the observation of the demand
public :
    Treasure(double aim_rate, double aim_demand, double low, double high, int period, int maturity);
    double GetRate();
    double GetDemand();
    int GetMaturity();
    double GetNewRate();
    void AddDemand(double price);//increase demand when a bound is bought
    void SetCash(double delta);

    
};

double abs(double);
#endif /* defined(__Stock_Exchange_Simulator__Dept_Treasure__) */
