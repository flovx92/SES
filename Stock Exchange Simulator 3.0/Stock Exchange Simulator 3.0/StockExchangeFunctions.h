#pragma once
//
//  StockExchangeFunctions.h
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 04/10/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#ifndef __Stock_Exchange_Simulator__StockExchangeFunctions__
#define __Stock_Exchange_Simulator__StockExchangeFunctions__

#include "StockExchangeFunctions.h"
#include "StockExchange.h"
#include "Order.h"
#include "Agent.h"
#include <iostream>
#include <vector>
using namespace std;

vector<double> Sorting(vector<Order*>,int,bool);
vector<double> Ordering(vector<double>, bool);
void Insert(int j, Order*& order, vector<Order*>& orders);


#endif /* defined(__Stock_Exchange_Simulator__StockExchangeFunctions__) */
