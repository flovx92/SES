
//  Agent.cpp
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 06/10/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#include "Agent.h"
#include "Order.h"
#include "Portfolio.h"
#include "Stock.h"
#include "Option.h"
#include "Treasure.h"
#include "Bond.h"
#include "General.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <Stat.h>

using namespace std;

Agent::Agent(int id,double cash,vector<double> stock_prices)
{
    _id = id;
    _cash = cash;
    int stocks_number = stock_prices.size();
    _portfolio = vector<Portfolio*>(stocks_number);
    for (int i=0; i<stocks_number; i++)
    {
        Portfolio* p = new Portfolio(0);
        _portfolio[i] = p;
    }
    

}

int Agent::GetId()
{
    return _id;
}

vector<Order>& Agent::GetOrders()
{
    return _orders;
}

Order Agent::GetOrder(int i)
{
    return _orders[i];

}

void Agent::SetOrder(Order neworder)
{
    int id = neworder.GetId();
    int i=0;
    bool stop = false;
    while (!stop && i<(int) _orders.size())
    {
        if (_orders[i].GetId()==id)
        {
            stop=true;
        }
        else
        {
            i++;
        }
    }
    
    _orders[i]=neworder;
}


double Agent::GetCash()
{
    return _cash;
}

void Agent::SetCash(double newcash)
{
    _cash = newcash;
}

void Agent::ChangeCash(double delta)
{
    _cash+=delta;
}


void Agent::ReceiveDividends(int stock_id, double price)
{
    ChangeCash(price);
    _portfolio[stock_id]->SetDividends(price);
}


void Agent::MakeAnOrder(int time,int stock_id, bool is_buy, int number_of_shares, double price)
{
    int id=1;
    int n = _orders.size();
    if (n!=0)
    {
        Order ord = _orders[n-1];
        id = ord.GetId()+1;
    }
    
    Order order(id, time, stock_id, _id, is_buy, number_of_shares, price);
    _orders.push_back(order);

}

void Agent::EraseOrder(int order_id)
{
    int i=0;
    bool stop = false;
    while (!stop && i<(int) _orders.size())
    {
        if (_orders[i].GetId()==order_id)
        {
            stop=true;
        }
        else
        {
            i++;
        }
    }
    _orders.erase(_orders.begin()+i);
}

void Agent::EraseUsedOrders()//after being used by the stockexchange the number is set to 0 ->this functions erase properly those orders
{
    int n = _orders.size();
    int compteur = 0;
    for( int i = 0; i < n; i++)
    {
        Order order = _orders[i-compteur];
        if(order.GetNumber() == 0)
        {
            _orders.erase(_orders.begin() + i-compteur);
            compteur+=1;
        }
    }
}

void Agent::EraseOldOrders(int time, int limit)
{
    int n = _orders.size();
    int erased = 0;
    for(int i=0; i<n; i++)
    {
        Order order = _orders[i - erased];
        int id = order.GetId();
        int t = order.GetTime();
        if(t<time - limit)
        {
            EraseOrder(id);
            erased++;
        }
    }
}

void Agent::EraseAllOrders()
{
	int n = _orders.size();
	for(int i = 0; i<n ; i++)
	{
		_orders.erase(_orders.begin());
	}
}

vector<Portfolio*> Agent::GetPortfolio()
{
    return _portfolio;
}

void Agent::SetPortfolio(int stock_id, int number, double price, bool isbuy)
{
    int delta = number;
    if (!isbuy)
    {
        delta = -delta;
    }
    Portfolio* pp = _portfolio[stock_id];
    pp -> SetPortfolio(delta, price);
    
}



//Bonds

vector<Bond> Agent::GetBonds()
{
    return _bonds;
}

void Agent::MakeBond(int time,int maturity, Treasure* treasure, double price)
{
	price = convert_price(price);
    treasure -> AddDemand(price);
    _cash -= price;
    Bond bond(time, maturity,treasure -> GetRate(), price);
    _bonds.push_back(bond);
    
}

void Agent::SellBond(int bond_id)
{
	Bond* bond = &_bonds[bond_id];
	bond -> Sold();
	
	
}

void Agent::EraseBond(int bond_id)
{
    _bonds.erase(_bonds.begin() + bond_id);
}


//Options

vector<Option*>& Agent::GetOptionStore()
{
    return _option_store;
}

vector<Option*> Agent::GetOptions()
{
    return _options;
}


void Agent::SellOption(int id_stock, int maturity, double strike, double price, bool is_call, double delta)
//puts a new option in my option_sore
{
    int op_id = 1;
    unsigned long n = _option_store.size();
    if (n!=0)
    {
        op_id= _option_store[n-1]->GetId()+1;
    }
    Option* poption = new Option(op_id, _id, id_stock, maturity, strike, is_call, price, delta);
    _option_store.push_back(poption);
}

void Agent::BuyOption(int time, int id, int seller, double offer, vector<Option*>& options)
//change the informations (buyer_id and price) in the option that I want to buy so that the stock exchange know that I made on offer
{
    int i = 0;
    bool stop = false;
    while (! stop && i < (int) options.size())
    {
        Option* poption = options[i];
        int id_option = poption -> GetId();
        int id_seller = poption -> GetIdSeller();
        if (id_option == id && id_seller == seller)
        {
            stop = true;
            double price1 = poption -> GetOffer();
            if (offer > price1)
            {
                poption -> NewBuyer(_id,offer);
                poption -> SetTime(time);

            }
        }
        else
        {
            i++;
        }
    }
}

void Agent::AddOption(Option* poption)
//used by the StEx in order to put newly bought options of mine in my "options" vector
{
    _options.push_back(poption);
}

void Agent::EraseOption(int id_option)//when I want to erase an option that I sold
{
    int i=0;
    int n = _option_store.size();
    bool stop = false;
    while (! stop && i<n)
    {
        Option* op = _option_store[i];
        
        if (id_option == op->GetId())
        {
            stop = true;
            _option_store.erase(_option_store.begin()+i);

        }
        else
        {
            i++;
        }
    }
}

void Agent::EraseBoughtOption(int id_option, int id_seller)//at the end of the life of an option that I bought
{
    int i=0;
    int n = _options.size();
    bool stop = false;
    while (! stop && i<n)
    {
        Option* op = _options[i];
        
        if (id_option == op -> GetId() && id_seller == op -> GetIdSeller())
        {
            stop = true;
            _options.erase(_options.begin()+i);
        }
        else
        {
            i++;
        }
    }
}

void Agent::ChangePriceOption(int id, double price)//change the price of an option I wasn't able to sell so far
{
    int i=0;
    int n = _option_store.size();
    bool stop = false;
    while (! stop && i<n)
    {
        Option* op = _option_store[i];
        
        if (id == op->GetId())
        {
            stop = true;
            if (op->GetIdSeller() == op->GetIdBuyer())
            {
                op->SetPrice(price);
                _option_store[i] = op;
            }
        }
        else
        {
            i++;
        }
    }
}

void Agent::ExerciceOption(int i)
{
    Option* op = _options[i];
    op -> Exercice();
}

void Agent::Do(int time,vector<Stock> stocks, vector<Option*> options, Treasure* tres, vector<Company*> companies, vector<Stat*> stats)
{


}


void Agent::NewOrder(int time,int id_stock,bool isbuy, int number_to_buy, double price)
{
    int n = _orders.size();
    int i = 0;
    bool stop = false;
    while(stop==false and i<n)
    {
        Order order = _orders[i];
        if (order.GetStockId()==id_stock)
        {
            order.SetNumber(number_to_buy);
            order.SetPrice(price);
            order.SetIsBuy(isbuy);
            stop = true;
        }
        else
        {
            i++;
        }
    }
    if(stop==false)
    {
        MakeAnOrder(time,id_stock, isbuy, number_to_buy, price);
    }
}
Agent::~Agent()
{
    
}
