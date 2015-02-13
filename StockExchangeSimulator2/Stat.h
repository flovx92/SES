
#ifndef STAT_H
#define STAT_H

#include <vector>
using namespace std;

class Stock;
class Company;

class Stat
{
protected :
    int _period;//the object contains statistics on the yields observed in the last "_period" turns
    vector< vector<double> > _adjusted_values;//price matrix of all the stocks adjusted with the last dividend distributed
    vector<double> _yields;//medium yields bserved for every stock
    vector< vector<double> > _covariances;//matrix of the covariances between the stocks


public:
    Stat(int period, int number_stocks);
    void AdjustStocks(int date, vector<Stock> stocks, vector<Company*> companies);
    void Update_yields(int date);
    void Update_covar(int date);
    void Update(int date, vector<Stock> stocks,vector<Company*> companies);
    vector<double> GetYields();
    vector< vector<double> > GetCovar();
    double GetPeriod();
    ~Stat();
};


Stat* GetStat(vector<Stat*> stats, int period);

#endif // STAT_H
