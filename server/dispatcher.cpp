#include <iostream>
#include <atomic>
#include <thread>
#include <list>
#include <queue>
#include "common/network.hpp"
#include "common/utils.hpp"

extern std::atomic<bool> global_exit;

void loop_for_client(const SOCKET socketSrv, /*const*/ std::shared_ptr<std::list<SOCKET>> connections, /*const*/ std::shared_ptr<std::queue<std::string>> msg) {
    const std::thread::id this_id = std::this_thread::get_id();
    {
        //char str[INET_ADDRSTRLEN];
        std::cout << "Thread " << this_id /*<< " has socket " << socketCli << "(" << get_ip_str((const PSOCKADDR)&(addrCli.addr), str, INET_ADDRSTRLEN)*/ << std::endl;
    }
    while(!global_exit) {
        while(!msg->empty()) {
            std::cout << "new msg |> " << msg->front() << std::endl;
            for(const auto& cli : /*std::as_const*/(*connections))
                send(cli, msg->front().c_str(), msg->front().length(), 0); //TODO: check return code
                //write(cli, msg.front().c_str(), msg.front().length());
            msg->pop();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
    std::cout << "Fin du thread " << std::this_thread::get_id() << std::endl;
}
