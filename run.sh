#!/bin/bash
cols=125
rows=21

orig_cols=$(tput cols)
orig_rows=$(tput lines)



printf "\e[8;%s;%st" "$rows" "$cols"

sleep 1

./build/main

printf "\e[8;%s;%st" "$orig_rows" "$orig_cols"