#!/bin/bash
f="\e[38;2;255;255;255m\e[48;2;255;255;255m"
b="\e[38;2;32;32;32m\e[48;2;32;32;32m"
o="\e[38;2;227;171;94m\e[48;2;227;171;94m"
p="\e[38;2;227;107;162m\e[48;2;227;107;162m"
case $1 in
"-h"|"--hage")echo -en "$o████████████████\n████████████████\n$f██████$o████$f██████\n██$b██$f██$o████$f██$b██$f██\n██████$o████$f██████\n$o████████████████\n$p██$o████$b████$o████$p██\n$o████████████████\n\e[0m";;
*)echo -en "$b████████████████\n$o██$b██$o████$b██$o██$b██$o██\n$f██████$o████$f██████\n██$b██$f██$o████$f██$b██$f██\n██████$o████$f██████\n$o████████████████\n$p██$o████$b████$o████$p██\n$o████████████████\n\e[0m";;
esac