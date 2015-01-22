#pragma once
//
//  Company.h
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 05/10/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#ifndef __Stock_Exchange_Simulator__Company__
#define __Stock_Exchange_Simulator__Company__



#include "Stock.h"
#include <iostream>
#include "Agent.h"
#include "Portfolio.h"
#include "General.h"

using namespace std;

class Company
{
protected:
    int _id;
    string _name;
    vector<double> _cash;
    vector<double> _results;
    vector<double> _objectives;
    int _paytime;//next time when the result will be distributed
    int _div_period;//at the end of each paytime: _paytime+=_div_period
    vector<double> _dividends;//total distributed
    vector<double> _investments;
    vector<double> _savings;
    vector<double> _mu;//expected result growth per day
    double _sigma;//risk of the company (>0)
    double _alpha;// dividends coefficient
    double _beta;// savings coef
    double _warning;

    
public:
    Company(int id, string name, double cash,int paytime, int div_period, double initial_dividend, double initial_mu, double sigma, double alpha, double beta, double warning);
    void Display();
    int GetId();
    string GetName();
    double GetCash();
    void ChangeCash(double delta_cash);
    void UpdateResult();
    void UpdateCompany(int time, double rate, int nb_stock, vector<Agent*> pagents);
};



#endif /* defined(__Stock_Exchange_Simulator__Company__) */
