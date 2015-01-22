//
//  Database.cpp
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 09/10/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#include "Database.h"


Database::Database()
{
}

void Database::Display()
{
    cout << "Agents :" << _pagents.size() << "\n";
    cout << "Companies :" << _companies.size() << "\n";
    cout << "Banks : " << _banks.size() << "\n";
    cout << "\n";
    
}

void Database::SetStockExchange(StockExchange* pse)
{
    _pse = pse;
}

StockExchange* Database::GetStockExchange()
{
    return _pse;
}

void Database::SetTreasure(Treasure* ptreasure)
{
    _ptreasure = ptreasure;
}


int Database::GetTime()
{
    return (*_pse).GetTime();
}

void Database::AddAgent(Agent& agent)
{
    Agent* pagent = &agent;
    _pagents.push_back(pagent);
}

vector<Agent*> Database::GetAgents()
{
    return _pagents;
}

Agent* Database::GetAgent(int id)
{
    Agent* pagent = _pagents[id];
    return pagent;
}

void Database::AddCompany(Company& co)
{
    _companies.push_back(&co);
}

vector<Company*> Database::GetCompanies()
{
    return _companies;
}

void Database::AddBank(Bank& bank)
{
    _banks.push_back(&bank);
}

Treasure* Database::GetTreasure()
{
    return _ptreasure;
}

void Database::BondPayment()
{
    int time = (*_pse).GetTime();
    Treasure& tres = *_ptreasure;
    int maturity = tres.GetMaturity();
    int ref_time = time-maturity;
    int n = _pagents.size();
    for (int i = 0; i<n; i++)
    {
        Agent& agent = *(_pagents[i]);
        vector<Bond> bonds = agent.GetBonds();
        int m = bonds.size();
        bool stop = false;
        int j =0;
        while (j<m && stop==false)
        {
            Bond bond = bonds[j];
            int btime = bond.GetTime();
            if (btime<=ref_time)
            {
                double rate = bond.GetRate();
                double x = 1 + (rate/100);
                double price = bond.GetPrice()*x;
                tres.SetCash(-price);
                agent.SetCash(agent.GetCash()+price);
                agent.EraseBond(j);
                j++;
            }
            else
            {
                stop = true;
            }
            
        }
    }
}



