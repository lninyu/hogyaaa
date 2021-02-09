#!/bin/bash
VX=$1
VY=$2
CS="┌┐└┘─│"
N=${0##*/}

OBJ(){
  if [ $x = 1 ];then
    echo -n "$1"
  elif [ $x = $VX ];then
    echo -n "$2"
  else
    echo -n "$3"
  fi
}

HELP(){
  echo "${N} [-b|-t] <wide> <height>"
  echo "${N} <wide> <height>"
  echo "${N} [-h]"
  echo "-h --help : show this message"
  echo "-b --bold : bold line"
  echo "-t --thin : thin line(default)"
  exit 0
}

case $1 in
  [0-9]+):;;
  "-b"|"--bold")VX=$2;VY=$3;CS="┏┓┗┛━┃";;
  "-t"|"--thin")VX=$2;VY=$3;;
  "-h"|"--help")HELP;;
  #"--test")${N} -t 3 2;${N} -b 3 2;${N} 3 2;${N} -h;exit 0;;
esac

for y in $(seq $VY);do
  for x in $(seq $VX);do
    if [ $y = 1 ];then
      OBJ "${CS:0:1}" "${CS:1:1}" "${CS:4:1}"
    elif [ $y = $VY ];then
      OBJ "${CS:2:1}" "${CS:3:1}" "${CS:4:1}"
    else
      OBJ "${CS:5:1}" "${CS:5:1}" " "
    fi
  done
  echo
done
