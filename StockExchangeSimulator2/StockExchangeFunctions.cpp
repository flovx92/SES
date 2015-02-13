//
//  StockExchangeFunctions.cpp
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 04/10/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#include "StockExchangeFunctions.h"
#include "Order.h"
#include <iostream>
#include <vector>
using namespace std;


vector<double> Sorting(vector<Order*> orders, int stock, bool isbuy)
{
    vector<double> results;
    int n = orders.size();
    
    for (int i=0; i<n; i++)
    {
        Order* order = orders[i];
        if (order -> GetIsBuy() == isbuy && order -> GetStockId()==stock)
        {
            int nb_stocks = order -> GetNumber();
            for (int k=0; k<nb_stocks; k++)
            {
                results.push_back(order -> GetPrice());
            }
        }
    }
    if (n>0)
    {
        results = Ordering(results,isbuy);
    }
    return results;
}



vector<double> Ordering(vector<double> tab, bool isbuy)
{
    vector<double> results;
    int n = tab.size();
    
    if(isbuy)
    {
        for (int i=0; i<n; i++)
        {
            int i_max = 0;
            for (int j=1; j<(n-i); j++)
            {
                if (tab[j]>tab[i_max])
                {
                    i_max = j;
                }
            }
            results.push_back(tab[i_max]);
            tab.erase(tab.begin() + i_max);
        }
    }
    else
    {
        for (int i=0; i<n; i++)
        {
            int i_min = 0;
            for (int j=1; j<(n-i); j++)
            {
                if (tab[j]<tab[i_min])
                {
                    i_min = j;
                }
            }
            results.push_back(tab[i_min]);
            tab.erase(tab.begin() + i_min);
        }
    }
    
    return results;
}




void Insert(int j, Order*& order, vector<Order*>& orders)
{
    int n = orders.size();
    if (n==0)
    {
        orders.push_back(order);
    }
    else
    {
        Order* previous = order;
        for (int k =j; k<n; k++)
        {
            Order* saved = orders[k];
            orders[k]=previous;
            previous = saved;
        }
        orders.push_back(previous);
    }
}
