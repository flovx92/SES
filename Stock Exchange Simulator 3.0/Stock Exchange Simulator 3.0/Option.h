#pragma once
//
//  Option.h
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 04/12/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#ifndef __Stock_Exchange_Simulator__Option__
#define __Stock_Exchange_Simulator__Option__

#include <iostream>
#include <vector>
using namespace std;

class Option
{
private:
    int _id;//for the seller and then for seller and buyer
    int _id_seller;
    int _id_buyer;
    int _maturity;
    int _id_stock;
    double _strike;
    bool _is_call;
    int _number_of_stocks;//we will fix it at 10
    double _price;//selling price (fixed)
    double _offer;//highest bid
    bool _exercice;//if the option is exerciced
public:
    Option(int id, int id_seller, int id_stock, int maturity, double strike ,bool is_call,double price);
    int GetId();
    int GetIdSeller();
    int GetIdBuyer();
    int GetMaturity();
    int GetIdStock();
    double GetStrike();
    bool GetIsCall();
    int GetNumberOfStocks();
    double GetPrice();
    void SetPrice(double price);
    double GetOffer();
    void NewBuyer(int id, double offer);
    bool GetExercice();
    void Exercice();
};

#endif /* defined(__Stock_Exchange_Simulator__Option__) */
