#include "Database.h"
#include "StockExchange.h"
#include "Agent.h"
#include "Company.h"
#include "Treasure.h"
#include "General.h"
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
#include <QApplication>
#include <QTimer>
#include <QWidget>
#include "Window.h"
#include "Stat.h"



Database::Database() : QWidget()
{

}

void Database::Display()
{
    cout << "Agents :" << _pagents.size() << "\n";
    cout << "Companies :" << _companies.size() << "\n";
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
    return _pse -> GetTime();
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


Treasure* Database::GetTreasure()
{
    return _ptreasure;
}

void Database::AddStat(Stat* stat)
{
    _stats.push_back(stat);
}

vector<Stat*> Database::GetStats()
{
    return _stats;
}

void Database::BondPayment()//makes the money transactions at the maturity of the bonds
{
    int time = _pse -> GetTime();

	//for the agents
    int n = _pagents.size();
    for (int i = 0; i<n; i++)
    {
        Agent* pagent = _pagents[i];
        vector<Bond> bonds = pagent -> GetBonds();
        int m = bonds.size();
        for(int j =0;j<m;j++)
        {
            Bond bond = bonds[j];
            int btime = bond.GetTime();
			int bmat = bond.GetMaturity();
            int bonds_erased = 0;
            if (btime+bmat<=time)
            {
                double rate = bond.GetRate();
				double coef = (double) bmat/ (double) (_ptreasure->GetMaturity());
                double x = pow(1 + (rate/100.), coef);
                double price = convert_price(bond.GetPrice()*x);
                _ptreasure -> SetCash(-price);
                pagent -> ChangeCash(price);
                pagent -> EraseBond(j-bonds_erased);
                bonds_erased+=1;
            }
             
        }
    }


	//for the stock exchange
	vector<Bond> sebonds = _pse -> GetBonds();
	int nb_bonds = sebonds.size();
	for (int a = 0;a<nb_bonds;a++)
	{
		Bond bond = sebonds[a];
		int btime = bond.GetTime();
		int bmat = bond.GetMaturity();
        if (btime+bmat<=time)
		{
			double rate = bond.GetRate();
			double coef = ((double) (bmat)/(double) (_ptreasure->GetMaturity()));
			double x = exp(coef*log(1 + (rate/100)));
            double price = convert_price(bond.GetPrice()*x);
            _ptreasure -> SetCash(-price);
            _pse -> SetCash(price);
            _pse -> EraseBond(a);
			a--;
			nb_bonds--;
		}
	}

}

//Qt functions

void Database::Simulation(Window* frame)
{
    _timer = new QTimer(this);

    _timer -> start(1);//5 sec
    _timer -> setInterval(5000);

    connect(_timer,SIGNAL(timeout()),this,SLOT(DoOneSimulation()));
    connect(_timer,SIGNAL(timeout()),frame,SLOT(Update()));


}

void Database::DoOneSimulation()
{
    NextDay(this);
    _timer -> start(1);
    _timer -> setInterval(1000);//the speed between turn
    if(this->GetTime()>=100)
    {
        _timer -> stop();
    }


}

QTimer* Database::GetTimer()
{
    return _timer;
}

Database::~Database()
{

}
