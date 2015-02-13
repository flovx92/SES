#pragma once
#ifndef __Stock_Exchange_Simulator__TreeAgent__
#define __Stock_Exchange_Simulator__TreeAgent__

#include "Agent.h"

class Stock;
class Option;

#include <iostream>
#include <vector>
using namespace std;

class TreeAgent : public Agent
{
protected:
    double _margin;
public :
    TreeAgent(int id, double cash, vector<double> stock_prices, double margin);
    void Do(int time, vector<Stock> stocks, vector<Option*> options, Treasure* tres, vector<Company*> companies, vector<Stat*> stats);
    ~TreeAgent();
};

double option_price_call_european_binomial (double S, double K, double r, double sigma, int steps);


#endif

/* defined(__Stock_Exchange_Simulator__TreeAgent__) */




