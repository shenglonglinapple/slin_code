#ifndef __CLASS_BAR_HH__
#define __CLASS_BAR_HH__

#include <set>

enum BarType 
{
    FIVE_SECOND = 5,
	TEN_SECOND = 10,
	FIFTEEN_SECEOND = 15,
	THIRTY_SECOND = 30,
	MINUTE = 60,
	FIVE_MINUTE = 5 * MINUTE,
	FIFTEEN_MINUTE = 15 * MINUTE,
	THIRTY_MINUTE = 30 * MINUTE,
	ONE_HOUR = 60 * MINUTE,
	DAY = ONE_HOUR * 24,
	WEEK = DAY * 7,
	MONTH = DAY * 30,
	YEAR = DAY * 7
};

class  Bar
{
public:
	enum Element
	{
		OPEN,
		HIGH,
		LOW,
		CLOSE,
		VOLUME,
	};
public:
	Bar();
	~Bar();

	/// Lowest price within the time span
	double low;

	/// Highest price within the time span
	double high;

	/// First traded price within the time span
	double open;

	/// Last traded price within the time span
	double close;

	/// Total volume within the time span
	double volume;

	/// Time of the bar
	unsigned int timestamp;


    bool operator<(const Bar &rhs) 
    {
        return timestamp < rhs.timestamp;
    }
};


#endif//__CLASS_BAR_HH__



