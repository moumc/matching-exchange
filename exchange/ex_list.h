#ifndef __EX_LIST__
#define __EX_LIST__

#include <list>
#include <memory>
#include <map>

#include "order.h"
#include "common.h"

using namespace std;

class CStkMatchList
{
public:
	typedef list<shared_ptr<COrder> > order_list_t;
	
	struct MatchList
	{
		order_list_t lBuyList;
		order_list_t lSellList;
	};

	CStkMatchList();
	CStkMatchList(const string& code);
	~CStkMatchList();

	int InsertOrder(shared_ptr<COrder> order);
//	DelOrder();
	COrder* GetOrder(const int& flag);
	bool RemoveOrder(const COrder& order);
	void RemoveAll();
//	Identify();

	void InitList(const string& code);
	void ShowList();

private:
	MatchList m_list;
	string m_strCode;
	
//	记录每个节点指针，用于直接删除
	map<long, order_list_t::iterator> m_mapCodes;
};

#endif
