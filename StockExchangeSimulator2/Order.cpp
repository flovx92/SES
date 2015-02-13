//
//  Order.cpp
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 04/10/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#include "Order.h"
#include <iostream>
#include <vector>
using namespace std;

Order::Order(int id_order, int time,int stock_id, int agent, bool isbuy, int number_of_shares, double price)
{
    _id = id_order;
    _time = time;
    _stock_id = stock_id;
    _agent = agent;
    _isbuy = isbuy;
    _number_of_shares = number_of_shares;
    _price = price;
    
}

int Order::GetId()
{
    return _id;
}

int Order::GetTime()
{
    return _time;
}

int Order::GetAgent()
{
    return _agent;
}

bool Order::GetIsBuy()
{
    return _isbuy;
}

int Order::GetStockId()
{
    return _stock_id;
}

int Order::GetNumber()
{
    return _number_of_shares;
}

double Order::GetPrice()
{
    return _price;
}

void Order::SetIsBuy(bool isbuy)
{
    _isbuy = isbuy;
}

void Order::SetNumber(int n)
{
    _number_of_shares = n;
}

void Order::SetPrice(double price)
{
    _price = price;
}
