#ifndef __Stock_Exchange_Simulator__Database__
#define __Stock_Exchange_Simulator__Database__

#include <QApplication>
#include <iostream>
#include <vector>
#include <QTimer>
#include <QWidget>
using namespace std;

class StockExchange;
class Agent;
class Company;
class Treasure;
class Window;
class Stat;

class Database : public QWidget
{
    Q_OBJECT

private:
    QTimer* _timer;//timer counting the seconds between two turns.
    vector<Agent*> _pagents;//all the agents
    StockExchange* _pse;//the stock exchange
    Treasure* _ptreasure;//the treasure
    vector<Company*> _companies;//all the companies
    vector<Stat*> _stats;//the vector of stats with different "_period"

public slots:
    void Simulation(Window* frame);
    void DoOneSimulation();

    
public :
    explicit Database();
    void Display();
	//Construction
    void SetStockExchange(StockExchange* se);
    StockExchange* GetStockExchange();
    void SetTreasure(Treasure* treasure);
    int GetTime();
    void AddAgent(Agent& agent);
    vector<Agent*> GetAgents();
    Agent* GetAgent(int id_agent);
    void AddCompany(Company& co);
    vector<Company*> GetCompanies();
    Treasure* GetTreasure();
    void AddStat(Stat* stat);
    vector<Stat*> GetStats();
	//Bonds
    void BondPayment();
    //Simulation->Qt
    QTimer* GetTimer();
    ~Database();
    
};

#endif /* defined(__Stock_Exchange_Simulator__Database__) */
