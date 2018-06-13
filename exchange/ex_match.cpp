#include "ex_match.h"

#include <glog/logging.h>

CExMatch::CExMatch() {
	m_pReceiver = nullptr;
	m_pSender = nullptr;
	
	m_sRecUrl = "ipc://ex_match_receiver.ipc";
	m_sSendUrl = "ipc://ex_match_sender.ipc";
	m_bRunning = true;
}

CExMatch::~CExMatch() {
	if (m_pReceiver) {
		delete m_pReceiver;
	}

	if (m_pSender) {
		delete m_pSender;
	}

	if (m_pMatchHandle) {
		delete m_pMatchHandle;
	}
}

void CExMatch::Init() {
	m_pSender = new CSender(m_sSendUrl);
	assert(m_pSender);
	if (!m_pSender->Init()) {
	  return ;
	}

	m_pMatchHandle = new CMatchHandle();
	assert(m_pMatchHandle);

	m_vecMatchMarkets.push_back("ltc_btf");
	m_matchPool.InitMarket(m_vecMatchMarkets);

	m_vecSymbols.push_back(CMarket(1, "ltc_btf", "btf", 10));	//从配置文件读取
	m_matchPool.AppendSymbol(m_vecSymbols);

	m_pMatchHandle->Init(&m_matchPool, m_pSender);

	LOG(INFO) << "CExMatch init finish";
}

bool CExMatch::Run() {
	LOG(INFO) << "CExMatch Run ... ";

	// run Receiver thread
	m_pReceiver = new CReceiver(m_sRecUrl, this);
	assert(m_pReceiver);
	if (!m_pReceiver->SetupThreadReceiver()) {
	  return false;
	}

	while(m_bRunning) {
		sleep(5);
		LOG(INFO) << "sleep 5 second ... ";

		string symbol = "ltc_btf";
//		m_pMatchHandle->ShowOrder(symbol);
	}
	LOG(INFO) << "CExMatch Run ... End  11";

	m_pReceiver->Join();
	LOG(INFO) << "CExMatch Run ... End";
	return true;
}

void CExMatch::DoTest() {
	
	string symbol = "ltc_btf";
//	string s = "{\"id\":4,\"userid\":6,\"symbol\":\"ltc_btf\",\"flag\":3,\"price\":100,\"amount\":10,\"over_amount\":10,\"status\":0,\"created\":\"2018-05-02T19:49:51+08:00\",\"updated\":\"2018-05-02T19:49:51+08:00\",\"unixnano\":1525261791204824000}";

	vector<string> orders;
		//买
	orders.push_back("{\"id\":1,\"userid\":6,\"symbol\":\"ltc_btf\",\"flag\":1,\"price\":100,\"amount\":10,\"over_amount\":10,\"status\":0,\"created\":\"2018-05-02T19:49:51+08:00\",\"updated\":\"2018-05-02T19:49:51+08:00\",\"unixnano\":1528363177204824000}");
	orders.push_back("{\"id\":2,\"userid\":6,\"symbol\":\"ltc_btf\",\"flag\":1,\"price\":100,\"amount\":11,\"over_amount\":11,\"status\":0,\"created\":\"2018-05-02T19:49:51+08:00\",\"updated\":\"2018-05-02T19:49:51+08:00\",\"unixnano\":1528363177304824000}");
	orders.push_back("{\"id\":3,\"userid\":6,\"symbol\":\"ltc_btf\",\"flag\":1,\"price\":100,\"amount\":12,\"over_amount\":12,\"status\":0,\"created\":\"2018-05-02T19:49:51+08:00\",\"updated\":\"2018-05-02T19:49:51+08:00\",\"unixnano\":1528363177404824000}");
	orders.push_back("{\"id\":4,\"userid\":6,\"symbol\":\"ltc_btf\",\"flag\":1,\"price\":100,\"amount\":13,\"over_amount\":13,\"status\":0,\"created\":\"2018-05-02T19:49:51+08:00\",\"updated\":\"2018-05-02T19:49:51+08:00\",\"unixnano\":1528363177504824000}");

		//卖
	orders.push_back("{\"id\":5,\"userid\":6,\"symbol\":\"ltc_btf\",\"flag\":2,\"price\":100,\"amount\":15,\"over_amount\":15,\"status\":0,\"created\":\"2018-05-02T19:49:51+08:00\",\"updated\":\"2018-05-02T19:49:51+08:00\",\"unixnano\":1528363177604824000}");
//	orders.push_back("{\"id\":6,\"userid\":6,\"symbol\":\"ltc_btf\",\"flag\":2,\"price\":101,\"amount\":6,\"over_amount\":6,\"status\":0,\"created\":\"2018-05-02T19:49:51+08:00\",\"updated\":\"2018-05-02T19:49:51+08:00\",\"unixnano\":1528363177704824000}");
//	orders.push_back("{\"id\":7,\"userid\":6,\"symbol\":\"ltc_btf\",\"flag\":2,\"price\":102,\"amount\":7,\"over_amount\":7,\"status\":0,\"created\":\"2018-05-02T19:49:51+08:00\",\"updated\":\"2018-05-02T19:49:51+08:00\",\"unixnano\":1528363177804824000}");
//	orders.push_back("{\"id\":8,\"userid\":6,\"symbol\":\"ltc_btf\",\"flag\":2,\"price\":103,\"amount\":8,\"over_amount\":8,\"status\":0,\"created\":\"2018-05-02T19:49:51+08:00\",\"updated\":\"2018-05-02T19:49:51+08:00\",\"unixnano\":1528363177904824000}");

	for (auto i : orders) {
		COrder order(i);
	
		cout << "match before" << endl;
		m_pMatchHandle->ShowOrder(symbol);

		m_pMatchHandle->Match(symbol, order);

		cout << "after match" << endl;
		m_pMatchHandle->ShowOrder(symbol);
	}
	
}

void CExMatch::Stop() {
	string symbol = "ltc_btf";
	m_pMatchHandle->ShowOrder(symbol);

	if (!m_bRunning)
	  return;
	
	m_bRunning = false;

	m_pReceiver->Stop();
}

