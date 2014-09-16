#include <stdlib.h>
#include <math.h>
#include "BarSummary.h"



BarSumary::BarSumary()
{
	instrumentID = 0;
	bars.clear();

	int nBarIndex = 0;
	Bar barData;

	nBarIndex = 0;
	for (int nIndex = 0; nIndex < 100; nIndex++)
	{
		barData.low = 0;
		barData.high = 0;
		barData.open = 0;
		barData.close = 0;
		barData.volume = 0;
		barData.timestamp = 0;

		double tmp1 = ::rand() % 100;
		double tmp2 = ::rand() % 100;

		barData.open = tmp1;
		barData.close = tmp2;

		if (barData.open > barData.close)
		{
			barData.high = barData.open + 0.5;
			barData.low = barData.close - 0.5;
		}
		else
		{
			barData.high = barData.close + 0.5;
			barData.low = barData.open - 0.5;
		}
		

		bars.insert(std::map<int, Bar>::value_type(nBarIndex, barData));
		nBarIndex++;
	}

	
}

BarSumary::~BarSumary()
{

}
