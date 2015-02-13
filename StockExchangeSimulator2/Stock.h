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

#include <QString>
class Stock
{
private:
    int _company_id;
    QString _company_name;
    vector<double> _stock_values;//price history
    vector<double> _median_buy;//history of median buy prices
    vector<double> _median_sell;//history of median sell prices
    int _number_of_stocks;//number of stock in total present in the market
public:
    Stock(int company_id,QString _company_name, double price,int number_of_stocks);
    QString GetCompanyName();
    int GetCompanyID();
    double GetPrice();
    vector<double> GetPrices();
    double GetBuyPrice();
    double GetSellPrice();
    int GetNumber();
    void NewPrice(double new_price, double median_buy, double median_sell);

};

double price_variation(double price,double delta);

#endif /* defined(__Stock_Exchange_Simulator__Stocks__) */

