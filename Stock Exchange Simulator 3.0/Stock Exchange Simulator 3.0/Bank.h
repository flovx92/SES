#pragma once
//
//  Bank.h
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 06/10/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#ifndef __Stock_Exchange_Simulator__Bank__
#define __Stock_Exchange_Simulator__Bank__


#include "Company.h"
#include "StockExchange.h"
#include "Agent.h"
#include <iostream>
#include <vector>
using namespace std;

class Bank
{
private :
    int _id;
    string _name;
    double _expected_yield;
    double _predictions;
    double _predictions_variance;
    vector<Agent*> _agents;
    
    
public :
    Bank(int id, string name, double predictions_variance);
};

#endif /* defined(__Stock_Exchange_Simulator__Bank__) */
