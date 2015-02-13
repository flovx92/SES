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
    int _time;//time when the order is done (not really used)
    int _stock_id;
    int _agent;//whom this order is from
    bool _isbuy;
    int _number_of_shares;//wants to buy (or sell) "n" shares
    double _price;//price paid or received for the transaction
    
public:
    Order(int id_order, int time,int stock_id, int agent, bool isbuy, int number_of_shares, double price);
    int GetId();
    int GetTime();
    int GetAgent();
    bool GetIsBuy();
    int GetStockId();
    int GetNumber();
    double GetPrice();
    void SetIsBuy(bool isbuy);
    void SetNumber(int);
    void SetPrice(double price);
    
};

#endif /* defined(__Stock_Exchange_Simulator__Order__) */
