#include <exception>
#include <iostream>

#include "iharr.hpp"

IHARR::IHARR() {
}

IHARR::~IHARR() {
    for(auto&& t : _runners_threads) t.join();
}

void IHARR::run() {
    _log->info("Server initalized");
    while(1) {
        auto comm = new Comm;
        comm->listen("0.0.0.0", 1234);
        spawnRunner(comm);
    }
}

// Private methods

void IHARR::spawnRunner(Comm* comm) {
    _runners_threads.emplace_back(std::thread(&IHARR::runner, this, comm));
}

void IHARR::runner(Comm* comm) {
    try {
        while(1) {
            auto p = comm->readPacket();
            auto pack = _exc.interpretPacket(p);
            comm->writePacket(pack);
        }
    } catch(std::exception& e) {
        // TODO
        _log->error("Error occured: {}", e.what());
    }

    delete comm;
}
