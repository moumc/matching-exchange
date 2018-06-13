#ifndef __MARKET_H__
#define __MARKET_H__

#include <string>

using namespace std;

class CMarket
{
public:
	CMarket(const long& id, const string& symbol, const string& market, const long& fee);
	CMarket();
	~CMarket();
	
	string GetMarket() {
		return m_strMarket;
	}
	
//private:

	long m_nId;
	string m_strSymbol;
	string m_strMarket;
	long m_nFee;
};


#endif