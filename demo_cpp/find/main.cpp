#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>

#include <dirent.h>

enum Option { None, Name };
typedef std::vector<std::string> StringList;

const std::string NAME = "-name";
const std::string LEVEL = ".";
const std::string LEVEL_UP = "..";

/** Matches @param str by wildcard '?' based @param mask */
bool maskMatch(const std::string& str, const std::string& mask)
{
    if (!mask.size()) return true;
    if (str.size() != mask.size()) return false;

    for (std::string::const_iterator s = str.begin(), m = mask.begin();
            s != str.end(); ++s, ++m)
        if (*m != '?' && *s != *m)
            return false;

    return true;
}

/** Seraches for @param nameMask in @param path */
StringList find(const std::string& path, const std::string& nameMask)
{
    StringList result;
    if (maskMatch(path, nameMask))
        result.push_back(path);

    if (DIR* dirPtr = opendir(path.c_str()))
    {
        while (dirent* dirEnt = readdir(dirPtr))
        {
            std::string dirName(dirEnt->d_name);
            if (dirName == LEVEL || dirName == LEVEL_UP) continue;

            std::string dirPath(path + "/" + dirName);
            if (dirEnt->d_type == DT_DIR)
            {
                StringList res = find(dirPath, nameMask);
                for (StringList::iterator it = res.begin(); it != res.end(); ++it)
                    result.push_back(*it);
            }
            else
            {
                if (maskMatch(dirName, nameMask))
                    result.push_back(dirPath);
            }
        }
    }
    else
    {
        std::ostringstream ss;
        ss << "`" << path << "': No such file or directory";
        throw std::runtime_error(ss.str());
    }

    return result;
}

int main(int argc, const char** argv)
{
    // Configuration
    StringList pathList;
    std::string name;

    // Parse options
    Option option(None);
    for (const char** arg = argv + 1; arg != argv + argc; ++arg)
    {
        std::string str(*arg);
        if (str[0] == '-')
        {
            if (str == NAME)
                option = Name;
            else
            {
                std::cerr << "Error: unknown option `"
                          << str << "'" << std::endl;
                return 1;
            }
        }
        else
        {
            switch (option)
            {
                case None: pathList.push_back(str); break;
                case Name: name = str;              break;
            }
        }
    }

    // Run
    if (!pathList.size())
        pathList.push_back(".");
    try
    {
        for (StringList::iterator path = pathList.begin();
                path != pathList.end(); ++path)
        {
            StringList res = find(*path, name);
            for (StringList::iterator it = res.begin(); it != res.end(); ++it)
                std::cout << *it << std::endl;
        }
    }
    catch(const std::exception& ex)
    {
         std::cerr << "Error: " << ex.what() << std::endl;
    }
}
