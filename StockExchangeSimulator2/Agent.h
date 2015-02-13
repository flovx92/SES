#pragma once
#ifndef __Stock_Exchange_Simulator__Agent__
#define __Stock_Exchange_Simulator__Agent__


#include <iostream>
#include <vector>

#include "Order.h"
#include "Option.h"
#include "Bond.h"

using namespace std;

class Portfolio;
class Treasure;
class Stock;
class Stat;
class Company;
class Agent
{
protected :
    int _id;
    double _cash;
    vector<Portfolio*> _portfolio;
    vector<Order> _orders; //orders transmitted to the stock exchange
    vector<Bond> _bonds;
    vector<Option*> _option_store;//Options seeking buyer or already sold
    vector<Option*> _options;//Option bought (the Option object is still present in the seller store even if not for sell)
    
    
public :
    Agent(int id,double cash, vector<double> stock_prices);
    int GetId();
    vector<Order>& GetOrders();
    Order GetOrder(int id);
    void SetOrder(Order neworder);//change a preexisting order
    double GetCash();
    void SetCash(double newcash);
    void ChangeCash(double delta);
    void ReceiveDividends(int stock_id, double price);
	//order
    void MakeAnOrder(int time,int stock_id, bool is_buy, int number_of_stocks, double price);
    void EraseOrder(int order_id);
    void EraseUsedOrders();
    void EraseOldOrders(int time,int limit);
	void EraseAllOrders();
    void NewOrder(int time,int id_stock, bool buy, int number_to_buy, double price);
	//portfolio
    vector<Portfolio*> GetPortfolio();
    void SetPortfolio(int stock_id, int number, double price, bool isbuy);
    //bond
    vector<Bond> GetBonds();
    void MakeBond(int time, int maturity,Treasure* treasure, double price);
	void SellBond(int bond_id);
    void EraseBond(int bond_id);
    //option
    vector<Option*>& GetOptionStore();
    vector<Option*> GetOptions();
    void SellOption(int id_stock, int maturity, double strike, double price, bool is_call, double delta);
    void BuyOption(int time, int id, int seller, double offer, vector<Option*>& options);//only a proposition (offer)
    void AddOption(Option* poption);//when a option is transfered to him if bought
    void EraseOption(int id_option);
    void EraseBoughtOption(int id_option, int id_seller);
    void ChangePriceOption(int _id, double price);
    void ExerciceOption(int id);
    //virtual part
    virtual void Do(int time, vector<Stock> stocks, vector<Option*> options, Treasure* tres,vector<Company*> companies, vector<Stat*> stats);
    ~Agent();
};


#endif /* defined(__Stock_Exchange_Simulator__Agent__) */
