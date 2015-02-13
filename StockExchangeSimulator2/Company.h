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



#include <QString>
#include <iostream>
#include <vector>

class Agent;

using namespace std;

class Company
{
protected:
    int _id;
    QString _name;
    vector<double> _cash;//company's capital
    vector<double> _results;//random cash flows between two paytimes
    vector<double> _objectives;//minimum to invest in the company in order to get growth (in expectancy)
    int _paytime;//next time when the result will be distributed
    int _div_period;//at the end of each paytime: _paytime+=_div_period
    vector<double> _dividends;//total distributed
    vector<double> _investments;//money invested in the company
    vector<double> _savings;
    vector<double> _mu;//expected result growth per day
    double _sigma;//risk of the company (>0)
    double _alpha;// dividends coefficient
    double _beta;// savings coef
    double _warning;//variable defining critical situations where the company invest with its savings

    
public:
    Company(int id, QString name, double cash,int paytime, int div_period, double initial_dividend, double initial_mu, double sigma, double alpha, double beta, double warning);
    int GetId();
    QString GetName();
    double GetCash();
    void ChangeCash(double delta_cash);
    double GetDiv();
    int GetPaytime();
    int GetDivPeriod();
    void UpdateResult();
    void UpdateCompany(int time, double rate, int nb_stock, vector<Agent*> pagents);
};



#endif /* defined(__Stock_Exchange_Simulator__Company__) */
