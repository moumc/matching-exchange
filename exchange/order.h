#ifndef __ORDER_H__
#define __ORDER_H__

#include <string>

using namespace std;

class COrder
{
public:
	COrder();
	COrder(const string& order);
	~COrder();

	int SetOrder(const string& order);
	string ToString();
	bool CheckOrder();

	void SetId(const long& id);
	void SetUserId(const long& userId);
	void SetSymbol(const string& symbol);
	void SetFlag(const long& flag);
	void SetPrice(const long& price);
	void SetAmount(const long& amount);
	void SetOverAmount(const long& overAmount);
	void SetStatus(const int& status);
	void SetCreated(const string& created);
	void SetUpdated(const string& updated);
	void SetUnixNano(const long& unixNano);
	
	
//private:
	long m_nId;
	long m_nUserId;
	string m_strSymbol;
	int m_nFlag;
	long m_nPrice;
	long m_nAmount;
	long m_nOverAmount;
	int m_nStatus;
	string m_strCreated;
	string m_strUpdated;
	long m_nUnixNano;
};

class CPushData 
{
public:
	CPushData();
	CPushData(const string& symbol, long fromUserid, long fromOrderid, long toOrderid, long toUserid, 
		long dealAmount, long dealPrice, long orderPrice, int flag, const string& compare);
	~CPushData();

	string ToString();

	string m_strSymbol;
	long m_nFromUserId;
	long m_nFromOrderId;
	long m_nToOrderId;
	long m_nToUserId;
	long m_nDealAmount;
	long m_nDealPrice;
	long m_nOrderPrice;
	int m_nFlag;
	string m_strCompare;

};

#endif
