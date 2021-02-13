#!/bin/bash
cd $(dirname $0)
HOST="mel"
case $1 in
	("m"|"g")
		for name in ${@:2};do
			echo -e "/* $HOST : $(date) */\n#include <iostream>" > p/${name}.cpp
		done
		;;
	("c"|"-c"|"--compile")
		for name in ${@:2};do
			g++ -o o/${name} p/${name}.cpp
		done
		;;
	(*)
		echo "$0 [m|g] [c|-c|--compile] str ..."
		;;
esac
