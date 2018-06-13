#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <nanomsg/nn.h>
#include <nanomsg/pipeline.h>

#include <glog/logging.h>
#include <time.h>

#define URL "ipc://../ex_match_sender.ipc"

#include <string>
#include <thread>
#include <unistd.h>

using namespace std;	

long g_nCount = 0;

void
fatal(const char *func)
{
	fprintf(stderr, "%s: %s\n", func, nn_strerror(nn_errno()));
	exit(1);
}

void Init(const char *exe) {
	string optLogDir = "./log";
	// Initialize Google's logging library.
	google::InitGoogleLogging(exe);
	FLAGS_log_dir		  = optLogDir;
	// Log messages at a level >= this flag are automatically sent to
	// stderr in addition to log files.
	FLAGS_stderrthreshold = 3;	  // 3: FATAL
	FLAGS_max_log_size	  = 100;  // max log file size 100 MB
	FLAGS_logbuflevel	  = -1;   // don't buffer logs
	FLAGS_stop_logging_if_full_disk = true;
}

int Receive() {
	
	int sock;
	int rv;
	long count = 0;
	
	if ((sock = nn_socket(AF_SP, NN_PULL)) < 0) {
		fatal("nn_socket");
	}
	if ((rv = nn_bind(sock, URL)) < 0) {
		fatal("nn_bind");
	}
	
	for (;;) {
		char *buf = NULL;
		int bytes;
		if ((bytes = nn_recv(sock, &buf, NN_MSG, 0)) < 0) {
				fatal("nn_recv");
		}

		LOG(INFO) << buf;
		count++;
		nn_freemsg(buf);
	}
	
	sleep(1);
	
	LOG(INFO) << "Total orders received " << count ;
	nn_shutdown(sock, 0);
	return 0;
}
//
// %y	Year, last two digits (00-99)	01
// %Y	Year	2001
// %m	Month as a decimal number (01-12)	08
// %d	Day of the month, zero-padded (01-31)	23
// %H	Hour in 24h format (00-23)	14
// %I	Hour in 12h format (01-12)	02
// %M	Minute (00-59)	55
// %S	Second (00-61)	02
//
// %D	Short MM/DD/YY date, equivalent to %m/%d/%y	08/23/01
// %F	Short YYYY-MM-DD date, equivalent to %Y-%m-%d	2001-08-23
// %T	ISO 8601 time format (HH:MM:SS), equivalent to %H:%M:%S	14:55:02
//
//string date(const char *format, const time_t timestamp) {
//  char buffer[80] = {0};
//  struct tm tm;
//  time_t ts = timestamp;
//  gmtime_r(&ts, &tm);
//  strftime(buffer, sizeof(buffer), format, &tm);
//  return string(buffer);
//}

//void Clock() {
//	
//	time_t t = time(nullptr);
//	
//	for (;;) {
//		
//		LOG(INFO) << " ================== " << date("%F %T", t) << " ================== ";
//		usleep(500);
//	}
//}

int
main(const int argc, const char **argv)
{
	Init(argv[0]);
	
	Receive();
	
	//thread t(Clock, nullptr);
	
	//t.join();

	return 0;
}

//    clock_t start = clock();  
//    // Place your codes here...  
//    // 指定运行次数  
//    clock_t ends = clock();  
//  
//    cout <<"Running Time : "<<(double)(ends - start)/ CLOCKS_PER_SEC << endl;  // 每秒时钟的跳数  
//  cout <<"Running Time : "<<ends - start <<" ms"<<endl;  // 毫秒 ms  
  