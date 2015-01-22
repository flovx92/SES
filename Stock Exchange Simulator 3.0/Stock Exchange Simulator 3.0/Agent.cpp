
//  Agent.cpp
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 06/10/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#include "Agent.h"
#include "Order.h"
#include <iostream>
#include <vector>
using namespace std;

Agent::Agent(int id,int bank,double cash,vector<double> stock_prices)
{
    _id = id;
    _bank = bank;
    _cash = cash;
    int stocks_number = stock_prices.size();
    _portfolio = vector<Portfolio*>(stocks_number);
    for (int i=0; i<stocks_number; i++)
    {
        Portfolio* p = new Portfolio(0, stock_prices[i]);
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

void Agent::DisplayCash()
{
    cout << "L'agent " << _id << " a : $" <<_cash << "\n";
    cout << "\n";
}


void Agent::DisplayOrders()
{
    cout << "Agent " << _id << " orders :" << "\n";
    cout << "\n";
    for (int i=0; i<(int) _orders.size(); i++)
    {
        Order order = _orders[i];
        cout << "id : " <<  order.GetId() << "\n";
        cout << "agent : " <<  order.GetAgent() << "\n";
        cout << "stock Id : " <<  order.GetStockId() << "\n";
        cout << "isbuy : " <<  order.GetIsBuy() << "\n";
        cout << "number : " <<  order.GetNumber() << "\n";
        cout << "price : " <<  order.GetPrice() << "\n";
        cout << "\n";
    }
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
    
    Order order(id,time, stock_id, _id, is_buy, number_of_shares, price);
    _orders.push_back(order);
    //ces ordres sont ensuite mis dans l'objet bourse par une fonction extérieure à Agent.
    //ces ordres porteront à ce moment là le time et leur id.
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

void Agent::DisplayPortfolio()
{
    cout << "portfolio de l'agent " << _id << "\n";;
    int n = _portfolio.size();
    for (int i=0; i<n; i++)
    {
        cout << "Stock " << i << " : " << _portfolio[i] -> GetNumber() << "\n";
    }
    cout << "\n";
}



//Bonds

vector<Bond> Agent::GetBonds()
{
    return _bonds;
}

void Agent::MakeBond(int time, Treasure& treasure, double price)
{
    treasure.AddDemand(price);
    _cash -= price;
    Bond bond(time, treasure.GetRate(), price);
    _bonds.push_back(bond);
    
}

void Agent::EraseBond(int bond_id)
{
    _bonds.erase(_bonds.begin() + bond_id);
}


//Options

vector<Option>& Agent::GetOptionStore()
{
    return _option_store;
}



void Agent::SellOption(int id_stock, int maturity, double strike, double price, bool is_call)
{
    int op_id = 1;
    unsigned long n = _option_store.size();
    if (n!=0)
    {
        op_id= _option_store[n-1].GetId()+1;
    }
    Option option(op_id, _id, id_stock, maturity, strike, is_call, price);
    _option_store.push_back(option);
}

void Agent::BuyOption(int id, int seller, double offer, vector<Option*> options)
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
            }
        }
        else
        {
            i++;
        }
    }
}

void Agent::AddOption(Option* poption)
{
    _options.push_back(poption);
}

void Agent::EraseOption(int id_option)
{
    int i=0;
    int n = _option_store.size();
    bool stop = false;
    while (! stop && i<n)
    {
        Option op = _option_store[i];
        
        if (id_option == op.GetId())
        {
            stop = true;
            if (op.GetIdSeller() == op.GetIdBuyer())
            {
                _option_store.erase(_option_store.begin()+i);
            }
        }
        else
        {
            i++;
        }
    }
}

void Agent::EraseBoughtOption(int id_option, int id_seller)
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

void Agent::ChangePriceOption(int id, double price)
{
    int i=0;
    int n = _option_store.size();
    bool stop = false;
    while (! stop && i<n)
    {
        Option op = _option_store[i];
        
        if (id == op.GetId())
        {
            stop = true;
            if (op.GetIdSeller() == op.GetIdBuyer())
            {
                op.SetPrice(price);
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

void Agent::Do(int time,vector<Stock> stocks, vector<Option*> options)
{
    cout << "Je suis un agent!" << "\n";
}



Agent::~Agent()
{
    
}