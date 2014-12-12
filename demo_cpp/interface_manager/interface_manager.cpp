/** Interface Manager implementation.
 *
 *  @file: interface_manager.cpp
 *  @author: Uskov M. V.
 *  @date: 2013-01-22
 */
#include "interface_manager.h"

namespace interface_manager {


int InterfaceManager::dalay_timeout =  100000;  // 100ms
int InterfaceManager::repot_timeout = 5000000;  // 5s
bool InterfaceManager::terminate    =   false;  // still work


Interface::Interface(Udev* udev, const std::string& path)
{
    if (device_ = udev_device_new_from_syspath(udev, path.c_str()))
        event_ = "sync";
        return;
    throw std::runtime_error("Can't get device from syspath.");
}

Interface::Interface(Monitor* monitor)
{
    if (device_ = udev_monitor_receive_device(monitor)) {
        event_ = udev_device_get_action(device_);
        return;
    }
    throw std::runtime_error("Can't get device from monitor.");
}

Interface::~Interface()
{
    udev_device_unref(device_);
}

std::string Interface::name() const
{
    return udev_device_get_sysname(device_);
}

std::string Interface::description() const
{
    return name() + " " + attribute("address") + " " + attribute("type");
}

std::string Interface::event() const
{
    return event_;
}

std::string Interface::attribute(const std::string& key) const
{
    if (const char* value = udev_device_get_sysattr_value(
            device_, key.c_str()))
        return value;

    throw std::runtime_error("Can't get attribute " + key +
        " from device " + name() + ".");
}


InterfaceManager::InterfaceManager()
{
    if (!(udev_ = udev_new()))
        throw std::runtime_error("Can't create udev object.");

    enumerate_ = udev_enumerate_new(udev_);
    udev_enumerate_add_match_subsystem(enumerate_, "net");
}

InterfaceManager::~InterfaceManager()
{
    udev_enumerate_unref(enumerate_);
    udev_unref(udev_);
}

InterfaceList InterfaceManager::list()
{
    udev_enumerate_scan_devices(enumerate_);
    ListEntry* entry;
    ListEntry* devices = udev_enumerate_get_list_entry(enumerate_);

    InterfaceList device_list;
    udev_list_entry_foreach(entry, devices) {
        const char* path = udev_list_entry_get_name(entry);
        InterfacePtr interface(new Interface(udev_, path));
        device_list.push_back(interface);
    }
    return device_list;
}

void InterfaceManager::monitor()
{
    report(list());
    report_time = 0;

    monitor_ = udev_monitor_new_from_netlink(udev_, "udev");
    if (!monitor_)
        throw std::runtime_error("Can't create monitor.");

    udev_monitor_filter_add_match_subsystem_devtype(monitor_, "net", 0);
    udev_monitor_enable_receiving(monitor_);

    int fd = udev_monitor_get_fd(monitor_);
    while (1) {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(fd, &fds);

        TimeValue tv;
        tv.tv_sec = tv.tv_usec = 0;

        int ret = select(fd+1, &fds, 0, 0, &tv);
        if (ret > 0 && FD_ISSET(fd, &fds))
            display(Interface(monitor_));

        usleep(dalay_timeout);
        report_time += dalay_timeout;
        if (report_time + dalay_timeout > repot_timeout) {
            report(list());
            report_time = 0;
        }
        
        if (terminate)
	  return;
    }
}


} // namespace interface_manager

