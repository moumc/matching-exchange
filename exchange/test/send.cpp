#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <nanomsg/nn.h>
#include <nanomsg/pipeline.h>
#include <signal.h>

#include "../order.h"

#include <time.h>
#include <stdlib.h>
#include <sys/timeb.h>

#define NODE0 "node0"
#define NODE1 "node1"

#define URL "ipc://../ex_match_receiver.ipc"

long g_sendCount = 0;

void
fatal(const char *func)
{
	fprintf(stderr, "%s: %s\n", func, nn_strerror(nn_errno()));
	exit(1);
}

int init(int& sock, const char* url)
{
	int rv;
	if ((sock = nn_socket(AF_SP, NN_PUSH)) < 0) {
			fatal("nn_socket");
	}
	if ((rv = nn_connect(sock, url)) < 0) {
			fatal("nn_connect");
	}
	return 0;
}

int
sendMsg(const int& sock, const char *msg)
{
	int sz_msg = strlen(msg) + 1; // '\0' too
	int bytes;

	printf("SENDING \"%s\"\n", msg);
	if ((bytes = nn_send(sock, msg, sz_msg, 0)) < 0) {
		fatal("nn_send");
	}

	return 0;
}

long MakeRand(long min, long max) {
	struct timeb stb;
	ftime(&stb);

	srand((unsigned)stb.millitm);
	long r = (rand() % (max - min))+ min + 1;

	return r;
}

void test1(const int& sock) {
			//买
	sendMsg(sock, "{\"id\":1,\"userid\":6,\"symbol\":\"ltc_btf\",\"flag\":1,\"price\":100,\"amount\":10,\"over_amount\":10,\"status\":0,\"created\":\"2018-05-02T19:49:51+08:00\",\"updated\":\"2018-05-02T19:49:51+08:00\",\"unixnano\":1528363177204824000}");
	sendMsg(sock, "{\"id\":2,\"userid\":6,\"symbol\":\"ltc_btf\",\"flag\":1,\"price\":101,\"amount\":11,\"over_amount\":11,\"status\":0,\"created\":\"2018-05-02T19:49:51+08:00\",\"updated\":\"2018-05-02T19:49:51+08:00\",\"unixnano\":1528363177304824000}");
	sendMsg(sock, "{\"id\":3,\"userid\":6,\"symbol\":\"ltc_btf\",\"flag\":1,\"price\":102,\"amount\":12,\"over_amount\":12,\"status\":0,\"created\":\"2018-05-02T19:49:51+08:00\",\"updated\":\"2018-05-02T19:49:51+08:00\",\"unixnano\":1528363177404824000}");
	sendMsg(sock, "{\"id\":4,\"userid\":6,\"symbol\":\"ltc_btf\",\"flag\":1,\"price\":103,\"amount\":13,\"over_amount\":13,\"status\":0,\"created\":\"2018-05-02T19:49:51+08:00\",\"updated\":\"2018-05-02T19:49:51+08:00\",\"unixnano\":1528363177504824000}");

	//卖
	sendMsg(sock, "{\"id\":5,\"userid\":6,\"symbol\":\"ltc_btf\",\"flag\":2,\"price\":100,\"amount\":5,\"over_amount\":5,\"status\":0,\"created\":\"2018-05-02T19:49:51+08:00\",\"updated\":\"2018-05-02T19:49:51+08:00\",\"unixnano\":1528363177604824000}");
	sendMsg(sock, "{\"id\":6,\"userid\":6,\"symbol\":\"ltc_btf\",\"flag\":2,\"price\":101,\"amount\":6,\"over_amount\":6,\"status\":0,\"created\":\"2018-05-02T19:49:51+08:00\",\"updated\":\"2018-05-02T19:49:51+08:00\",\"unixnano\":1528363177704824000}");
	sendMsg(sock, "{\"id\":7,\"userid\":6,\"symbol\":\"ltc_btf\",\"flag\":2,\"price\":102,\"amount\":7,\"over_amount\":7,\"status\":0,\"created\":\"2018-05-02T19:49:51+08:00\",\"updated\":\"2018-05-02T19:49:51+08:00\",\"unixnano\":1528363177804824000}");
	sendMsg(sock, "{\"id\":8,\"userid\":6,\"symbol\":\"ltc_btf\",\"flag\":2,\"price\":103,\"amount\":8,\"over_amount\":8,\"status\":0,\"created\":\"2018-05-02T19:49:51+08:00\",\"updated\":\"2018-05-02T19:49:51+08:00\",\"unixnano\":1528363177904824000}");
}

void test2(const int& sock) {
	
	COrder order;
	
	static long id = 0;
	struct timeb stb;

	order.SetSymbol("ltc_btf");
	order.SetCreated("");
	order.SetUpdated("");
	order.SetStatus(0);
	
	for (;;) {
		order.SetId(++id);
		order.SetUserId(MakeRand(10000, 11000));
		order.SetFlag(MakeRand(0, 4));
		order.SetPrice(MakeRand(1000, 1100));
		long amount = MakeRand(1, 100);
		order.SetAmount(amount);
		order.SetOverAmount(amount);
		
		order.SetUnixNano(clock());
	
		sendMsg(sock, order.ToString().c_str());
		
		//usleep(1000);
		g_sendCount = id;
	}
	
}

void handler(int sig) {
	printf("SENDING count  %ld \n", g_sendCount);
}

int
main(const int argc, const char **argv)
{
	int sock;
	
	init(sock, (const char*)URL);

	signal(SIGTERM, handler);
	signal(SIGINT,	handler);
	//test1(sock);
	test2(sock);
	
	
	sleep(1);
	nn_shutdown(sock, 0);
	
	return 0;
}