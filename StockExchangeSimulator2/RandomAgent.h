#pragma once
#ifndef __Stock_Exchange_Simulator__RandomAgent__
#define __Stock_Exchange_Simulator__RandomAgent__



#include "Agent.h"

class Option;
class Stock;
class Stat;
#include <iostream>
#include <vector>
using namespace std;
class Company;

class RandomAgent : public Agent
{
protected:
    double _margin;
public :
    RandomAgent(int id, double cash, vector<double> stock_prices, double margin);
    void Do(int time, vector<Stock> stocks, vector<Option*> options, Treasure* tres,vector<Company*> companies, vector<Stat*> stats);
	~RandomAgent();
};


#endif /* defined(__Stock_Exchange_Simulator__RandomAgent__) */
