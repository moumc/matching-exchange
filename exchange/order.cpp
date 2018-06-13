#include "order.h"
#include <json/json.h>

using namespace std;

COrder::COrder() {

}

COrder::~COrder() {

}

COrder::COrder(const string& order)
{
	SetOrder(order);
}

int COrder::SetOrder(const string& order) {
	Json::Reader reader;
    Json::Value root;

    if (! reader.parse(order, root) ){
    	return -1;
    }

	m_nId = root["id"].asLargestInt();
	m_nUserId = root["userid"].asLargestInt();
	m_strSymbol = root["symbol"].asString();
	m_nFlag = root["flag"].asInt();
	m_nPrice = root["price"].asLargestInt();
	m_nAmount = root["amount"].asLargestInt();
	m_nOverAmount = root["over_amount"].asLargestInt();
	m_nStatus = root["status"].asInt();
	m_strCreated = root["created"].asString();
	m_strUpdated = root["updated"].asString();
	m_nUnixNano = root["unixnano"].asLargestInt();

	return 0;
}

string COrder::ToString() {
	Json::Value root;

	root["id"] = m_nId; 
	root["userid"] = m_nUserId; 
	root["symbol"] = m_strSymbol; 
	root["flag"] = m_nFlag; 

	root["price"] = m_nPrice; 
	root["amount"] = m_nAmount; 
	root["over_amount"] = m_nOverAmount; 
	root["status"] = m_nStatus; 

	root["created"] = m_strCreated; 
	root["updated"] = m_strUpdated; 
	root["unixnano"] = m_nUnixNano; 

	Json::FastWriter fw;
	string s = fw.write(root);

	return s;
}

bool COrder::CheckOrder() {
	return true;
}

void COrder::SetId(const long& id) {
	m_nId = id;
}
void COrder::SetUserId(const long& userId) {
	m_nUserId = userId;
}
void COrder::SetSymbol(const string& symbol) {
	m_strSymbol = symbol;
}
void COrder::SetFlag(const long& flag) {
	m_nFlag = flag;
}
void COrder::SetPrice(const long& price) {
	m_nPrice = price;
}
void COrder::SetAmount(const long& amount) {
	m_nAmount = amount;
}
void COrder::SetOverAmount(const long& overAmount) {
	m_nOverAmount = overAmount;
}
void COrder::SetStatus(const int& status) {
	m_nStatus = status;
}
void COrder::SetCreated(const string& created) {
	m_strCreated = created;
}
void COrder::SetUpdated(const string& updated) {
	m_strCreated = updated;
}
void COrder::SetUnixNano(const long& unixNano) {
	m_nUnixNano = unixNano;
}




CPushData::CPushData() {

}

CPushData::~CPushData() {

}

CPushData::CPushData(const string& symbol, long fromUserid, long fromOrderid, long toOrderid, long toUserid, 
	long dealAmount, long dealPrice, long orderPrice, int flag, const string& compare) 
	:m_strSymbol(symbol),
	m_nFromUserId(fromUserid),
	m_nFromOrderId(fromOrderid),
	m_nToOrderId(toOrderid),
	m_nToUserId(toUserid),
	m_nDealAmount(dealAmount),
	m_nDealPrice(dealPrice),
	m_nOrderPrice(orderPrice),
	m_nFlag(flag),
	m_strCompare(compare)
{
}
	//	type PushData struct{
		//	Symbol string	`json:"symbol"`
		//	FromUserid int64 `json:"from_userid"`
		//	FromOrderID int64  `json:"from_orderid"`
		//	ToOrderID int64 `json:"to_orderid"`
		//	ToUserid int64 `json:"to_userid"`
		//	DealAmount int64 `json:"deal_amount"` // 成交价
		//	DealPrice int64 `json:"deal_price"` // 成交数量
		//	OrderPrice int64 `json:"order_price"`  // 訂單價格
		//	Flag int32 `json:"flag"`
		//	Compare string `json:"compare"`
	//}

string CPushData::ToString() {
	Json::Value root;

	root["symbol"] = m_strSymbol; 
	root["from_userid"] = m_nFromUserId; 
	root["from_orderid"] = m_nFromOrderId; 
	root["to_orderid"] = m_nToOrderId; 

	root["to_userid"] = m_nToUserId; 
	root["deal_amount"] = m_nDealAmount; 
	root["deal_price"] = m_nDealPrice; 
	root["order_price"] = m_nOrderPrice; 

	root["flag"] = m_nFlag; 
	root["compare"] = m_strCompare; 

	Json::FastWriter fw;
	string s = fw.write(root);

	return s;
}

