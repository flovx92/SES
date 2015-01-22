﻿//
//  Portfolio.cpp
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 24/11/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#include "Portfolio.h"
#include "General.h"

Portfolio::Portfolio(int id, double price)
{
    _id_stock = id;
    _nb_stock = 0;
    _medium_price = 0;
    _actual_price = price;
    _dividends = 0;//perceived by this share
    _earnings = 0;//on sales (for long position) (and otherwise)  (not div)
    
}

int Portfolio::GetNumber()
{
    return _nb_stock;
}

double Portfolio::GetMedPrice()
{
    return _medium_price;
}

void Portfolio::SetPortfolio(int delta, double price)
{
    
    
    if (delta*_nb_stock > 0)// You are buying shares on a long position or selling shares on a short one.
    {
        _medium_price=(_medium_price*_nb_stock + price*delta)/(_nb_stock+delta);
    }
    else
    {
        if (absval(_nb_stock)<absval(delta))//going from a long to a short position (or otherwise)
        {
            _earnings+=(price-_medium_price)*_nb_stock;
            //if nbstock>0, ∆eanr>0 <=> price>medprice
            //if nbstock<0, ∆earn>0 <=> medprice>price
            _medium_price=price;
        }
        else
        {
            _earnings+=(price-_medium_price)*(-delta);
        }
        
    }
    _nb_stock+=delta;
    
}