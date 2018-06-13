#ifndef __MATCH_POOL_H__
#define __MATCH_POOL_H__

#include "ex_list.h"
#include "market.h"
#include <map>
#include <vector>

using namespace std;

class CMatchPool
{
public:
	typedef map<string, map<string, CStkMatchList> > match_list_t; 

	CMatchPool();
	~CMatchPool();

	void InitMarket(const vector<string>& vecMarket);
	void AppendSymbol(const vector<CMarket>& vecSymbol);
	CStkMatchList *GetMatchQueue(const string& symbol);

	match_list_t *GetMatchPool() {
		return &m_vecMatchPool;
	}
private:
	match_list_t m_vecMatchPool;
	map<string, CMarket> m_mapMarketQuoteMap;	//市场-行情
};

#endif
