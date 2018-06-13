#include "matchpool.h"

#include <glog/logging.h>

CMatchPool::CMatchPool()
{
}

CMatchPool::~CMatchPool()
{
}


void CMatchPool::InitMarket(const vector<string>& vecMarket) {
	for (const auto& i : vecMarket) {
		map<string, CStkMatchList> mapTransPair;
		m_vecMatchPool.insert(pair<string, map<string, CStkMatchList> >(i, mapTransPair));
	}
	LOG(INFO) << "Init " << m_vecMatchPool.size() << " market";
}

void CMatchPool::AppendSymbol(const vector<CMarket>& vecSymbol) {

	for (const auto& i : vecSymbol) {
		CStkMatchList matchList(i.m_strSymbol);
		m_mapMarketQuoteMap[i.m_strSymbol] = i;
		m_vecMatchPool[i.m_strMarket][i.m_strSymbol] = matchList;
	}
	LOG(INFO) << "Append " << vecSymbol.size() << " symbol";
}

CStkMatchList *CMatchPool::GetMatchQueue(const string& symbol) {
	map<string, CMarket>::iterator iter = m_mapMarketQuoteMap.find(symbol);
	if (iter == m_mapMarketQuoteMap.end()) {
		LOG(ERROR) << "There's no symbol";
		return nullptr;
	}

	string market = m_mapMarketQuoteMap[symbol].GetMarket();
	return &m_vecMatchPool[market][symbol];
}


