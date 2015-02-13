//
//  Bond.cpp
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 30/10/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#include "Bond.h"

Bond::Bond(int time, int maturity, double rate, double price)
{
    _time = time;
	_maturity = maturity;
    _rate = rate;
    _price = price;
    _sold = false;
}

int Bond::GetTime()
{
    return _time;
}

int Bond::GetMaturity()
{
	return _maturity;
}

double Bond::GetRate()
{
    return _rate;
}

double Bond::GetPrice()
{
    return _price;
}

bool Bond::GetSold()
{
	return _sold;
}

void Bond::Sold()
{
	_sold = true;
}