/** Interface Manager main program.
 *
 *  @file: main.cpp
 *  @author: Uskov M. V.
 */
#include "interface_manager.h"

#include <iostream>
#include <iomanip>

#include <signal.h>


class InterfaceManager :
    public interface_manager::InterfaceManager {
public:
    /** Displaies events */
    virtual void display(const interface_manager::Interface& interface)
    {
        std::string event = interface.event();
        if (event == "add")
            std::cout << "NEW " << interface.description() << std::endl;
        if (event == "remove")
            std::cout << "GONE " << interface.name() << std::endl;

    }
    /** Reports every 5 sec (by design) */
    virtual void report(const interface_manager::InterfaceList& list)
    {
        for (interface_manager::InterfaceList::const_iterator it = list.begin();
                it != list.end(); ++it)
            std::cout << "IFACE " << (*it)->description() << std::endl;
    }
};

void sig_handler(int signum)
{
    // Only query to termination
    interface_manager::InterfaceManager::terminate = true;
    std::cout << "Preparing to exit..." << std::endl;
}

int main(int argc, char* argv[])
{
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);

    try {
        InterfaceManager manager;
        manager.monitor();
    } catch (const std::exception& error) {
        std::cout << std::string("Error: ") + error.what() << std::endl;
        return -1;
    }
    std::cout << "Exit." << std::endl;
}
