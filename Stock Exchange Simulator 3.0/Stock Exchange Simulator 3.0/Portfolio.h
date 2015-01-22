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
    int _id_stock;//maybe useless
    int _nb_stock;
    double _medium_price;
    double _actual_price;
    double _dividends;//perceived by this share
    double _earnings;//on sales (not div)
public :
    Portfolio(int id, double price);
    int GetNumber();
    double GetMedPrice();
    void SetPortfolio(int delta, double price);
};

#endif /* defined(__Stock_Exchange_Simulator__Portfolio__) */
