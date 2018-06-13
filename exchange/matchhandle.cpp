#include "matchhandle.h"

#include <glog/logging.h>
#include <time.h>

#include <iostream>
using namespace std;

CMatchHandle::CMatchHandle() {
	m_pMatchServer = nullptr;
	m_pMatchPool = nullptr;
	m_pSender = nullptr;
	m_nCount = 0;
}

CMatchHandle::~CMatchHandle() {
	if (m_pMatchServer) {
		delete m_pMatchServer;
	}
}

void CMatchHandle::Init(CMatchPool *pMatchPool, CSender *sender) {
	m_pMatchPool = pMatchPool;
	m_pMatchServer = new CCoinMatchServer();
	m_pSender = sender;

	LOG(INFO) << "CMatchHandle Init";
}

int CMatchHandle::Match(const string& symbol, COrder& order) {
	CStkMatchList *pList = m_pMatchPool->GetMatchQueue(symbol);

	if (pList == nullptr) {
		LOG(ERROR) << "There is not MatchList";
		return -1;
	}
	
	m_nCount++;
	m_pMatchServer->DealMatch(pList, order, m_pSender);

	return 0;
}

void CMatchHandle::ShowOrder(const string& symbol) {
	CStkMatchList *pList = m_pMatchPool->GetMatchQueue(symbol);

	if (pList == nullptr) {
		LOG(ERROR) << "There is not MatchList";
		return ;
	}
	pList->ShowList();

	LOG(INFO) << "Total order processing  " << m_nCount ;
}


