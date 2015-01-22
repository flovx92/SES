#pragma once
//
//  StockExchange.h
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 04/10/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#ifndef __Stock_Exchange_Simulator__StockExchange__
#define __Stock_Exchange_Simulator__StockExchange__

#include "Company.h"
#include "Agent.h"
#include "Stock.h"
#include "Order.h"
#include "Option.h"
#include <iostream>
#include <vector>
using namespace std;


class StockExchange
{
private:
    int _time;
    double _cash;
    vector<Stock> _stocks;
    vector<Order*> _orders;
    vector<Option*> _options;//options to sell
    vector<Option*> _sold_options;//options sold
    //vector<Stock*> _portefolio; //stocks to introduce
    
    
public:
    StockExchange();
    int GetTime();
    vector<Stock> GetStocks();
    vector<Option*> GetOptions();
    void AddStock(Stock stock);
    void DisplayStocks(vector<Company*> companies);
    void DisplayOrders();
    //orders -> stocks
    void AddNewOrders(Agent* agent);
    void UpdatePrices();
    void UpdateOrders(vector<Agent*> pagents);//link best buyer to best seller and launch Execute
    void ExecuteOrders(Agent* buyer, Agent* seller, int& j,Order* buyorder,int& k, Order* sellorder);
    //option
    void AddNewOptions(Agent* agent);
    void UpdateOptions(vector<Agent*> pagents);// make the transaction of the derivative
    void ExerciceOptions(vector<Agent*> pagents);
    void ExpiredOptions(vector<Agent*> pagents);//delete everywhere expired options
    //main function
    void NextDay(vector<Agent*> pagents);//erase all orders and options and scan everything again to be updated
};

#endif /* defined(__Stock_Exchange_Simulator__StockExchange__) */
