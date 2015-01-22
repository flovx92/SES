#pragma once
//
//  Stocks.h
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 03/10/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#ifndef __Stock_Exchange_Simulator__Stocks__
#define __Stock_Exchange_Simulator__Stocks__

#include <iostream>
#include <vector>
using namespace std;

class Stock
{
private:
    int _company_id;
    vector<double> _stock_values;
    vector<double> _median_buy;
    vector<double> _median_sell;
    int _number_of_stocks;
public:
    Stock(int company_id, double price,int number_of_stocks);
    int GetCompanyID();
    double GetPrice();
    double GetBuyPrice();
    double GetSellPrice();
    void NewPrice(double new_price, double median_buy, double median_sell);
    
};

double price_variation(double price,double delta);

#endif /* defined(__Stock_Exchange_Simulator__Stocks__) */

