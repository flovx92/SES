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
    int _time;//time = creation of the bound
    int _maturity;//period of time between creation and maturity of the bound
    double _rate;
    double _price; //money "put" on the bound like a deposit
	bool _sold; //the value is true when the agent sold it to the stock exchange
    
public :
    Bond(int time, int maturity, double rate, double price);
    int GetTime();
	int GetMaturity();
    double GetPrice();
    double GetRate();
	bool GetSold();
	void Sold();
};

#endif /* defined(__Stock_Exchange_Simulator__Bond__) */
