### MasterMind
# a Master Mind console game in C language

## Instructions

1) Compile command

# make

It will compile as:

gcc -c -o mastermind_functions.o mastermind_functions.c -Wall -Wextra -Werror
gcc -c -o mastermind_data_struct.o mastermind_data_struct.c -Wall -Wextra -Werror
gcc -c -o mastermind.o mastermind.c -Wall -Wextra -Werror
gcc -o mastermind mastermind_functions.o mastermind_data_struct.o mastermind.o -Wall -Wextra -Werror

2) Clean up command

# make clean

it will clean up object files (.o) and the executable programa (mastermind)

3) Run the program

Usage: ./mastermind [-d] [-h]
        -d [Debug]: prints out the secret code for debug
        -h [Help]: this help

from the current directory or use the absolute path (/path/to/some/where/mastermind)

4) Known issues
In case of unicode characters visualization problems, try to change font type (mono?) in your terminal
