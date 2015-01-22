#pragma once
//
//  General.h
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 28/12/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#ifndef __Stock_Exchange_Simulator__General__
#define __Stock_Exchange_Simulator__General__

#include <random>
#include <math.h>
#include <iostream>
#include <vector>


using namespace std;



double Normal_generator(double mu,double sigma);//Box-Muller method
double max(double a, double b);
double convert_price(double p);
double absval(double);

#endif /* defined(__Stock_Exchange_Simulator__General__) */
