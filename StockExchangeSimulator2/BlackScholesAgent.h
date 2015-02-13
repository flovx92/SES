
#ifndef BLACKSCHOLESAGENT_H
#define BLACKSCHOLESAGENT_H

#include "BlackScholesAgent.h"
#include "Agent.h"
class Option;
class Stock;
class Stat;
#include <iostream>
#include <vector>
using namespace std;

class BlackScholesAgent : public Agent
{
protected:
    double _margin;
    vector<double> _delta;
public :
    BlackScholesAgent(int id, double cash, vector<double> stock_prices, double margin);
    void Do(int time, vector<Stock> stocks, vector<Option*> options, Treasure* tres,vector<Company*> companies, vector<Stat*>);
    ~BlackScholesAgent();
};
double Normal_distribution(double x);
double first_arg(double S, double K, double r, double rho, double sigma, int mat);
double sec_arg(double sigma, int mat,double d1);
double price_call_blacks(double S,double K, double r, double rho, int mat,double d1,double d2);
double price_put_blacks(double S,double K, double r, double rho, int mat,double call_price);
double delta_call(int mat,double rho, double d1);
double delta_put(int mat, double rho, double d1);

#endif // BLACKSCHOLESAGENT_H


