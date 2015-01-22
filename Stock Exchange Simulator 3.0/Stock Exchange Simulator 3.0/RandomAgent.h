#pragma once
//
//  Agent.h
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 06/10/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#ifndef __Stock_Exchange_Simulator__RandomAgent__
#define __Stock_Exchange_Simulator__RandomAgent__

#include "Agent.h"
#include "Order.h"
#include "Stock.h"
#include "Bond.h"
#include "Option.h"
#include "Dept_Treasury.h"
#include "Portfolio.h"
#include <iostream>
#include <vector>
using namespace std;

class RandomAgent : public Agent
{
protected:
	double _price;
public :
	RandomAgent(int id, int bank, double cash, vector<double> stock_prices, double price);
	void Do(int time, vector<Stock> stocks, vector<Option*> options);
	~RandomAgent();
};


#endif /* defined(__Stock_Exchange_Simulator__RandomAgent__) */