#include "Bar.h"

Bar::Bar()
{

}

Bar::~Bar()
{

}

Bar& Bar::operator=( const Bar& newValue )
{
	low = newValue.low;
	high = newValue.high;
	open = newValue.open;
	close = newValue.close;
	volume = newValue.volume;
	timestamp = newValue.timestamp;
	return *this;
}
