#include <boost/interprocess/sync/file_lock.hpp>
#include <glog/logging.h>
#include <libconfig.h++>
#include <signal.h>

#include "ex_match.h"
#include "common.h"

using namespace libconfig;

CExMatch *g_exMatch = nullptr;

void handler(int sig) {
  if (g_exMatch) {
    g_exMatch->Stop();
  }
}

void usage() {
  fprintf(stderr, "Usage:\n\tex_match -c \"ex_match.cfg\"\n");
}

int main(int argc, char *argv[])
{
	char *optConf = nullptr;
	int c;

	if (argc <= 1) {
	  usage();
	  return 1;
	}
	while ((c = getopt(argc, argv, "c:h")) != -1) {
	  switch (c) {
	    case 'c':
	      optConf = optarg;
	      break;
	    case 'h': default:
	      usage();
	      exit(0);
	  }
	}

	// Read the file. If there is an error, report it and exit.
	Config cfg;
	try
	{
	  cfg.readFile(optConf);
	} catch(const FileIOException &fioex) {
	  std::cerr << "I/O error while reading file." << std::endl;
	  return(EXIT_FAILURE);
	} catch(const ParseException &pex) {
	  std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
	  << " - " << pex.getError() << std::endl;
	  return(EXIT_FAILURE);
	}

	string optLogDir;
    cfg.lookupValue("log_dir", optLogDir);

	// Initialize Google's logging library.
	google::InitGoogleLogging(argv[0]);
	FLAGS_log_dir		  = optLogDir;
	// Log messages at a level >= this flag are automatically sent to
	// stderr in addition to log files.
	FLAGS_stderrthreshold = 3;	  // 3: FATAL
	FLAGS_max_log_size	  = 100;  // max log file size 100 MB
	FLAGS_logbuflevel	  = -1;   // don't buffer logs
	FLAGS_stop_logging_if_full_disk = true;

	// lock cfg file:
	//	  you can't run more than one process with the same config file
	boost::interprocess::file_lock pidFileLock(optConf);
	if (pidFileLock.try_lock() == false) {
	  LOG(FATAL) << "lock cfg file fail";
	  return(EXIT_FAILURE);
	}

	signal(SIGTERM, handler);
	signal(SIGINT,	handler);

	g_exMatch = new CExMatch();

	g_exMatch->Init();
	g_exMatch->Run();
//	g_exMatch->DoTest();

	delete g_exMatch;

	google::ShutdownGoogleLogging();

	return 0;
}
