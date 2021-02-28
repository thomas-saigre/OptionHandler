#ifndef _GETOPT_HPP
#define _GETOPT_HPP

#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <iostream>

namespace OptionHandler
{

class NoArgumentForRequired : public std::invalid_argument
{
public:
    NoArgumentForRequired(std::string name) :
    std::invalid_argument("Option '" + name + "' require an argument") {}
};

class OptionNotValid : public std::invalid_argument
{
public:
    OptionNotValid(std::string name) :
    std::invalid_argument("Option '" + name + "' not valid") {}
};

class OptionSequenceError : public std::invalid_argument
{
public:
    OptionSequenceError(std::string seq) :
    std::invalid_argument("Option '" + seq + "' with argument can't be allowed \
in this sequence") {}
};

class Handler
{
    using args_t = std::vector<std::string>;
    using opt_t  = std::map<std::string, bool>;
public:

    //! @brief Constructor
    //! @param argc number of arguments
    //! @param argv array of parameters
    Handler(int argc, char *argv[]) :
        M_args( args_t(argv + 1, argv + argc) ), optind( 1 ), M_tmpInd( 1 ),
        M_str( M_args.begin() ), M_end( M_args.end() ) { };

    int optind;
    std::string optarg;

    //! @brief set the options of the program
    //! @param shortOpt string of short arguments, : if it takes an argument
    //!     example : "vn:"
    //! @param longOpt vector of long, if at the end if it take an argument
    //!     example : {verbose, size:}
    void setOpt(std::string shortOpt, args_t longOpt);

    //! @brief parse the arguments (this function goes in a while loop)
    //!     if the options require an argument, it is set in optarg.
    //!     returns the option (long or short) as a string,
    //!     empty string if we reached end of options
    std::string getOpt();

    //! @brief displays all options parsed
    void seeOpt();
private:
    args_t M_args;
    args_t::iterator M_str;
    args_t::iterator M_end;

    opt_t M_declaredOpt;
    opt_t::iterator M_endOpt;

    int M_tmpInd;

    bool  isLong(std::string s) const;
    bool isShort(std::string s) const;

};

void Handler::setOpt(std::string shortOpt, args_t longOpt)
{
    // handling short opts
    int ns = shortOpt.size();
    for (int i = 0; i < ns; ++i)
    {
        std::string s; s.assign(1, shortOpt[i]);
        bool arg = (i < ns-1 && shortOpt[i+1] == ':');
        if (arg) ++i;
        M_declaredOpt.insert(
            std::make_pair( s, arg )
        );
    }

    // handling long options
    int nl = longOpt.size();
    for (int i = 0; i < nl; ++i)
    {
        int size = longOpt[i].size();
        bool arg = (longOpt[i].at(size-1) == ':');
        M_declaredOpt.insert(
          std::make_pair( (arg)? longOpt[i].substr(0,size-1) : longOpt[i], arg )  
        );
    }

    // set M_endOpt
    M_endOpt = M_declaredOpt.end();
}

void Handler::seeOpt()
{
    opt_t::iterator opt = M_declaredOpt.begin();
    opt_t::iterator end = M_declaredOpt.end();
    for (; opt != end; ++opt)
        std::cout << opt->first << " (" << opt->second << ")" << std::endl;
}

std::string Handler::getOpt()
{
    opt_t::iterator opt;
    if (M_str == M_end)
        return "";
    if (*M_str == "--")
    {
        ++optind;
        return "";
    }
    if (M_tmpInd != 1)  // we are in a sequence of short options (eg -la)
    {
        std::string s; s.assign(1, M_str->at(M_tmpInd));
        opt = M_declaredOpt.find(s);
        if (opt == M_endOpt)
            throw OptionNotValid(s);
        else if (opt->second)
            throw OptionSequenceError(s);
        if (M_tmpInd + 1 < M_str->length())
            ++M_tmpInd;
        else
        {
            ++optind; ++M_str;
            M_tmpInd = 1;
        }
        return s;
    }
    if (isShort(*M_str))
    {
        std::string s; s.assign(1, M_str->at(1));
        opt = M_declaredOpt.find(s);
        if (opt == M_endOpt)
            throw OptionNotValid(s);
        else
        {
            if (opt->second)    // the option requires an argument
            {
                if (M_str->length() > 2)
                {
                    optarg = M_str->substr(2);
                    ++optind;
                    ++M_str;
                }
                else if (M_str->length() == 2)
                {
                    ++optind; ++M_str;
                    if ( (M_str == M_end) || (*M_str == "--") )
                        throw NoArgumentForRequired(s);
                    optarg = *M_str;
                    ++optind; ++M_str;
                }
            }
            else
            {
                if (M_tmpInd + 1 < M_str->length())
                    ++M_tmpInd;
                else
                {
                    ++optind; ++M_str;
                    M_tmpInd = 1;
                }
            }
        }
        return s;
    }
    else if (isLong(*M_str))
    {
        std::string s = M_str->substr(2);
        opt = M_declaredOpt.find(s);
        if (opt == M_endOpt)
            throw OptionNotValid(s);
        else
        {
            ++optind; ++M_str;
            if (opt->second)
            {
                if ( (M_str == M_end) || (*M_str == "--") )
                    throw NoArgumentForRequired(s);
                optarg = *M_str;
                ++optind; ++M_str;
            }
        }
        return s;
    }
    else    // we reached end of options
        return "";
}

bool Handler::isLong(std::string s) const
{
    return ((s.length() > 2) && (s[0] == '-') && (s[1] == '-'));
}

bool Handler::isShort(std::string s) const
{
    return ((s[0] == '-') && (s[1] != '-'));
}

}   // namespace OptionHandler

#endif