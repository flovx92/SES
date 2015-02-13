#ifndef BONDAGENT_H
#define BONDAGENT_H


#include "Agent.h"
class Company;
class Option;
class Stock;
class Stat;
#include <iostream>
#include <vector>
using namespace std;

class BondAgent : public Agent
{
protected:
    double _margin;
    int _maturity;
public :
    BondAgent(int id, double cash, vector<double> stock_prices, double margin, int mat);
    void Do(int time, vector<Stock> stocks, vector<Option*> options, Treasure* tres,vector<Company*> companies , vector<Stat*> stats);
    ~BondAgent();
};


#endif // BONDAGENT_H
