//
//  Bank.cpp
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 06/10/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#include <QString>
#include "Bank.h"
#include <iostream>
#include <vector>
using namespace std;

Bank::Bank(int id, QString name, double predictions_variance)
{
    _id = id;
    _name = name;
    _predictions_variance = predictions_variance;   
}
