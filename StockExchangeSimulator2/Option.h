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
    int _maturity;//period between the sale and the maturity
    int _time; //time when the option is sold and the option really starts
    int _id_stock;//on which stock the option apply
    double _strike;
    bool _is_call;
    int _number_of_stocks;//we will fix it at 10
    double _price;//selling price (fixed)
    double _offer;//highest bid
    bool _exercice;//if the option is exerciced
    bool _sold;//indicates if initial money<->option transfer was made
    double _delta; //info for the seller.

public:
    Option(int id, int id_seller, int id_stock, int maturity, double strike ,bool is_call,double price,double delta);
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
    bool GetSold();
    void Sold();
    double GetDelta();
    void SetDelta(double delta);
    int GetTime();
    void SetTime(int time);
};

#endif /* defined(__Stock_Exchange_Simulator__Option__) */
