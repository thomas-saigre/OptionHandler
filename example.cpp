#include <iostream>
#include <vector>
#include <string>
#include "OptionHandler.hpp"

// #define SEEOPT

int main(int argc, char *argv[])
{
    std::string s = "";
    std::cout << s << std::endl;
    OptionHandler::Handler h(argc, argv);
    h.setOpt("hp:vn:",{"help","pick:","verbose","size:"});
#ifdef SEEOPT
    h.seeOpt();
    std::cout << std::endl;
#endif

    std::string opt;
    while ( (opt = h.getOpt()) != "")
    {
        if (opt == "h" || opt == "help")
            std::cout << "help is required (" << opt << ")" << std::endl;
        else if (opt == "p" || opt == "pick")
            std::cout << "pick (" << opt << ") is set to " << h.optarg << std::endl;
        else if (opt == "v" || opt == "verbose")
            std::cout << "verbose is set (" << opt << ")" << std::endl;
        else if (opt == "n" || opt == "size")
            std::cout << "size (" << opt << ") is set to " << h.optarg << std::endl;
    }

    std::cout << std::endl << "optind = " << h.optind << std::endl;
    std::cout << "remaining arguments : " << std::endl;
    for (int i = h.optind; i < argc; ++i)
        std::cout << "   " << argv[i] << std::endl;

    return 0;
}