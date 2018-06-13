#ifndef __COIN_MATCH_SERVER_H__
#define __COIN_MATCH_SERVER_H__

#include <string>
using namespace std;

#include "databus.h"

class CSender;

class CCoinMatchServer {
public:
	CCoinMatchServer();
	~CCoinMatchServer();
	int DealMatch(CStkMatchList *pList, COrder& order, CSender *sender);
private:

};

#endif
