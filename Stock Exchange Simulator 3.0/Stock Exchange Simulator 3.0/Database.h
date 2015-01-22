#pragma once
//
//  Database.h
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 09/10/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#ifndef __Stock_Exchange_Simulator__Database__
#define __Stock_Exchange_Simulator__Database__

#include "Agent.h"
#include "Company.h"
#include "Bank.h"
#include "StockExchange.h"
#include "Dept_Treasury.h"
#include <iostream>
#include <vector>
using namespace std;


class Database
{
private:
    vector<Agent*> _pagents;
    StockExchange* _pse;
    Treasure* _ptreasure;
    vector<Bank*> _banks;
    vector<Company*> _companies;
    
public :
    Database();
    void Display();
    void SetStockExchange(StockExchange* se);
    StockExchange* GetStockExchange();
    void SetTreasure(Treasure* treasure);
    int GetTime();
    void AddAgent(Agent& agent);
    vector<Agent*> GetAgents();
    Agent* GetAgent(int id_agent);
    void AddCompany(Company& co);
    vector<Company*> GetCompanies();
    void AddBank(Bank& bank);
    Treasure* GetTreasure();
    void BondPayment();
    
    
};

#endif /* defined(__Stock_Exchange_Simulator__Database__) */
