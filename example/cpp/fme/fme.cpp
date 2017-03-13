#include "fme.hpp"

namespace fme {

// Error

Error::Error(const std::string& message)
    : std::logic_error(message)
{
}

// Entry

Entry::~Entry()
{
}

Entry* File::clone() const
{
    return new File(*this);
}

Entry::Children& File::children()
{
    throw Error("file does not have any children");
}

void File::print(std::ostream& os, size_t level) const
{
}

// Directory

Directory::Directory()
{
}

Directory::Directory(const Directory& other)
{
    for (Children::const_iterator it = other._children.begin();
            it != other._children.end(); ++it)
        _children[it->first] = it->second->clone();
}

Directory::~Directory()
{
    for (Children::iterator it = _children.begin();
            it != _children.end(); ++it)
        delete it->second;
}

Entry* Directory::clone() const
{
    return new Directory(*this);
}

Entry::Children& Directory::children()
{
    return _children;
}

void Directory::print(std::ostream& os, size_t level) const
{
    for (Children::const_iterator it = _children.begin();
            it != _children.end(); ++it)
    {
        for (int i = 0; i < level; ++i) os << "| ";
        os << "- " << it->first << std::endl;
        it->second->print(os, level + 1);
    }
}

// FileSystem

void FileSystem::makeFile(const std::string& path)
{
    std::vector<std::string> dirs = split(path, '/');
    Entry& entry = fetchEntry(dirs.begin(), dirs.end() - 1);
    std::string name = *(dirs.end() - 1);

    if (!entry.children().insert(std::make_pair(name, new File())).second)
        throw Error("file already exists");
}

void FileSystem::makeDirectory(const std::string& path)
{
    std::vector<std::string> dirs = split(path, '/');
    Entry& entry = fetchEntry(dirs.begin(), dirs.end() - 1);
    std::string name = *(dirs.end() - 1);

    if (!entry.children().insert(std::make_pair(name, new Directory())).second)
        throw Error("directory already exists");
}

void FileSystem::remove(const std::string& path)
{
    std::vector<std::string> dirs = split(path, '/');
    Entry& entry = fetchEntry(dirs.begin(), dirs.end() - 1);
    std::string name = *(dirs.end() - 1);

    Entry::Children::iterator it = entry.children().find(name);
    if (it == entry.children().end())
        throw Error("no such file or directory");

    delete it->second;
    entry.children().erase(it);
}

void FileSystem::copy(const std::string& source, const std::string& target)
{
    std::vector<std::string> sDirs = split(source, '/');
    Entry& sEntry = fetchEntry(sDirs.begin(), sDirs.end() - 1);
    std::string sName = *(sDirs.end() - 1);

    std::vector<std::string> tDirs = split(target, '/');
    Entry& tEntry = fetchEntry(tDirs.begin(), tDirs.end() - 1);
    std::string tName = *(tDirs.end() - 1);

    Entry::Children::iterator it = sEntry.children().find(sName);
    if (it == sEntry.children().end())
        throw Error("no such file or directory");

    Entry* entryCopy = it->second->clone();
    if (!tEntry.children().insert(std::make_pair(tName, entryCopy)).second)
        throw Error("target already exists");
}

void FileSystem::move(const std::string& source, const std::string& target)
{
    std::vector<std::string> sDirs = split(source, '/');
    Entry& sEntry = fetchEntry(sDirs.begin(), sDirs.end() - 1);
    std::string sName = *(sDirs.end() - 1);

    std::vector<std::string> tDirs = split(target, '/');
    Entry* tEntry = &fetchEntry(tDirs.begin(), tDirs.end() - 1);
    std::string tName = *(tDirs.end() - 1);

    Entry::Children::iterator sIt = sEntry.children().find(sName);
    if (sIt == sEntry.children().end())
        throw Error("no such file or directory");

    Entry::Children::iterator tIt = tEntry->children().find(tName);
    if (tIt != tEntry->children().end())
    {
        tEntry = tIt->second;
        tName = sName;
    }

    if (!tEntry->children().insert(std::make_pair(tName, sIt->second)).second)
        throw Error("target already exists");
    sEntry.children().erase(sIt);
}

Entry& FileSystem::fetchEntry(Path::const_iterator begin, Path::const_iterator end)
{
    Entry* entry = &root;
    while (begin != end)
    {
        Entry::Children::iterator it = entry->children().find(*begin);
        if (it == entry->children().end())
            throw Error("does not have such child");

        entry = it->second;
        begin++;
    }
    return *entry;
}

std::ostream& operator <<(std::ostream& os, const FileSystem& fs)
{
    os << "/" << std::endl;
    fs.root.print(os);
    return os;
}

// helpres

std::vector<std::string> split(const std::string& line, char delimiter)
{
    std::istringstream ss(line);
    std::vector<std::string> parsed;
    while (!ss.eof())
    {
        std::string token;
        std::getline(ss, token, delimiter);
        if (token.size()) parsed.push_back(token);
    }
    return parsed;
}

} // fme

