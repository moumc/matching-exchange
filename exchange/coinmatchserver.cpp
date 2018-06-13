#include "coinmatchserver.h"

#include <stdlib.h> 
#include <glog/logging.h>

#include <iostream>
using namespace std;

CCoinMatchServer::CCoinMatchServer() {
}

CCoinMatchServer::~CCoinMatchServer() {

}


int CCoinMatchServer::DealMatch(CStkMatchList *pList, COrder& fromOrder, CSender *pSender)  {
	LOG(INFO) << "Start processing order[ " << fromOrder.m_nId << " ], flag [ " << fromOrder.m_nFlag << " ]";

	if (pList == nullptr) {
		return -1;
	}

	for (;;) {
		long nBuyPrice = 0, nSellPrice = 0, nOverAmount = 0;
		COrder *toOrder = nullptr;

		if (fromOrder.m_nFlag == BUY) {		// 买	
			toOrder = pList->GetOrder(SELL);

			if (toOrder == nullptr) {
				LOG(INFO) << "List empty, insert order, is a BUY order" ;
				pList->InsertOrder(make_shared<COrder>(fromOrder));
				break;
			}

			nBuyPrice = fromOrder.m_nPrice;
			nSellPrice = toOrder->m_nPrice;
		} else if (fromOrder.m_nFlag == SELL) {		// 卖
			toOrder = pList->GetOrder(BUY);

			if (toOrder == nullptr) {
				LOG(INFO) << "List empty, insert order, is a SELL order" ;
				pList->InsertOrder(make_shared<COrder>(fromOrder));
				break;
			}

			nSellPrice = fromOrder.m_nPrice;
			nBuyPrice = toOrder->m_nPrice;
		} else if (fromOrder.m_nFlag == BUYCANCEL || fromOrder.m_nFlag == SELLCANCEL) {		 // 撤
			LOG(INFO) << "Start cancelling an order[ " << fromOrder.m_nId << " ]" ;

			CPushData pushData(fromOrder.m_strSymbol, fromOrder.m_nUserId, fromOrder.m_nId, 0, 0, fromOrder.m_nOverAmount, fromOrder.m_nPrice, 0, fromOrder.m_nFlag, "");
			if (pSender->SendMsg(pushData.ToString())) {
				pList->RemoveOrder(fromOrder);
			}
			
			break;
		}

		if (nBuyPrice < nSellPrice) {	//委托订单价格小于匹配订单的价格
			LOG(INFO) << "The price of the entrustment order is less than the price of the matching order, insert order, nBuyPrice [ " << nBuyPrice << " ], nSellPrice [ " << nSellPrice << " ]";
			pList->InsertOrder(make_shared<COrder>(fromOrder));
			break;
		}

		CPushData pushData(fromOrder.m_strSymbol, fromOrder.m_nUserId, fromOrder.m_nId, toOrder->m_nId, toOrder->m_nUserId, 0, toOrder->m_nPrice, fromOrder.m_nPrice, fromOrder.m_nFlag, "");

		nOverAmount = fromOrder.m_nOverAmount - toOrder->m_nOverAmount;
		if (nOverAmount > 0) {
			LOG(INFO) << "match amount > 0, Partial transaction, left [ " <<  nOverAmount << " ]";
			LOG(INFO) << "Delete matching order [ " << toOrder->m_nId << " ]";
			pushData.m_strCompare = CompareGt;
			pushData.m_nDealAmount = toOrder->m_nAmount;

			if (pSender->SendMsg(pushData.ToString())) {
				fromOrder.m_nOverAmount = nOverAmount;
				pList->RemoveOrder(*toOrder);
			}
			
		} else if (nOverAmount == 0) {
			LOG(INFO) << "match amount == 0, Transaction finish";
			LOG(INFO) << "Delete matching order [ " << toOrder->m_nId << " ]";

			pushData.m_strCompare = CompareEq;
			pushData.m_nDealAmount = toOrder->m_nAmount;

			if (pSender->SendMsg(pushData.ToString())) {
				fromOrder.m_nOverAmount = nOverAmount;
				pList->RemoveOrder(*toOrder);
				break;
			}
			
		} else {
			LOG(INFO) << "match amount < 0, Partial transaction, left [ " <<  toOrder->m_nOverAmount << " ]";
			toOrder->m_nOverAmount = labs(nOverAmount);

			pushData.m_strCompare = CompareLt;
			pushData.m_nDealAmount = fromOrder.m_nAmount;

			if (pSender->SendMsg(pushData.ToString())) {

				break;
			}
		}
	}

	LOG(INFO) << "End processing order[ " << fromOrder.m_nId << " ]";
	return 0;
}

