#include "SharpeAgent.h"
#include "Stat.h"
#include <random>
#include <cmath>
#include "General.h"
#include "Agent.h"
#include "Treasure.h"
#include "QTime"


SharpeAgent::SharpeAgent(int id, double cash, vector<double> stock_prices, int period, double alpha, double r_target, double margin):Agent(id, cash, stock_prices)
{
    _period=period;
    _alpha=alpha;
    _r_target=r_target;
    _margin = margin;
}

//Gives the portfolio distribution
vector<double> SharpeAgent::DistributionPortfolio()
{
    int size = _portfolio.size();
    vector<double> dist;
    int total =0;
    for(int i =0; i < size ; i++)
    {
        int number = (_portfolio[i])->GetNumber();
        dist.push_back(number);
        total+=number;
    }
    for(int j =0; j < size; j++)
    {

        dist[j] = dist[j]/total;
    }
    return dist;
}

//This function creates the vector of stock-distribution of portfolio A
vector<double> SharpeAgent::DistributionA(int included)
{
    vector<double> distribution_A;
    for(int i=0; i<(int) _portfolio.size(); i++)
    {
        distribution_A.push_back(0);
    }
    distribution_A[included]=1;
    return distribution_A;
}


//This function creates the vector of stock-distribution of portfolio B
vector<double> SharpeAgent::DistributionB(int excluded, vector<double> dist_portfolio)
{
    vector<double> distribution_B;
    double excluded_weight = dist_portfolio[excluded];
    for(int k=0; k<(int) _portfolio.size() ; k++)
    {
        if (k!=excluded)
        {
            distribution_B.push_back(dist_portfolio[k]/(1-excluded_weight));
        }
        else
        {
            distribution_B.push_back(0);
        }
    }
    return distribution_B;
}

//This function return the total dollar amount of portfolio B
double SharpeAgent::ValueB(vector<double> dist_B, vector<Stock> stocks)
{
        double valueB=0;
        for(int i=0; i<(int) _portfolio.size() ; i++)
        {

            Stock stock = stocks[i];
            valueB+=(dist_B[i])*(stock.GetPrice());

        }
        return valueB;
}

//This function defines the whole sharpeagent's strategy
void SharpeAgent::Do(int time, vector<Stock> stocks,vector<Option*> options, Treasure* tres, vector<Company*> companies, vector<Stat*> stats)
{
    QTime qtime = QTime::currentTime();
    qsrand((uint)qtime.msec()+_id);

    this->EraseUsedOrders();
    if (_period>time)
    {


        int n = stocks.size();
        EraseAllOrders();

        //creating a portfolio composed of all possible stocks with equal dollar amount invested for each. 90% of total cash is invested in the portfolio
        //when the agent's portfolio is complete : the agent remains idle until period >= time
        for(int i=0; i<n ; i++)
        {

              double value_to_buy = _cash*0.05/n;
              double price = stocks[i].GetBuyPrice();
              int number_to_buy=floor(value_to_buy/price);
              MakeAnOrder(time, i, true, number_to_buy, convert_price(price));

        }
    }

    else
    {
        //cout << "je suis un agent Sharpe (actif) !" << "\n";
        int n = stocks.size(); // au lieu de _portfolio.size() plutot ?

    // Obtaining the stat object, the yields vector and the covariance matrix which all refer to the proper period parameter
        Stat* ref_stat = GetStat(stats,_period);
        vector<double> yields = ref_stat->GetYields();
        vector< vector<double> > covar = ref_stat->GetCovar();

    //Portfolio distribution
        vector<double> dist_port=DistributionPortfolio();

    //Yield/STD of portfolio A (composed of only the stock "stock")
        int stock = qrand()%n;	//Drawing a stock at random
        double RA=yields[stock];
        double sigmaA=covar[stock][stock];

    //Yield/STD of portfolio B (composed of the entire agent's portfolio except the stock "stock")
        vector<double> distribution_B=DistributionB(stock,dist_port); //distribution of portfolio B
        //calculation of RB : weighted mean of the yields : product between vectors distribution_B and yields
        double RB = Calculvect(distribution_B,yields);
        //calculation of sigmaB : using the matrix of variance-covariance and operating the following product : distribution_B*covar*distribution_B
        double sigmaB=Calculmat(distribution_B,covar,distribution_B);

    //calculation of covAB : the covariance between the portfolios A and B
        vector<double> distribution_A=DistributionA(stock);
        double covAB=Calculmat(distribution_A,covar,distribution_B);


    //Getting the weight of the portfolio as it is now
        double valueB = ValueB(distribution_B,stocks);
        double weightA = dist_port[stock];
        double valueA = stocks[stock].GetPrice();

    //Maximizing the Sharpe ratio
        double argmax= this -> Maxisharp(weightA, RA, RB, sigmaA, sigmaB, covAB);

    //Calculation of the number of stock shares "stock" to buy/sell
        double number_shares_B = 0;
        for (int i = 0; i<(int) _portfolio.size(); i++)
        {
            if (i!= stock)
            {
                number_shares_B += _portfolio[i]->GetNumber();
            }
        }
        int numberA = _portfolio[stock]->GetNumber();
        double new_numberA=argmax*number_shares_B/(1-argmax);

        int number_to_buy = floor(absval(new_numberA - numberA));
        bool buy = (new_numberA > numberA);
        double price;
        if (buy)
        {
            price = stocks[stock].GetBuyPrice()*(1+_margin);
        }
        else
        {
            price = stocks[stock].GetSellPrice()*(1-_margin);
        }

        this -> NewOrder(time, stock, buy,number_to_buy,convert_price(price));
    }
}



//This function returns the vectorial product : a*m*b
double SharpeAgent::Calculmat(vector<double> a,vector< vector<double> > m,vector<double> b)
{
            vector<double> temporaire;
            int n = b.size();
            for(int i=0; i<n ; i++) {
                double a=0;

                    for(int j=0; j<n ; j++) {
                    a+=b[i]*m [i][j];
                                }
                temporaire.push_back(a);
            }

            double resultat=0;

            for(int i=0; i<n ; i++) {
                  resultat+=a[i]*temporaire[i];
            }
            return resultat;
}

//This function returns the vectorial product : a*b
double SharpeAgent::Calculvect(vector<double> a,vector<double> b)
{
    int n = b.size();
            double temporaire=0;
            for(int i=0; i<n ; i++) {
                  temporaire+=a[i]*b[i];
            }
            return temporaire;
}


//This function returns the real (distribution between the two portfolios) which maximizes the Sharpe Ratio of the Agent
double SharpeAgent::Maxisharp(double initial_weight, double RA, double RB, double sigmaA, double sigmaB,double covAB)
{
            double max_sharpe;
            double argmax=initial_weight;

            //Calculation of the Sharpe Ration for w=initial_weight
            double w=initial_weight;
            double RP=w*RA+(1-w)*RB;
            double sigmaP=sqrt(w*w*sigmaA*sigmaA+(1-w)*(1-w)*sigmaB*sigmaB+2*covAB*w*(1-w));
            max_sharpe=(RP-_r_target)*exp(-_alpha*log(sigmaP));


            for(int i=0; i<=50 ; i++)
            {
                double w=initial_weight*(1+((i - 25)/100.));

                double sharpe=0; //temporary Sharpe ratio for this w only
                double RP=w*RA+(1-w)*RB;
                double sigmaP=sqrt(w*w*sigmaA*sigmaA+(1-w)*(1-w)*sigmaB*sigmaB+2*covAB*w*(1-w));
                sharpe=(RP-_r_target)*exp(-_alpha*log(sigmaP));

                if (sharpe>max_sharpe)
                {
                    argmax=w;
                    max_sharpe=sharpe;
                }
            }
             return argmax;
}



SharpeAgent::~SharpeAgent(void)
{
}
