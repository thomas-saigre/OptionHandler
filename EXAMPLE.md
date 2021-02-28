# Example given

The options given in this example are set like it :

    h.setOpt("hn:",{"help","size:"});

## Working calls to the program

These examples should be working :

| Command                       | optind | remaining arguments |
|:------------------------------|--------|:--------------------|
| `./example -h`                | 2      |                     |
| `./example -h arg1 arg2`      | 2      | `arg1 arg2`         |
| `./example -hv`               | 2      |                     |
| `./example -hv arg`           | 2      | `arg`               |
| `./example -hv -- arg`        | 3      | `arg`               |
| `./example -n 20`             | 3      |                     |
| `./example -n20`              | 2      |                     |
| `./example --size 20`         | 3      |                     |
| `./example -n 20 --`          | 4      |                     |
| `./example -n20 -- arg1 arg2` | 3      | `arg1 arg2`         |
| `./example -n 20 arg`         | 3      | `arg`               |
| `./example --size 20 arg`     | 3      | `arg`               |
| `./example -- -l        `     | 2      | `-l`                |

**WARNING :** the call `./example -n -h` will set `optarg` for option `n` to  the string `"-h"`.


## Not working calls

Those examples should be raising an error


| Command               | ErrorType               | message                                                    |
|:----------------------|:------------------------|:-----------------------------------------------------------|
| `./example -hl`       | `OptionNotValid`        | `Option 'l' not valid`                                     |
| `./example -n`        | `NoArgumentForRequired` | `Option 'n' require an argument`                           |
| `./example --size`    | `NoArgumentForRequired` | `Option 'size' require an argument`                        |
| `./example --size --` | `NoArgumentForRequired` | `Option 'size' require an argument`                        |
| `./example -l`        | `OptionNotValid`        | `Option 'size20' not valid`                                |
| `./example --size20`  | `OptionNotValid`        | `Option 'size20' not valid`                                |
| `./example -hn 20`    | `OptionSequenceError`   | `Option 'n' with argument can be allowed in this sequence` |