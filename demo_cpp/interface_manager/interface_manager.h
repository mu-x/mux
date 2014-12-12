/** Interface Manager definition.
 *
 *  @file: interface_manager.h
 *  @author: Uskov M. V.
 *  @date: 2013-01-22
 */
#ifndef INTERFACE_MANAGER
#define INTERFACE_MANAGER

#include <string>
#include <vector>
#include <stdexcept>
#include <memory>

#include <libudev.h>
#include <unistd.h>

namespace interface_manager {


typedef struct udev             Udev;
typedef struct udev_device      Device;
typedef struct udev_enumerate   Enumirate;
typedef struct udev_list_entry  ListEntry;
typedef struct udev_monitor     Monitor;
typedef struct timeval          TimeValue;


/** The Network Interface.
 *  Provides interface for work with single interfaces.
 */
class Interface {
public:
    Interface(Udev* udev, const std::string& path);
    Interface(Monitor* monitor);
    Interface(const Interface&); // forbidden
    ~Interface();

    std::string name() const;
    std::string description() const;
    std::string event() const;

private:
    Device* device_;
    std::string event_;
    std::string attribute(const std::string& key) const;
};


typedef std::shared_ptr<Interface>  InterfacePtr;   /**< Auto ptr    */
typedef std::vector<InterfacePtr>   InterfaceList;  /**< Auto array  */


/** The Network Interface Manager.
 *  Provides interface for work with network interfaces.
 */
class InterfaceManager {
public:
    InterfaceManager();
    virtual ~InterfaceManager();

    InterfaceList list();   /**< Returns list of network interfases */
    void monitor();         /**< Switches to waiting mode */

    /** Should be overwritten for display information */
    virtual void display(const Interface& interface) = 0;

    /** Should be overwritten for report information */
    virtual void report(const InterfaceList& list) = 0;

    static int  dalay_timeout;  /**< Cicle dalay        */
    static int  repot_timeout;  /**< Cicle report       */
    static bool terminate;      /**< Terminate query    */

private:
    Udev*       udev_;
    Enumirate*  enumerate_;
    Monitor*    monitor_;
    int         report_time;
};


} // namespace interface_manager

#endif // INTERFACE_MANAGER