#ifndef __DEF_CLASS_BAR_HH__
#define  __DEF_CLASS_BAR_HH__


class Bar
{
public:
	Bar();
	~Bar();
public:
	Bar& operator=(const Bar& newValue);

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

};

#endif// __DEF_CLASS_BAR_HH__



