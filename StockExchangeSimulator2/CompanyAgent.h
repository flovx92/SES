#ifndef COMPANYAGENT_H
#define COMPANYAGENT_H



#include "Agent.h"

class Option;
class Stock;
class Stat;
#include <iostream>
#include <vector>
using namespace std;
class Company;

class CompanyAgent : public Agent
{
protected:
    double _margin;
public :
    CompanyAgent(int id, double cash, vector<double> stock_prices, double margin);
    void Do(int time, vector<Stock> stocks, vector<Option*> options, Treasure* tres,vector<Company*> companies, vector<Stat*> stats);
    ~CompanyAgent();
};


#endif // COMPANYAGENT_H
