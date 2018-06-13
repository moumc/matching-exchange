#include "databus.h"

#include <nanomsg/nn.h>
#include <nanomsg/pipeline.h>
#include <glog/logging.h>

using namespace std;

CReceiver::CReceiver(const string& url, CExMatch *match) {
	m_sUrl = url;
	m_bRunning = true;
	m_pExMatch = match;
}

CReceiver::~CReceiver() {
	nn_shutdown(m_nSock, 0);
}

bool CReceiver::SetupThreadReceiver() {
	m_threadReceiver = thread(&CReceiver::RunThreadReceiver, this);
	return true;
}

void CReceiver::RunThreadReceiver() {
	LOG(INFO) << "Listening order messages...";

	int rv;
	
	if ((m_nSock = nn_socket(AF_SP, NN_PULL)) < 0) {
			LOG(FATAL) << "nn_socket";
	}
	if ((rv = nn_bind(m_nSock, m_sUrl.c_str())) < 0) {
		LOG(FATAL) << "nn_bind";
	}
	while (m_bRunning) {
		char *buf = NULL;
		int bytes;
		if ((bytes = nn_recv(m_nSock, &buf, NN_MSG, 0)) < 0) {
			LOG(FATAL) << "nn_recv";
		}
		string s(buf) ;
		COrder order(s);

		if (order.CheckOrder()) {
			LOG(INFO) << "receive a order messages, order id [ " << order.m_nId << " ]";
			m_pExMatch->m_pMatchHandle->Match(order.m_strSymbol, order);

		}

		nn_freemsg(buf);
	}
}

void CReceiver::Stop() {
	LOG(INFO) << "stop ipc server loop";

	nn_shutdown(m_nSock, 0);

	if (!m_bRunning) {
	  return;
	}
	m_bRunning = false;

	LOG(INFO) << "stop receiver thread...";
}

void CReceiver::Join() {
	m_threadReceiver.join();
}


CSender::CSender(const string& url) {
	m_sUrl = url;
}

CSender::~CSender() {
	nn_shutdown(m_nSock, 0);
}

bool CSender::Init() {
	int rv;
	if ((m_nSock = nn_socket(AF_SP, NN_PUSH)) < 0) {
			return false;
	}
	if ((rv = nn_connect(m_nSock, m_sUrl.c_str())) < 0) {
			return false;
	}
	return true;
}

bool CSender::SendMsg(const string& msg) {
	int sz_msg = msg.length() + 1; 
	int bytes;

	if ((bytes = nn_send(m_nSock, msg.c_str(), sz_msg, 0)) < 0) {
		return false;
	}

	return true;

}



