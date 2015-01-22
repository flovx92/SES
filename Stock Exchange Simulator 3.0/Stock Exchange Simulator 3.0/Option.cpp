//
//  Option.cpp
//  Stock Exchange Simulator
//
//  Created by Vassaux Florent on 04/12/2014.
//  Copyright (c) 2014 Vassaux Florent. All rights reserved.
//

#include "Option.h"

Option::Option(int id, int id_seller, int id_stock, int maturity, double strike ,bool is_call,double price)
{
    _id = id;
    _id_seller = id_seller;
    _id_buyer = id_seller;//_id-seller=_id_buyer <=> the option is not already sold and there is no buyer.
    _id_stock = id_stock;
    _maturity = maturity;
    _strike = strike;
    _is_call = is_call;
    _number_of_stocks = 10;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    _price = price;
    _offer = price;
    _exercice = false;
    
}

int Option::GetId()
{
    return _id;
}
int Option::GetIdSeller()
{
    return _id_seller;
}
int Option::GetIdBuyer()
{
    return _id_buyer;
}
int Option::GetMaturity()
{
    return _maturity;
}
int Option::GetIdStock()
{
    return _id_stock;
}
double Option::GetStrike()
{
    return _strike;
}
bool Option::GetIsCall()
{
    return _is_call;
}
int Option::GetNumberOfStocks()
{
    return _number_of_stocks;
}
double Option::GetPrice()
{
    return _price;
}
void Option::SetPrice(double price)
{
    _price = price;
}
double Option::GetOffer()
{
    return _offer;
}
void Option::NewBuyer(int id, double offer)
{
    _id_buyer = id;
    _offer = offer;
}
bool Option::GetExercice()
{
    return _exercice;
}
void Option::Exercice()
{
    _exercice = true;
}
