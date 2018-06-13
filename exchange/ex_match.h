#ifndef __EX_MATCH_H__
#define __EX_MATCH_H__

#include "ex_list.h"
#include "matchhandle.h"
#include "market.h"
#include "matchpool.h"
#include "common.h"

class CReceiver;
class CSender;
class CMatchHandle;

class CExMatch
{
public:
	typedef list<shared_ptr<COrder> > order_list_t;

	CExMatch();
	~CExMatch();

	void Init();
	bool Run();
	void DoTest();
	void Stop();

	CMatchHandle *m_pMatchHandle;

private:
	atomic<bool> m_bRunning;
  	mutex m_lock;

	vector<string> m_vecMatchMarkets;	//市场
	CMatchPool m_matchPool;
	vector<CMarket> m_vecSymbols;		//交易对

	CReceiver *m_pReceiver;
	CSender *m_pSender;
	
	string m_sRecUrl;
	string m_sSendUrl;
};

#endif
