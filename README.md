# OptionHandler 1.0

*adapted from [ryngonzalez/OptionHandler](https://github.com/ryngonzalez/OptionHandler).*


Handle the options given at execution of a C++ program, with an API close to the C function [`getopt`](https://linux.die.net/man/3/getopt).

## Installation

Just download the file [OptionHandler](OptionHandler.hpp) ([view raw](https://raw.githubusercontent.com/thomas-saigre/OptionHandler/master/OptionHandler.hpp))


## Usage

To use with your code, simply include `OptionHandler.hpp` in your source code.

### Command Line Usage

On the command line you can allow your program to take in long or short options.

    ./myprogram --help --size 20 argument1 argument2

This is equivalent:

    ./myprogram -h -s20 argument1 argument2

Here are the rules of the option that can be given at the execution of the program :

* Short option with no argument can be grouped together : `./myprogram -hv`
* Short option with argument can be used in two ways : `./myprogram -n20` or `./myprogram -n 20`
* Use `--` to tell the parser that all the following arugments are not options : `./myprogram -n20 -- -l`, on this example `-l` is not an option, it is an argument of the funciton
* Argument for long option must be separated, and such options cannot be grouped.

See the [EXAMPLE.md](EXAMPLE.md) for the cases. The script code [test.sh](test.sh) runs thoses tests.

**Note :** if `h` is set as a short option, the passing `--h` at the execution will work.

### Developer Usage

#### Instantiation

Instantiate an option handler by passing in the command line input (`argv` and `argc`):

    OptionHandler::Handler(int argc, char *argv[]);

where `argc` and `argv` are the parameters of the `main` function of the program.

Exemple :

    OptionHandler::Handler h(argc, argv);


#### Add options

Add options with `setOpt`:

    void OptionHandler::Handler::setOpt(std::string shortOpt, std::vector<std::string> longOpt);

where :
* `shortOpt` is a string listing all short options (one character each), followed by a `:` if this option requires an argument,
* `longOpt` is a vector of strings, each element of this vector is a long name for an option, followed by a `:` is this option requires an argument.

Example :

    h.setOpt("hp:vn:",{"help","pick:","verbose","size:"});

**NOTE :** we can be tricky and set the char `:` as an option acceptiong argument, so `shortOpt` will contain `::`.


#### Get options

    std::string OptionHandler::Handler::getOpt()

This function has to be called within a `while` loop : it returns the treated option, while there are one of those in the `argv` array. When all the options have been treated, this function returns an empty string `""`.

    std::string opt;
    while ( (opt = h.getOpt()) != "")
    {
        if (opt == "h" || opt == "help")
            // do something;
        else if (opt == "n" || opt == "size")
            // do something
        ...
    }

If the option requires an argument, it is placed in the `std::string` `h.optarg` and can be used in the previous loop.

After the `while` loop is over, the interger `h.optind` tells the index in the array `argv` passed in the constructor where the remaining arguments begin. The remaining arguments can therefore by use with `&argv[h.optind]`. For instance, with the call `./myprogram -h -n 20 arg1 arg2`, `h.optind` will have the value of `4`.


#### See the options

    void OptionHandler::Handler::seeOpt()

displays the list of the options set with the function `setOpt`, in this format : `<name> (<arg>)`, where :
* `<name>` is the name of the option (long or short)
* `<arg>` (1 or 0) is a boolean telling if the option requires an option


## License
Copyright (&copy;) 2021 thomas-saigre

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
of the Software, and to permit persons to whom the Software is furnished to do 
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
SOFTWARE.
