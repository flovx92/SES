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

#include <iostream>
#include <vector>
using namespace std;

class Order;

vector<double> Sorting(vector<Order*> orders, int stock, bool isbuy);//sort the prices of orders of the same type (buy or sell) and the same stock
vector<double> Ordering(vector<double>, bool);//returns the vector with its value organised in a decreasing way (increasing if the boolean is false)
                                //at the end, the results[0] gets us the best buying (or selling) price
void Insert(int j, Order*& order, vector<Order*>& orders);//sort the orders by their prices at the same time they are "scanned" in every agents'orders


#endif /* defined(__Stock_Exchange_Simulator__StockExchangeFunctions__) */
