#pragma once

#ifndef __Stock_Exchange_Simulator__General__
#define __Stock_Exchange_Simulator__General__


#include <math.h>
#include <iostream>
#include <vector>


using namespace std;

class Database;

Database* Initialisation(int select=0);
void NextDay(Database* pdata);


double Normal_generator(double mu,double sigma);//Box-Muller method
double max(double a, double b);
double convert_price(double p);
double absval(double);

#endif /* defined(__Stock_Exchange_Simulator__General__) */
