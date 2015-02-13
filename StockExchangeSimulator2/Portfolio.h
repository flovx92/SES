//
//  Portfolio.h
#pragma once
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 24/11/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#ifndef __Stock_Exchange_Simulator__Portfolio__
#define __Stock_Exchange_Simulator__Portfolio__

#include <iostream>
using namespace std;

class Portfolio // for accounting purposes (ex : how much do i have to sell a stock in order to make a profit)
{
private :
    int _id_stock;
    int _nb_stock;//number of stock Ive got of the stock_id
    double _medium_price;//if I have 10 stocks it tells at which medium price I have bought all these
    double _dividends;//perceived by this share
    double _earnings;//money I make by seeling stocks on a long position (or buying on a short one)
public :
    Portfolio(int id);
    int GetNumber();
    double GetMedPrice();
    double GetEarnings();
    double GetDividends();
    void SetPortfolio(int delta, double price);
    void SetDividends(double price);
};

#endif /* defined(__Stock_Exchange_Simulator__Portfolio__) */
