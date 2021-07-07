#!/bin/sh

if [ "$#" -lt "2" ]; then
    echo "Il manque des arguments"
    exit
fi

gcc -Wall -W -Wextra -Werror -Wconversion -O0 -g -std=c99 $1 -o $2
echo "Compilation temrminé"