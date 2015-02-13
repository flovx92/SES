#include "Stat.h"
#include "Stock.h"
#include <vector>
#include "Company.h"

Stat::Stat(int period, int number_companies)
{

    //yields
    _yields = vector<double>(number_companies);
    _period = period;

    //covariance
    for(int i = 0; i<number_companies; i++)
    {
        vector<double> vect = vector<double>(number_companies);
        _covariances.push_back(vect);
    }

    //adjusted values
    for(int i = 0; i<number_companies; i++)
    {
        vector<double> vect = vector<double>(_period);
        _adjusted_values.push_back(vect);
    }


}



void Stat::AdjustStocks(int date, vector<Stock> stocks, vector<Company*> companies)
{
if(date>_period)
{
    for(int i = 0; i<(int) stocks.size();i++)
    {
        //creating the adjusted valued of the stock i over the period

          int div_date=(companies[i]->GetPaytime())-(companies[i]->GetDivPeriod());
          vector<double> values = stocks[i].GetPrices();

          if (div_date<date-_period) //no dividends have been emitted over the period : prices remain the same
              {
                int t0 = date - _period;
                for(int j = t0; j<t0 + _period ;j++)
                    {

                        _adjusted_values[i][j-t0]=values[j];//doute
                    }
              }
          else //case where some dividends have been emitted over the period : prices have to be corrected
              {
                       int t0 = date - _period;
                  //Step 1 : after the dividend emission : prices remain the same
                      for(int j = div_date; j<date ;j++)
                          {
                             _adjusted_values[i][j-t0]=values[j];
                          }

                  //Step 2 : correcting the price at the dividend emission
                      double div_per_share = ((double) companies[i]->GetDiv())/((double) stocks[i].GetNumber());
                      double price_after_div=values[div_date];
                      double uncorrected_price=values[div_date-1];
                      double corrected_price=(price_after_div*uncorrected_price)/(price_after_div+div_per_share);
                      _adjusted_values[i][div_date-1-t0]=corrected_price;

                  //Step 3 : correcting the prices before the dividend emission
                      for(int j = div_date-2; j>=t0 ;j--)
                          {
                            double yield=(values[j+1]-values[j])/values[j];
                            _adjusted_values[i][j - t0]=_adjusted_values[i][j+1]/(1+yield);
                          }
              }
    }
}
}



// This function creates the vector of yields
void Stat::Update_yields(int date)
{
    if(date > _period)
    {
        int n=(int) _adjusted_values.size();
        for(int i = 0; i<n;i++)
        {
            vector<double> values = _adjusted_values[i];
            double yield = 0;
            for (int j = 1; j<_period; j++)
            {
                double previous = values[j-1];
                yield+=(1/((double) _period))*(values[j] - previous)/previous;
            }
            _yields[i]=yield;
        }
    }
}

// This function creates the variance-covariance matrix
void Stat::Update_covar(int date)
{
    if(date > _period)
    {
       int n=(int) _adjusted_values.size();

        for(int i=0; i<n ; i++) {
            for(int j=0; j<n ; j++) {

                //calculation of xbar and ybar : means of the yields of stocks i and j over the period
                double xbar=0;
                double ybar=0;

                xbar = _yields[i];
                ybar = _yields[j];
                vector<double> values_i=_adjusted_values[i];
                vector<double> values_j=_adjusted_values[j];

                double covar=0; //temporary double to calculate the covariance between the yields of stock i and stock j
                for(int k=1; k<_period ; k++)
                {
                    double yieldik=(values_i[k]-values_i[k-1])/(values_i[k-1]);
                    double yieldjk=(values_j[k]-values_j[k-1])/(values_j[k-1]);

                    covar+=(yieldik-xbar)*(yieldjk-ybar)/((double) _period);
                }
                _covariances [i][j]=covar;
                }
        }
    }
}

void Stat::Update(int date, vector<Stock> stocks,vector<Company*> companies)
{
    AdjustStocks(date,stocks, companies);

    Update_yields(date);

    Update_covar(date);
/*
    int n = companies.size();
    if(_period == 20 and date>20)
    {

        for (int i=0; i<_period; i++)
        {
            cout << i <<":"<<_adjusted_values[0][i]<<"\n";
        }

        for(int i = 0; i<n; i++)
        {
            for(int j = 0; j<n; j++)
            {
                cout << "("<<i<<","<<j<< ") : "<<_covariances[i][j]<<"\n";
            }
        }
    }
*/
}

vector<double> Stat::GetYields()
    {
       return _yields;
    }

vector< vector<double> > Stat::GetCovar()
    {
        return _covariances;
    }

double Stat::GetPeriod()
    {
        return _period;
    }



Stat::~Stat()
    {

    }


Stat* GetStat(vector<Stat*> stats,int period)
{
    int i= 0;
    int n = stats.size();
    bool stop = false;
    while(stop == false and i<n)
    {
        Stat* stat = stats[i];
        if(stat->GetPeriod() == period)
        {
            stop = true;
        }
        else
        {
            i++;
        }
    }

    return stats[i];
}

