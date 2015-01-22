//
//  General.cpp
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 28/12/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#include "General.h"
#include <random>
//general functions!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

double Normal_generator(double mu,double sigma)//Box-Muller method
{
	random_device rd;
	mt19937 rand(rd());
    double U1 = rand()%1000;
    double U2 = rand()%1000;
    double N = sqrt(-2*log(U1/1000))*cos(2*3.14159*U2/1000);
    return mu+sigma*N;
}

double max(double a, double b)
{
    if (a>b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

double convert_price(double p)
{
    int a= (int) (p*100);
    double res =  (((double) a)/100.);
    return res;
}

//end general functions!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


// General function !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

double absval(double num)
{
    if (num >= 0)
    {
        return num;
    }
    else
    {
        return (-num);
    }
}

// end general function !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

