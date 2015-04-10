#ifndef  __CLASS_MY_CLASS_FRIEND_HH__
#define  __CLASS_MY_CLASS_FRIEND_HH__

#include <iostream>
#include <string>

class CPoint
{
public:
	CPoint(float a= 0.0f, float b=0.0f):x(a),y(b)
	{

	}
private:
	float x;
	float y;
public:
	friend float distance(CPoint& left, CPoint& right);//友元函数
};
//友元函数
float distance(CPoint& left, CPoint& right)
{
	return (left.x - right.x);
	//return (((left.x - right.x)^2 + (left.y - right.y)^2)^0.5);
}

#endif //__CLASS_MY_CLASS_FRIEND_HH__