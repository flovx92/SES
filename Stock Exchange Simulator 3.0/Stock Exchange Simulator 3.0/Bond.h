#pragma once
//
//  Bond.h
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 30/10/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#ifndef __Stock_Exchange_Simulator__Bond__
#define __Stock_Exchange_Simulator__Bond__


#include <iostream>
using namespace std;

class Bond
{
private:
    int _time;
    double _rate;
    double _price; //money "put" on the bound
    
public :
    Bond(int time, double rate, double price);
    int GetTime();
    double GetPrice();
    double GetRate();
};

#endif /* defined(__Stock_Exchange_Simulator__Bond__) */
