#include "market.h"

CMarket::CMarket() {

}

CMarket::CMarket(const long& id, const string& symbol, const string& market, const long& fee)
	:m_nId(id),m_strSymbol(symbol),m_strMarket(market),m_nFee(fee)
	{}

CMarket::~CMarket() {

}


