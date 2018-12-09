#pragma once

#include <thread>
#include <memory>
#include <vector>

#include "lib/logging.hpp"
#include "commands/executer.hpp"
#include "networking/comm.hpp"

class IHARR {

public:
	IHARR();
	~IHARR();

	void run();

private:

	void spawnRunner(Comm* comm);
	void runner(Comm* comm);

	std::vector<std::thread> _runners_threads;

	Executer _exc;

	spdlogger _log{NewLogger("iharr")};

};