//
//  Bond.cpp
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 30/10/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#include "Bond.h"

Bond::Bond(int time, double rate, double price)
{
    _time = time;
    _rate = rate;
    _price = price;
    
}

int Bond::GetTime()
{
    return _time;
}

double Bond::GetRate()
{
    return _rate;
}

double Bond::GetPrice()
{
    return _price;
}
