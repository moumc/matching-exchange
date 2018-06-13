#include "ex_list.h"
#include <glog/logging.h>

#include <iostream>
using namespace std;

CStkMatchList::CStkMatchList() {
	
}

CStkMatchList::CStkMatchList(const string& code) {
	m_strCode = code;
}

CStkMatchList::~CStkMatchList() {
	m_list.lBuyList.erase(m_list.lBuyList.begin(), m_list.lBuyList.end());
	m_list.lSellList.erase(m_list.lSellList.begin(), m_list.lSellList.end());
}


void CStkMatchList::InitList(const string& code) {
	m_strCode = code;
}

//返回队列第一个订单
COrder* CStkMatchList::GetOrder(const int& flag) {
	LOG(INFO) << "GetOrder start";
	COrder* pOrder = nullptr;
	if (flag == BUY) {
		pOrder = m_list.lBuyList.begin()->get();
	} else if (flag == SELL) {
		pOrder = m_list.lSellList.begin()->get();
	} else {
		return nullptr;
	}

	LOG(INFO) << "GetOrder end";
	return pOrder;
}

int CStkMatchList::InsertOrder(shared_ptr<COrder> order) {
	LOG(INFO) << "InsertOrder start";

	if (m_mapCodes.count(order->m_nId)) {
		LOG(INFO) << "order.id: " << order->m_nId << " is allready exist";
		return 0;
	}

	if (order->m_nFlag == BUY) {	//买 价格从高到低 时间由旧及新
		order_list_t &buyList = m_list.lBuyList;
	
		order_list_t::iterator iter = buyList.begin();

		while (iter != buyList.end()) {
			if (order->m_nPrice > (*iter)->m_nPrice) {
				iter = buyList.insert(iter, order);
				m_mapCodes[order->m_nId] = iter;
				return 0;
				
			} else if (order->m_nPrice == (*iter)->m_nPrice) {
				if (order->m_nUnixNano < (*iter)->m_nUnixNano) {
					iter = buyList.insert(iter, order);
					m_mapCodes[order->m_nId] = iter;
					return 0;
				}
			}
			iter++;
		}

		iter = buyList.insert(buyList.end() , order);  
		m_mapCodes[order->m_nId] = iter;
		
	} else if (order->m_nFlag == SELL) {	//卖  价格从高到低 时间由旧及新
		order_list_t &sellList = m_list.lSellList;
	
		order_list_t::iterator iter = sellList.begin();

		while (iter != sellList.end()) {
			if (order->m_nPrice < (*iter)->m_nPrice) {
				iter = sellList.insert(iter, order);
				m_mapCodes[order->m_nId] = iter;
				return 0;
				
			} else if (order->m_nPrice == (*iter)->m_nPrice) {
				if (order->m_nUnixNano < (*iter)->m_nUnixNano) {
					iter = sellList.insert(iter, order);
					m_mapCodes[order->m_nId] = iter;
					return 0;
				}
			}
			iter++;
		}

		iter = sellList.insert(sellList.end() , order);  
		m_mapCodes[order->m_nId] = iter;

	} else {
		LOG(ERROR) << "order flag error";
		return -1;
	}

	LOG(INFO) << "InsertOrder end";
	return 0;
}

bool CStkMatchList::RemoveOrder(const COrder& order) {
	LOG(INFO) << "RemoveOrder start";

	if (!m_mapCodes.count(order.m_nId)) {
		LOG(INFO) << "order.id " << order.m_nId << " is allready non-existent";
		return true;
	}

	order_list_t::iterator iter = m_mapCodes[order.m_nId];

	if (order.m_nFlag == BUY) {
		m_list.lBuyList.erase(iter);
		m_mapCodes.erase(order.m_nId);
	} else if (order.m_nFlag == SELL) {
		m_list.lSellList.erase(iter);
		m_mapCodes.erase(order.m_nId);
	} else {
		LOG(ERROR) << "order flag error";
		return false;
	}

	LOG(INFO) << "RemoveOrder end";
	return true;
}

void CStkMatchList::RemoveAll() {
	m_list.lBuyList.erase(m_list.lBuyList.begin(), m_list.lBuyList.end());
	m_list.lSellList.erase(m_list.lSellList.begin(), m_list.lSellList.end());
	m_mapCodes.erase(m_mapCodes.begin(), m_mapCodes.end());
}

void CStkMatchList::ShowList() {
	order_list_t &buyList = m_list.lBuyList;
	
	order_list_t::iterator iter = buyList.begin();

	LOG(INFO) << "Start saving data..." ;
	LOG(INFO) << "======================== Buy List =============================" ;
	
	while (iter != buyList.end()) {
		LOG(INFO) << (*iter)->ToString() ;
		iter++;
	}

	order_list_t &sellList = m_list.lSellList;
	
	iter = sellList.begin();

	LOG(INFO) << "======================== Sell List =============================" ;
	
	while (iter != sellList.end()) {
		LOG(INFO) << (*iter)->ToString() ;
		iter++;
	}
	LOG(INFO) << "End saving data......" ;
}

