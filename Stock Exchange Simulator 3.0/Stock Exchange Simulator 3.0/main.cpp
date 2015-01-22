//
//  main.cpp
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 03/10/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#include <iostream>
#include <vector>
#include <random>
#include "General.h"
#include "Database.h"
#include "Stock.h"
#include "Order.h"
#include "StockExchange.h"
#include "StockExchangeFunctions.h"
#include "Company.h"
#include "Bank.h"
#include "Agent.h"
#include "RandomAgent.h"
#include "Dept_Treasury.h"
using namespace std;



Database* Initialisation(int nb_agents_per_bank, int nb_banks, double cash)
{
    Database* pdata = new Database();
    StockExchange* pbourse = new StockExchange();
    pdata -> SetStockExchange(pbourse);
    Treasure* ptreasure = new Treasure(5, 1000000, 0.1, 10, 5, 1);
    pdata -> SetTreasure(ptreasure);
    
    //Companies
    int nb_companies = 5;
    vector<int> stock_nb(nb_companies);
    stock_nb[0] = 10;
    stock_nb[1] = 7;
    stock_nb[2] = 5;
    stock_nb[3] = 2;
    stock_nb[4] = 1;
    
    int stock_total = 0;
    
    vector<double> stock_prices(nb_companies);
    stock_prices[0] = 10;
    stock_prices[1] = 20;
    stock_prices[2] = 50;
    stock_prices[3] = 70;
    stock_prices[4] = 100;
    

    Company* pcompany0 = new Company(0,"World Company",10000,1,1,1,10,5,5,5,2);
    pdata -> AddCompany(*pcompany0);
    Company* pcompany1 = new Company(1,"Société Centrale",1000000,1000,100,10000,1000,100,50,50,2);
    pdata -> AddCompany(*pcompany1);
    Company* pcompany2 = new Company(2,"Vivaldi",1000000,1000,100,10000,1000,100,50,50,2);
    pdata -> AddCompany(*pcompany2);
    Company* pcompany3 = new Company(3,"Bouguys Immo.",1000000,1000,100,10000,1000,100,50,50,2);
    pdata -> AddCompany(*pcompany3);
    Company* pcompany4 = new Company(4,"Universal Motors",1000000,1000,100,10000,1000,100,50,50,2);
    pdata -> AddCompany(*pcompany4);
    
    //pdata -> AddCompany(bourse);
    
    for (int i=0; i<nb_companies; i++)
    {
        pbourse -> AddStock(Stock(i, stock_prices[i], stock_nb[i]));
        stock_total += stock_nb[i];
    }
    
    //Agents
    
	random_device rd;
	mt19937 rand(rd());

    int nb_agents = nb_agents_per_bank*nb_banks;
    int stock_per_agent = stock_total/nb_agents;
    int reste = stock_total - nb_agents*stock_per_agent;
	
	//creation des agents
	vector<Agent*> pagents(0);

	Agent* pagent1 = new Agent(0,0,cash,stock_prices);
	pagents.push_back(pagent1);
	RandomAgent* pagent2 = new RandomAgent(1,1,cash,stock_prices,2.56);
	pagents.push_back(pagent2);

	//distribution des actions
    for (int i = 0; i<nb_agents; i++)
    {
        Agent* pagent = pagents[i];
        int nb = stock_per_agent;
        if (reste>0)
        {
            reste--;
            nb += 1;
        }
        
        for (int j = 0; j<nb; j++)
        {
            int stock = (int) rand()%(stock_total);
            int stock_id = 0;
            bool stop = false;
            while (!stop && stock_id<nb_companies)
            {
                stock -= stock_nb[stock_id];
                if (stock<0)
                {
                    stop = true;
                }
                else
                {
                    stock_id += 1;
                }
            }
            stock_nb[stock_id] -= 1;
            stock_total -= 1;
            pagent -> SetPortfolio(stock_id, 1, stock_prices[stock_id], true);
            double cash = pagent -> GetCash();
            pagent -> SetCash(cash - stock_prices[stock_id]);
            
        }
        
        pdata -> AddAgent(*pagent);
    }
    
    
    
    
    return pdata;
}


int main()
{
    std::cout << "Hello, World!" <<"\n";
    /* Initialisation & Bond tests
    Database* pdata = Initialisation(1,2,1000000);
    Database& data = *pdata;
    data.Display();
    Treasure* pt = data.GetTreasure();
    Treasure& tres = *pt;
    StockExchange* pse = data.GetStockExchange();
    StockExchange& se = *pse;
    
    tres.Display();
    
    Agent& agent = *data.GetAgent(0);
    
    agent.MakeBound(0, tres, 500000);
    tres.GetNewRate();
    tres.Display();
    se.NextDay(data.GetAgents());
    
    agent.MakeBound(1, tres, 1000000);
    tres.GetNewRate();
    tres.Display();
    data.BondPayment();
    
    agent.MakeBound(2, tres, 1100000);
    tres.GetNewRate();
    tres.Display();
    
    agent.MakeBound(3, tres, 1200000);
    tres.GetNewRate();
    tres.Display();
    
    agent.MakeBound(4, tres, 1300000);
    tres.GetNewRate();
    tres.Display();
    
    agent.MakeBound(5, tres, 1400000);
    tres.GetNewRate();
    tres.Display();
    
    agent.MakeBound(6, tres, 1500000);
    tres.GetNewRate();
    tres.Display();
    
    agent.MakeBound(7, tres, 1600000);
    tres.GetNewRate();
    tres.Display();
    
    agent.MakeBound(8, tres, 1700000);
    tres.GetNewRate();
    tres.Display();
    
    
    
    */
    
    //initilaisation
    Database* pdata = Initialisation(1, 2, 1000000);
    Database& data = *pdata;
    
    
    StockExchange& bourse = *data.GetStockExchange();
    
    
    
    Agent& agent1 = *data.GetAgent(0);
    Agent& agent2 = *data.GetAgent(1);
    
    
    
    /* Portfolio test
    vector<Portfolio*> pvectorportf = agent1.GetPortfolio();
    Portfolio& portf = *pvectorportf[0];
    int a = 0;
    agent1.SetPortfolio(0, portf.GetNumber()-1, portf.GetMedPrice() - 1, false);
    a = 1;
    agent1.SetPortfolio(0, 11, 1, false);
    a=2;
    agent1.SetPortfolio(0, 1, 0.5, true);
    a=3;
    */
    
    
    
    /* Company test
    vector<Company*> companies = pdata -> GetCompanies();
    Company& co1 = *companies[0];
    
    
    
    
    
    for (int i=1; i<11; i++)
    {
        
        co1.UpdateCompany(i, 0.001, 10, data.GetAgents());
        co1.Display();
        
    }
    */
    
    
    // Stock Exchange and shares market test
    //orders creation
    agent1.MakeAnOrder(0,0, true, 1, 10);
    agent1.MakeAnOrder(0,0, true, 1, 10.5);
    agent1.MakeAnOrder(0,0, true, 2, 11);
    agent1.MakeAnOrder(0,0, true, 1, 11.5);
    agent2.MakeAnOrder(0,0, false, 1, 9.5);
    agent2.MakeAnOrder(0,0, false, 1, 10);
    agent2.MakeAnOrder(0,0,false, 1, 10.5);
    agent2.MakeAnOrder(0,0,false, 1, 11);

    agent1.SellOption(0,100, 10, 1, false);
    agent2.SellOption(0, 100, 10, 1, true);
    //display before
    bourse.DisplayStocks(data.GetCompanies());
    //bourse récupère les ordres
    bourse.AddNewOrders(&agent1);
    bourse.AddNewOrders(&agent2);
    bourse.AddNewOptions(&agent1);
    bourse.AddNewOptions(&agent2);
    
    //bourse fait les transactions et affiche les new prix
    bourse.NextDay(data.GetAgents());
    bourse.DisplayStocks(data.GetCompanies());
    agent1.EraseOrder(1);
    
    
    
    agent1.BuyOption(1, 1, 2, bourse.GetOptions());
    int a=2;
    bourse.NextDay(data.GetAgents());
    
    
    agent1.ExerciceOption(0);
    bourse.NextDay(data.GetAgents());
    int b=3;
	agent1.Do(bourse.GetTime(),bourse.GetStocks(),bourse.GetOptions());
	agent2.Do(bourse.GetTime(),bourse.GetStocks(),bourse.GetOptions());
    cout << "End" << "\n";
    



	/*

	random_device rd;
	mt19937 rand(rd());
	//test loi uniforme
	double stat=0;
	for(int ite = 0; ite < 1000; ite++)
	{
		stat += (double) (rand()%1000);
	}
	
	cout << stat/1000 << "\n";
    

	//test loi normal

	stat = 0;
	double stat2 = 0;
	for(int ite = 0; ite < 100; ite++)
	{
		double r = Normal_generator(10,1);
		stat += r;
		stat2 += r*r;

	}
	double mu = stat/100;
	cout << mu << " and "<< stat2/100 - mu*mu<< "\n";
	*/

	return 0;
}

