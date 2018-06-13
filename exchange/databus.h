#ifndef __DATA_BUS_H__
#define __DATA_BUS_H__

#include <glog/logging.h>

#include "order.h"
#include "common.h"
#include "ex_match.h"

class CExMatch;

class CReceiver
{
public:
	bool SetupThreadReceiver();
	void RunThreadReceiver();
	void Stop();
	void Join();
	
	CReceiver(const string& url, CExMatch *match);
	~CReceiver();
private:
	atomic<bool> m_bRunning;
//  	mutex m_lock;

	string m_sUrl;
	int m_nSock;

	thread m_threadReceiver;
	CExMatch *m_pExMatch;
};

class CSender
{
public:
	CSender(const string& url);
	~CSender();

	bool Init();
	bool SendMsg(const string& msg);
private:
	string m_sUrl;
	int m_nSock;
};

#endif