#ifndef SHARPEAGENT_H
#define SHARPEAGENT_H


#include "Agent.h"
#include "Order.h"
#include "Stock.h"
#include "Bond.h"
#include "Option.h"
#include "Portfolio.h"
#include <iostream>
#include <vector>
#include <Stat.h>
#include "Agent.h"
class Treasure;
class Company;
using namespace std;

class SharpeAgent : public Agent
{
protected:
    double _period;
    double _alpha;
    double _r_target;
    double _margin;


public :
    SharpeAgent(int id, double cash, vector<double> stock_prices,int period, double alpha, double r_target,double margin);
    vector<double> DistributionPortfolio();
    vector<double> DistributionA(int included);
    vector<double> DistributionB(int excluded, vector<double> dist_port);
    double ValueB(vector<double> distB, vector<Stock> stocks);
    double Maxisharp(double initial_weight, double RB, double sigmaB, double RA, double sigmaA,double cov);
    double Calculmat(vector<double> a,vector< vector<double> > m,vector<double> b);
    double Calculvect(vector<double> a,vector<double> b);

    void Do(int time, vector<Stock> stocks, vector<Option*> options,Treasure* tres, vector<Company*> companies ,vector<Stat*> stats);
    ~SharpeAgent();
};



#endif // SHARPEAGENT_H
