#pragma once
//
//  Agent.h
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 06/10/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#ifndef __Stock_Exchange_Simulator__Agent__
#define __Stock_Exchange_Simulator__Agent__


#include "Order.h"
#include "Stock.h"
#include "Bond.h"
#include "Option.h"
#include "Dept_Treasury.h"
#include "Portfolio.h"
#include <iostream>
#include <vector>
using namespace std;


class Agent
{
protected :
    int _id;
    int _bank;
    double _cash;
    vector<Portfolio*> _portfolio;
    vector<Order> _orders;
    vector<Bond> _bonds;
    vector<Option> _option_store;//Options seeking buyer or already sold
    vector<Option*> _options;//Option bought (present in the seller store even if not for sell)
    
    
public :
    Agent(int id,int bank,double cash, vector<double> stock_prices);
    int GetId();
    vector<Order>& GetOrders();
    Order GetOrder(int id);
    void SetOrder(Order neworder);//change a preexisting order
    double GetCash();
    void DisplayCash();
    void SetCash(double newcash);
    void ChangeCash(double delta);
    void DisplayOrders();
	//order
    void MakeAnOrder(int time,int stock_id, bool is_buy, int number_of_stocks, double price);
    void EraseOrder(int order_id);
	void EraseAllOrders();
	//portfolio
    vector<Portfolio*> GetPortfolio();
    void SetPortfolio(int stock_id, int number, double price, bool isbuy);
    void DisplayPortfolio();
    //bond
    vector<Bond> GetBonds();
    void MakeBond(int time, Treasure& treasure, double price);
    void EraseBond(int bond_id);
    //option
    vector<Option>& GetOptionStore();
    void SellOption(int id_stock, int maturity, double strike, double price, bool is_call);
    void BuyOption(int id, int seller, double offer, vector<Option*> options);//only a proposition (offer)
    void AddOption(Option* poption);//when a option is trasfered to him if bought
    void EraseOption(int id_option);
    void EraseBoughtOption(int id_option, int id_seller);
    void ChangePriceOption(int _id, double price);
    void ExerciceOption(int id);
    //virtual part
    virtual void Do(int time, vector<Stock> stocks, vector<Option*> options);
    ~Agent();
};


#endif /* defined(__Stock_Exchange_Simulator__Agent__) */