#pragma once
//
//  Order.h
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 04/10/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#ifndef __Stock_Exchange_Simulator__Order__
#define __Stock_Exchange_Simulator__Order__


#include <iostream>
#include <vector>
using namespace std;

class Order
{
private:
    int _id;//id for the agent
    int _time;
    int _stock_id;
    int _agent;
    bool _isbuy;
    int _number_of_shares;
    double _price;
    
public:
    Order(int id_order, int time,int stock_id, int agent, bool isbuy, int number_of_shares, double price);
    int GetId();
    int GetAgent();
    bool GetIsBuy();
    int GetStockId();
    int GetNumber();
    double GetPrice();
    void SetNumber(int);
    
};

#endif /* defined(__Stock_Exchange_Simulator__Order__) */
