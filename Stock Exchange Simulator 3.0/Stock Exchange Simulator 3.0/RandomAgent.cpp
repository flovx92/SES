#include "RandomAgent.h"
#include <random>

RandomAgent::RandomAgent(int id, int bank, double cash, vector<double> stock_prices, double price):Agent(id, bank, cash, stock_prices)
{
	_price = price;
}

void RandomAgent::Do(int time, vector<Stock> stocks, vector<Option*> options)
{
	random_device rd;
	mt19937 rand(rd());

	cout << "je suis un agent random !" << "\n";
	int n = _portfolio.size();
	int stock = rand()%n;
	bool buy = (rand()%10)>=5;
	this -> MakeAnOrder(time, stock, buy, 1, _price);
	cout << "Order: " << stock << " and " << buy << "\n";


}



RandomAgent::~RandomAgent(void)
{
}
