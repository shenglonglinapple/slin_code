#ifndef __CLASS_SAMPLE_CLASS_HH__
#define __CLASS_SAMPLE_CLASS_HH__



class CSampleClassImp;

class CSampleClass
{
public:
	CSampleClass();
	virtual ~CSampleClass();
public:
	int testFun(int nParamOne);
private:
	CSampleClassImp* m_pImp;
};


#endif//__CLASS_SAMPLE_CLASS_HH__


