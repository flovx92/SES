//
//  General.cpp
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 28/12/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#include "General.h"
#include <QGlobal.h>
#include <QTime>
#include "Company.h"
#include "Database.h"
#include "Agent.h"
#include "RandomAgent.h"
#include "Treasure.h"
#include "StockExchange.h"
#include "Stat.h"
#include "SharpeAgent.h"
#include "BondAgent.h"
#include "CompanyAgent.h"
#include "BlackScholesAgent.h"
#include "TreeAgent.h"

#include <QString>
//general functions!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!




double Normal_generator(double mu,double sigma)//Box-Muller method
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());


    double U1 = qrand()%1000;
    double U2 = qrand()%1000;
    double N = sqrt(-2*log(U1/1000))*cos(2*3.14159*U2/1000);
    return mu+sigma*N;
}

double max(double a, double b)
{
    if (a>b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

double convert_price(double p)
{
    int a= (int) (p*100);
    double res =  (((double) a)/100.);
    return res;
}

//end general functions!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


// General function !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

double absval(double num)
{
    if (num >= 0)
    {
        return num;
    }
    else
    {
        return (-num);
    }
}

// end general function !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

Database* Initialisation(int select)
{
    Database* pdata = new Database();
    StockExchange* pbourse = new StockExchange();
    pdata -> SetStockExchange(pbourse);
    Treasure* ptreasure = new Treasure(1., 15000, 0.01, 2., 30, 20);
    pdata -> SetTreasure(ptreasure);
    
    //Companies
    int nb_companies = 5;

    vector<QString> company_name(nb_companies);
    company_name[0] = "World Company";
    company_name[1] = "Societe Centrale";
    company_name[2] = "Vivaldi";
    company_name[3] = "Bouguys Immo.";
    company_name[4] = "Universal Motors";

    vector<int> stock_nb(nb_companies);
    stock_nb[0] = 10000;
    stock_nb[1] = 7000;
    stock_nb[2] = 5000;
    stock_nb[3] = 2000;
    stock_nb[4] = 1000;
    
    int stock_total = 0;
    
    vector<double> stock_prices(nb_companies);
    stock_prices[0] = 10;
    stock_prices[1] = 20;
    stock_prices[2] = 50;
    stock_prices[3] = 70;
    stock_prices[4] = 100;
    

    Company* pcompany0 = new Company(0,company_name[0],1000000,10,50,1300,10,5,5,5,2);
    pdata -> AddCompany(*pcompany0);
    Company* pcompany1 = new Company(1,company_name[1],1000000,20,50,15000,700,100,50,50,2);
    pdata -> AddCompany(*pcompany1);
    Company* pcompany2 = new Company(2,company_name[2],1000000,30,45,25000,1250,100,50,50,2);
    pdata -> AddCompany(*pcompany2);
    Company* pcompany3 = new Company(3,company_name[3],1000000,15,20,1250,1000,100,50,50,2);
    pdata -> AddCompany(*pcompany3);
    Company* pcompany4 = new Company(4,company_name[4],1000000,49,50,1300,1500,100,50,50,2);
    pdata -> AddCompany(*pcompany4);
    
    
    for (int i=0; i<nb_companies; i++)
    {
        pbourse -> AddStock(Stock(i, company_name[i],stock_prices[i], stock_nb[i]));
        stock_total += stock_nb[i];
    }
    
    //random
    
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());


	
    //agents creation

    double cash = 50000;
    vector<Agent*> pagents;
    switch(select)
    {
        case 0:
        {
            RandomAgent* pagent1 = new RandomAgent(0,cash,stock_prices,.01);
            pagents.push_back(pagent1);
        }

        case 1:
        {
            CompanyAgent* pagent1 = new CompanyAgent(0,cash,stock_prices,.05);
            pagents.push_back(pagent1);
        }

        case 2:
        {
            SharpeAgent* pagent1 = new SharpeAgent(0,cash,stock_prices,15,2,0,0.01);
            pagents.push_back(pagent1);
        }

        case 3:
        {
            BondAgent* pagent1 = new BondAgent(0,cash,stock_prices,.0005,20);
            pagents.push_back(pagent1);
        }
        case 4:
        {
            BlackScholesAgent* pagent1 = new BlackScholesAgent(0,cash,stock_prices,0.);
            pagents.push_back(pagent1);
        }
        case 5:
        {
            TreeAgent* pagent1 = new TreeAgent(0,cash,stock_prices,0.5);
            pagents.push_back(pagent1);
        }
    }



    for(int i = 0; i<10; i++)
    {
        //double margin = (qrand()%(20)-10)/(double) 100;
        //warning rand≠U(0,1)
        double margin = (((i/(double)10)*10) -5)/((double) 100);
        RandomAgent* pagent = new RandomAgent(1+i,cash,stock_prices,margin);
        pagents.push_back(pagent);
    }

    for(int i = 0; i<5; i++)
    {

        double margin = (((i/(double)10)*10) -5)/((double) 100);
        SharpeAgent* pagent = new SharpeAgent(11+i,cash,stock_prices,10,2,0,margin);
        pagents.push_back(pagent);
    }
    for(int i = 0; i<10; i++)
    {
        BondAgent* pagent = new BondAgent(16+i,cash,stock_prices,i/10000.,i+5);
        pagents.push_back(pagent);
    }
    for(int i = 0; i<10; i++)
    {
        CompanyAgent* pagent = new CompanyAgent(26+i,cash,stock_prices,i/100.);
        pagents.push_back(pagent);
    }
    for(int i = 0; i<10; i++)
    {
        BlackScholesAgent* pagent = new BlackScholesAgent(36+i,cash,stock_prices,i/100.);
        pagents.push_back(pagent);
    }
/*
    for(int i = 0; i<10; i++)
    {
        TreeAgent* pagent = new TreeAgent(46+i,cash,stock_prices,i/100.);
        pagents.push_back(pagent);
    }

*/
    int nb_agents = pagents.size();
    int stock_per_agent = stock_total/nb_agents;
    int reste = stock_total - nb_agents*stock_per_agent;


    //shares distribution
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
            int stock = (int) qrand()%(stock_total);
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
    
    //Stat(s) creation
    
    Stat* stat0 = new Stat(5,nb_companies);
    pdata->AddStat(stat0);
    Stat* stat1 = new Stat(10,nb_companies);
    pdata->AddStat(stat1);
    Stat* stat2 = new Stat(15,nb_companies);
    pdata->AddStat(stat2);
    Stat* stat3 = new Stat(20,nb_companies);
    pdata->AddStat(stat3);
    
    return pdata;
}

void NextDay(Database* pdata)//General Update of the whole "world"
{
	int time = pdata -> GetTime();
	int newtime = time+1;
	StockExchange* pse = pdata -> GetStockExchange();
	Treasure* ptreasure = pdata -> GetTreasure();
    vector<Stock> stocks = pse -> GetStocks();
	vector<Company*> pcomp = pdata -> GetCompanies();
	int nb_companies = pcomp.size();
	vector<Agent*> pagents = pdata -> GetAgents();
	int nb_agents = pagents.size();

    //treasure update
    double rate = ptreasure -> GetNewRate();

    //StEx update
	pse -> NextDay(pagents,rate,ptreasure-> GetMaturity());

    //Bond payment
	pdata -> BondPayment();

    //Companies updates
	for(int i = 0; i<nb_companies; i++)
	{
		Company* cp = pcomp[i];
        Stock stock = stocks[i];
        cp -> UpdateCompany(newtime,rate,stock.GetNumber(),pagents);
	}

    //stats update
    vector<Stat*> stats = pdata->GetStats();
    for(int i =0; i<(int) stats.size(); i++)
    {
        Stat* stat = stats[i];
        stat->Update(newtime, pse->GetStocks(), pdata->GetCompanies());
    }

    //agents updates -> function DO
    vector<Option*> poptions = pse -> GetOptions();
	for(int j = 0; j<nb_agents;j++)
	{
		Agent* pagent = pagents[j];
        pagent -> Do(newtime, stocks, poptions,ptreasure,pdata->GetCompanies(),pdata->GetStats());
        //cout << "End\n";
	}

    //cout << newtime << "\n";


}
