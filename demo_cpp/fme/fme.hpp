#ifndef FME_HPP
#define FME_HPP

#include <sstream>
#include <stdexcept>
#include <vector>
#include <map>

namespace fme {

/** Splits @param line by @param selimiter */
std::vector<std::string> split(const std::string& line, char delimiter);

class Error : public std::logic_error
{
public:
    explicit Error(const std::string& message);
};

/** Abstract FS Entry */
class Entry
{
public:
    // TODO: use unique_ptr when c++11 or boost is avaliable
    typedef std::map<std::string, Entry*> Children;
    virtual ~Entry();

    virtual Entry* clone() const = 0;
    virtual Children& children() = 0;
    virtual void print(std::ostream& os, size_t level = 1) const = 0;
};

class File : public Entry
{
public:
    virtual Entry* clone() const;
    virtual Children& children();
    virtual void print(std::ostream& os, size_t level = 1) const;
};

class Directory : public Entry
{
public:
    Directory() /* = default (c++11) */;
    Directory(const Directory& other); /* = default (c++11) */
    virtual ~Directory();

    virtual Entry* clone() const;
    virtual Children& children();
    virtual void print(std::ostream& os, size_t level = 1) const;

private:
    Children _children;
};

/** File System Emulation Interface */
class FileSystem
{
public:
    void makeFile(const std::string& path);
    void makeDirectory(const std::string& path);
    void remove(const std::string& path);
    void copy(const std::string& source, const std::string& target);
    void move(const std::string& source, const std::string& target);

    friend std::ostream& operator <<(std::ostream& os, const FileSystem& fs);

private:
    typedef std::vector<std::string> Path;
    Entry& fetchEntry(Path::const_iterator begin, Path::const_iterator end);

    Directory root;
};

} // fme

#endif // FME_HPP

