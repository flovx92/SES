//
//  StockExchange.cpp
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 04/10/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#include "Company.h"
#include "StockExchange.h"
#include "StockExchangeFunctions.h"
#include "Order.h"
#include "Stock.h"
#include <iostream>
#include <vector>
using namespace std;

StockExchange::StockExchange()
{
    _time = 0;
    _cash = 0;
}

int StockExchange::GetTime()
{
    return _time;
}

vector<Stock> StockExchange::GetStocks()
{
    return _stocks;
}

vector<Option*> StockExchange::GetOptions()
{
    return _options;
}

void StockExchange::AddStock(Stock stock)
{
    _stocks.push_back(stock);
}


void StockExchange::DisplayStocks(vector<Company*> companies)
{
    cout << "\n";
    cout << "t : " << _time << "\n";
    int n = _stocks.size();
    for (int i=0; i<n; i++)
    {
        Stock stock = _stocks[i];
        int co_id = stock.GetCompanyID();
        string co_name = (*companies[co_id]).GetName();
        cout << "L'action " << co_id << " est au prix de " << stock.GetPrice() << " ! " << "\n";
        cout << "Buy : $" << stock.GetBuyPrice() << ". Sell : $" << stock.GetSellPrice() << "." << "\n";
        
    }
    cout << "\n";
}

void StockExchange::DisplayOrders()
{
    cout << "\n";
    cout << _time << "\n";
    int n = _orders.size();
    for (int i=0; i<n; i++)
    {
        Order order = *_orders[i];
        cout << "L'ordre de l'agent " << order.GetAgent() << " est au prix de " << order.GetPrice() << "\n";
        if (order.GetIsBuy())
        {
            cout << "il achète "<< order.GetNumber() << " action(s) d'ID " << order.GetStockId() << " ! " << "\n";
        }
        else
        {
            cout << "il vend "<< order.GetNumber() << " actions d'ID " << order.GetStockId() << " ! " << "\n";
        }
        
    }
    int m = _orders.size();
    cout << "Il y a " << m << " ordre(s) non execute(s)" << "\n";
    cout << "Caisse : " << _cash << "\n";
    cout << "\n";
}


void StockExchange::AddNewOrders(Agent* agent)
{
    vector<Order>& agent_orders = agent -> GetOrders();
    for (int i=0; i< (int) agent_orders.size(); i++)
    {
        Order* order = &agent_orders[i];
        double price =order -> GetPrice();
        int j=0;
        bool stop = false;
        while (!stop && j< (int) _orders.size())
        {
            if (price>_orders[j] -> GetPrice())
            {
                stop = true;
            }
            else
            {
                j++;
            }
        }
        Insert(j, order, _orders);
    }
}

void StockExchange::UpdatePrices()
{
    
    int number_stocks = _stocks.size();
    vector<double> results(number_stocks);
    vector<double> res_buy(number_stocks);
    vector<double> res_sell(number_stocks);

    for (int i=0; i<number_stocks; i++)
    {
        vector<double> buy_orders = Sorting(_orders,i,true);
        vector<double> sell_orders = Sorting(_orders,i,false);
        int n1 = buy_orders.size();
        int n2 = sell_orders.size();
        int m = min(n1,n2);
        
        int j = 0;
        bool stop = false;
        while (j<m && !stop)
        {
            if (buy_orders[j]<=sell_orders[j])
            {
                stop=true;
            }
            else
            {
                j++;
            }
        }
        if (j!=0)
        {
            double new_price = 0.5*(buy_orders[j-1]+sell_orders[j-1]);
            double new_buy = buy_orders[((j-1)/2)];
            double new_sell = sell_orders[((j-1)/2)];
            _stocks[i].NewPrice(new_price, new_buy, new_sell);
        }
        else
        {
            double new_price = _stocks[i].GetPrice();
            double new_buy = _stocks[i].GetBuyPrice();
            double new_sell = _stocks[i].GetSellPrice();
            _stocks[i].NewPrice(new_price, new_buy, new_sell);
        }
    }

    
    
}

void StockExchange::UpdateOrders(vector<Agent*> pagents)
{
    int n = _stocks.size();
    
    for (int i=0; i<n; i++)
    {
        int j = 0;
        int k = _orders.size()-1;
        while (j< (int) _orders.size() && k>0 && j<k)
        {
            Order* buyorder = _orders[j];
            if(buyorder -> GetStockId()==i && buyorder -> GetIsBuy())
            {
                Order* sellorder = _orders[k];
                if(sellorder -> GetStockId()==i && ! sellorder -> GetIsBuy())
                {
                    if (buyorder -> GetPrice() > sellorder -> GetPrice())
                    {
                        Agent* pseller = pagents[sellorder -> GetAgent()];
                        Agent* pbuyer = pagents[buyorder -> GetAgent()];
                        this -> ExecuteOrders(pbuyer,pseller,j,buyorder,k,sellorder);
                    }
                    else
                    {
                        j=k;
                    }
                }
                else
                {
                    k--;
                }
            }
            else
            {
                j++;
            }
        }
    }
	
}



void StockExchange::ExecuteOrders(Agent* buyer, Agent* seller, int& id_buy,Order* buyorder,int& id_sell, Order* sellorder)
{
    int buynumber = buyorder -> GetNumber();
    int sellnumber = sellorder -> GetNumber();
    
    if (buynumber>sellnumber)
    {
        // partial execution of buyorder
        double bprice = buyorder -> GetPrice();
        _cash = _cash + sellnumber*bprice;
        buyer -> ChangeCash(-sellnumber*bprice);
        buyorder -> SetNumber(buynumber-sellnumber);
        buyer -> SetPortfolio(buyorder -> GetStockId(), sellnumber,bprice, true);
        
        // complete execution of sellorder
        double sprice = sellorder -> GetPrice();
        _cash = _cash - sellnumber*sprice;
        seller -> ChangeCash(sellnumber*sprice);
        sellorder -> SetNumber(0);
        seller -> SetPortfolio(sellorder -> GetStockId(), sellnumber,sprice,false);
        id_sell--;
    }
    else
    {
        //complete execution of buyorder
        double bprice = buyorder -> GetPrice();
        _cash = _cash + buynumber*bprice;
        buyer -> ChangeCash( - buynumber*bprice);
        buyer -> SetPortfolio(buyorder -> GetStockId(), buynumber,bprice, true);
        buyorder -> SetNumber(0);
        id_buy++;
        
        if (buynumber==sellnumber)
        {
            //complete execution of sellorder
            double sprice = sellorder -> GetPrice();
            _cash = _cash - buynumber*sprice;
            seller -> ChangeCash(buynumber*sprice);
            seller -> SetPortfolio(sellorder -> GetStockId(), sellnumber,sprice, false);
            sellorder -> SetNumber(0);
            id_sell--;
        }
        else
        {
            // partial execution of sellorder
            double sprice = sellorder -> GetPrice();
            _cash = _cash - buynumber*sprice;
            seller -> ChangeCash(buynumber*sprice);
            sellorder -> SetNumber(sellnumber-buynumber);
            seller -> SetPortfolio(sellorder -> GetStockId(), sellnumber, sellorder -> GetPrice(), false);
            
        }
    }
}

void StockExchange::AddNewOptions(Agent* agent)
{
    vector<Option>& store = agent -> GetOptionStore();
    for (int i = 0; i< (int) store.size(); i++)
    {
        Option* poption = &store[i];
        if (poption -> GetIdBuyer() == poption -> GetIdSeller())//if different it means that the option was already bought
        {
            _options.push_back(poption);
        }
        else
        {
            _sold_options.push_back(poption);
        }
        
    }
    
    
}

void StockExchange::UpdateOptions(vector<Agent*> pagents)
{
    //erase expired options
    ExpiredOptions(pagents);
    
    //make all possible transactions
    int n = _options.size();
    for (int i=0; i<n; i++)
    {
        Option* poption = _options[i];
        int id_seller = poption -> GetIdSeller();
        int id_buyer = poption -> GetIdBuyer();
        
        if (id_buyer != id_seller)
        {
            //option transaction
            double offer = poption -> GetOffer();
            double price = poption -> GetPrice();
            Agent* pbuyer = pagents[id_buyer];
            pbuyer -> ChangeCash(offer);
            pbuyer -> AddOption(poption);
            Agent* pseller = pagents[id_seller];
            pseller -> ChangeCash(price);
            _cash+=offer - price;
            
        }
    }
    
    //check sold options which are exerciced
    int m = _sold_options.size();
    for (int j = 0; j<m; j++)
    {
        Option* poption = _sold_options[j];
        if (poption -> GetExercice())
        {
            ExerciceOptions(pagents);
        }
        
    }
}

void StockExchange::ExerciceOptions(vector<Agent*> pagents)
{
    int n = _sold_options.size();
    for (int i=0; i<n; i++)
    {
        Option* poption = _sold_options[i];
        bool exe = poption -> GetExercice();
        if (exe)
        {
            double delta = -1;
            if (poption -> GetIsCall())
            {
                delta = 1;
            }
            Agent* buyer = pagents[poption -> GetIdBuyer()];
            Agent* seller = pagents[poption -> GetIdSeller()];
            int id_stock = poption -> GetIdStock();
            int nb_stocks = poption -> GetNumberOfStocks();
            double strike = poption -> GetStrike();
            seller -> ChangeCash(delta*strike*nb_stocks);
            buyer -> ChangeCash(-delta*strike*nb_stocks);
            if (delta==1)
            {
                seller -> SetPortfolio(id_stock, nb_stocks, strike, false);
                buyer -> SetPortfolio(id_stock, nb_stocks, strike, true);
            }
            else
            {
                seller -> SetPortfolio(id_stock, nb_stocks, strike, true);
                buyer -> SetPortfolio(id_stock, nb_stocks, strike, false);
            }
            
        }
    }
}

void StockExchange::ExpiredOptions(vector<Agent*> pagents)
{
    int n = _options.size();
    for (int i=0; i<n; i++)
    {
        Option* poption = _options[i];
        int mat = poption -> GetMaturity();
        if (mat<_time)
        {
            int seller = poption -> GetIdSeller();
            pagents[seller] -> EraseOption(poption -> GetId());
        }
    }
    int m = _sold_options.size();
    for (int i =0; i<m; i++)
    {
        Option* poption = _options[i];
        int mat = poption -> GetMaturity();
        if (mat>_time)
        {
            int seller = poption -> GetIdSeller();
            pagents[seller] -> EraseOption(poption -> GetId());
            int buyer = poption -> GetIdBuyer();
            pagents[buyer] -> EraseBoughtOption(poption -> GetId(), seller);
        }
    }
}

void StockExchange::NextDay(vector<Agent*> pagents)
{
    _time++;
    //updates
    UpdatePrices();
    UpdateOrders(pagents);
    UpdateOptions(pagents);
    //formatting used orders
    int m = _orders.size();
    for (int i = 0; i<m; i++)
    {
        Order* porder = _orders[i];
        if (porder -> GetNumber() == 0)
        {
            int id = porder -> GetId();
			Agent* pagent = pagents[porder->GetAgent()];
            pagent -> EraseOrder(porder -> GetId());
        }
    }
    //formating stock exchange
    for (int i=0; i<m; i++)
    {
        _orders.erase(_orders.begin());
    }
    int n = _options.size();
    for (int i=0; i<n; i++)
    {
        _options.erase(_options.begin());
    }
    //Getting new information
    int k = pagents.size();
    for (int i=0; i<k; i++)
    {
        AddNewOrders(pagents[i]);
        AddNewOptions(pagents[i]);
    }
}





