#ifndef __MATCH_HANDLE_H__
#define __MATCH_HANDLE_H__

#include "matchpool.h"
#include "coinmatchserver.h"
#include "databus.h"

#include <list>
#include <map>

class CSender;
class CCoinMatchServer;

class CMatchHandle {
public:
	CMatchHandle();
	~CMatchHandle();
	void Init(CMatchPool *pMatchPool, CSender *sender);

	int Match(const string& symbol, COrder& order);

	void ShowOrder(const string& symbol);

	CSender *GetSender() {
		return m_pSender;
	}
	
private:
	CMatchPool *m_pMatchPool;
	CCoinMatchServer *m_pMatchServer;
	CSender *m_pSender;

	long m_nCount;
};

#endif