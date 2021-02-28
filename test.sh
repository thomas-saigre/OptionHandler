#!/bin/sh

# compilation
g++ example.cpp -o example


PROG=${PROG:-./example}	    # program to test
DIR=/tmp/opt                # temp directory

rm -rf $DIR
mkdir $DIR


testArg ()
{
    # those tests should work (return code = 0)
    $PROG  -h > $DIR/out                   || (echo "test failed 1"  && return)
    $PROG  -h arg1 arg2 > $DIR/out         || (echo "test failed 2"  && return)
    $PROG  -hv > $DIR/out                  || (echo "test failed 3"  && return)
    $PROG  -hv arg > $DIR/out              || (echo "test failed 4"  && return)
    $PROG  -hv -- arg > $DIR/out           || (echo "test failed 5"  && return)
    $PROG  -n 20 > $DIR/out                || (echo "test failed 6"  && return)
    $PROG  -n20 > $DIR/out                 || (echo "test failed 7"  && return)
    $PROG  --size 20 > $DIR/out            || (echo "test failed 9"  && return)
    $PROG  --help > $DIR/out               || (echo "test failed 10" && return)
    $PROG  -n 20 -- > $DIR/out             || (echo "test failed 11" && return)
    $PROG  -n20 -- arg1 arg2 > $DIR/out    || (echo "test failed 12" && return)
    $PROG  -n 20 arg > $DIR/out            || (echo "test failed 13" && return)
    $PROG  --size 20 arg > $DIR/out        || (echo "test failed 14" && return)
    $PROG  -- -l > $DIR/out                || (echo "test failed 15" && return)

    # none of these tests whould work (code de retour != 0)
    $PROG -hl 2> $DIR/out 1> $DIR/out         && echo "test failed: 16" >&2 && return
    $PROG -n 2> $DIR/out 1> $DIR/out          && echo "test failed: 17" >&2 && return
    $PROG --size 2> $DIR/out 1> $DIR/out      && echo "test failed: 18" >&2 && return
    $PROG --size -- 2> $DIR/out 1> $DIR/out   && echo "test failed: 19" >&2 && return
    $PROG -l 2> $DIR/out 1> $DIR/out          && echo "test failed: 20" >&2 && return
    $PROG --size20 2> $DIR/out 1> $DIR/out    && echo "test failed: 21" >&2 && return
    $PROG -hn 2> $DIR/out 1> $DIR/out         && echo "test failed: 22" >&2 && return
    
    # if we get here, all the tests passed !
    echo "test ok" >&2
}


testArg