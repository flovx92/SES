//
//  Stocks.cpp
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 03/10/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#include "Stock.h"
#include <iostream>
#include <vector>
using namespace std;


double price_variation(double price, double delta)
{
    int a = (int) price*(100+delta);
    return ((double) a)/100;
}

Stock::Stock(int company_id, double price, int number_of_stocks)
{
    _company_id = company_id;
    _stock_values.push_back(price);
    _median_buy.push_back(price_variation(price, 1));
    _median_sell.push_back(price_variation(price, -1));
    _number_of_stocks = number_of_stocks;
    
}

int Stock::GetCompanyID()
{
    return _company_id;
}

double Stock::GetPrice()
{
    int n=_stock_values.size();
    return _stock_values[n - 1];
}

double Stock::GetBuyPrice()
{
    int n=_median_buy.size();
    return _median_buy[n - 1];
}

double Stock::GetSellPrice()
{
    int n=_median_sell.size();
    return _median_sell[n - 1];
}
void Stock::NewPrice(double price,double med_buy, double med_sell)
{
    _stock_values.push_back(price);
    _median_buy.push_back(med_buy);
    _median_sell.push_back(med_sell);
}
