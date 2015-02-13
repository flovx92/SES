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


#include "Stock.h"
#include "Bond.h"
#include "Order.h"
#include <iostream>
#include <vector>
using namespace std;

class Agent;
class Option;

class Company;

class StockExchange
{
private:
    int _time;
    double _cash;
    vector<Stock> _stocks;//all the stocks
    vector<Order*> _orders;//all the orders
    vector<Option*> _options;//options to sell
    vector<Option*> _sold_options;//options sold
	vector<Bond> _bonds;//bonds bought by agents, sold before the expiration date
    //vector<Stock*> _portefolio; //stocks to introduce
    
    
public:
    StockExchange();
    int GetTime();
    vector<Stock> GetStocks();
    vector<Option*>& GetOptions();
	vector<Bond> GetBonds();
    void AddStock(Stock stock);
	//General
	void SetCash(double delta);
    //orders -> stocks
    void AddNewOrders(Agent* agent);//copy the orders of the agent
    void UpdatePrices();//
    void UpdateOrders(vector<Agent*> pagents);//link best buyer to best seller and launch Execute
    void ExecuteOrders(Agent* buyer, Agent* seller, int& j,Order* buyorder,int& k, Order* sellorder);//make the actual transaction
    //option
    vector<Option*> GetSoldOptions();
    void AddNewOptions(Agent* agent);
    void UpdateOptions(vector<Agent*> pagents);// make the transaction of the derivative
    void ExerciceOptions(vector<Agent*> pagents);
    void ExpiredOptions(vector<Agent*> pagents);//delete everywhere expired options
	//Bond
	void EraseBond(int bond_id);
    //main function
    void NextDay(vector<Agent*> pagents, double rate, int ref_mat);//erase all orders and options and scan everything again to be updated
};

#endif /* defined(__Stock_Exchange_Simulator__StockExchange__) */
