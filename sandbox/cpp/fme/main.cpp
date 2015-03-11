#include "fme.hpp"

#include <iostream>
#include <string>
#include <vector>

void execute(fme::FileSystem& fs, const std::vector<std::string>& command)
{
    // TODO: use generics and std::function to reduse code when c++11 avaliable

    if (command[0] == "mf")
    {
        if (command.size() != 2) throw fme::Error("mf needs 1 argument");
        fs.makeFile(command[1]);
    }
    else
    if (command[0] == "md")
    {
        if (command.size() != 2) throw fme::Error("md needs 1 argument");
        fs.makeDirectory(command[1]);
    }
    else
    if (command[0] == "rm")
    {
        if (command.size() != 2) throw fme::Error("rm needs 1 argument");
        fs.remove(command[1]);
    }
    else
    if (command[0] == "cp")
    {
        if (command.size() != 3) throw fme::Error("cp needs 2 arguments");
        fs.copy(command[1], command[2]);
    }
    else
    if (command[0] == "mv")
    {
        if (command.size() != 3) throw fme::Error("mf needs 2 arguments");
        fs.move(command[1], command[2]);
    }
    else
    {
        std::ostringstream ss;
        ss << "unsupported command `" << command[0] << "'";
        throw fme::Error(ss.str());
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout << "File Manager Emulator by Uskov Mikhail (2015)" << std::endl
              << "Ctrl+D for exit" << std::endl;
    try
    {
        fme::FileSystem fs;
        std::cout << fs << "> ";
        while (!std::cin.eof())
        {
            std::string line;
            std::getline(std::cin, line);

            std::vector<std::string> command = fme::split(line, ' ');
            if (!command.size()) continue;

            try
            {
                execute(fs, command);
                std::cout << fs;
            }
            catch (const fme::Error& error)
            {
                std::cerr << "ERROR: " << error.what() << std::endl;
            }
            std::cout << "> ";
        }
    }
    catch (const std::exception& error)
    {
        std::cerr << "FATAL ERROR: " << error.what() << std::endl;
    }

    std::cout << "Ctrl+D Exit..." << std::endl;
}

