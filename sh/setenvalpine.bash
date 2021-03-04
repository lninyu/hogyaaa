#!/bin/bash

deb(){ 
	[ -n "${DEBUG}" ] && echo "debug:${@}"
}

alpinesetup(){ echo "alpine-setup"; } #test

_CHECK(){
	RAND_C=${RANDOM}
	FAIL_COUNT=0
	echo -n "type this [$RAND_C] > "
	while [ -z "${FLAG}" ] ; do
		read STR_C 
		if [ "${STR_C}" -eq "${RAND_C}" ] ; then
			deb check:passed
			FLAG="ok"
		else
			FAIL_COUNT=$((${FAIL_COUNT}+1))
			if [ $FAIL_COUNT -ge 3 ] ; then
				deb check:failed && exit 1
			fi
			echo -n "try again [$RAND_C] > "
		fi
	done
}

_USAGE(){
	cat<<-EOF
		$0 [h|help]
		$0 [d] set 0-3

		set
		0 : alpine-setup -> setenv:all
		1 : alpine-setup -> setenv:sim
		2 : setenv:all
		3 : setenv:sim
	EOF
}

_SETENV(){
	repo_d="/etc/apk/repositories"
	sshd_d="/etc/ssh/sshd_config"
	clrp_d="/etc/profile.d/color_prompt"
	
	[ "$(grep 'PermitRootLogin yes' ${sshd_d})" = "PermitRootLogin yes" ] || \
		cat<<-'EOF'>>${sshd_d} && deb ssh:sshdcfg
		################################
		PermitRootLogin yes
		################################
		EOF
	
	find ${clrp_d} >/dev/null 2>&1 && \
		mv ${clrp_d} ${clrp_d}.sh
	deb rename
	
	cat ${repo_d} | sed -e '2,9s-#--g' > .setenv.temp
	cat .setenv.temp > ${repo_d}
	deb repo:_
	
	find ~/.zprofile >/dev/null 2>&1 || \
		cat<<-'EOF'>~/.zprofile && deb zsh:zprofile
		export _NAME_=""

		for upath in $(ls ~/bin) ; do
		export PATH=${PATH}:/root/bin/${upath}
		done

		autoload -U colors && colors
		autoload -U bashcompinit && bashcompinit
		
		PROMPT="[${_NAME_}] "
		RPROMPT="[%~]"
		EOF

	apk update > /dev/null
	deb apk:update

	[ "${FLAG_m}" = "all" ] \
		&& apk add $(wget -q -O - https://raw.githubusercontent.com/lninyu/hogyaaa/ugaaaaaa/apk.txt) > /dev/null \
		|| apk add zsh vim git coreutils moreutils curl clang gcc > /dev/null
		deb apk:install

	[ "${FLAG_m}" = "all" ] && find ~/.vimrc >/dev/null 2>&1 || \
		cat<<-'EOF'>~/.vimrc && deb vim:vimrc 
		set nocompatible
		filetype off
		set rtp+=~/.vim/bundle/Vundle.vim
		call vundle#begin()
			Plugin 'VundleVim/Vundle.vim'
			Plugin 'tomasr/molokai'
			Plugin 'scrooloose/nerdtree'
			Plugin 'osyo-manga/vim-watchdogs'
		call vundle#end()
		filetype plugin indent on

		set ruler
		set showcmd
		set tabstop=4
		set shiftwidth=4
		set laststatus=4
		set smartcase
		set incsearch
		set hlsearch
		set number
		syntax enable
		colorscheme molokai
		EOF
	
	[ "${FLAG_m}" = "all" ] \
		&& git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim >/dev/null 2>&1 \
		&& vim +PluginInstall +qall \
		&& deb vim:plugin
}

_MAIN(){
	case $1 in
		"d")
			DEBUG="T"
			shift
			_MAIN $1 $2
			;;
		"-h" | "--help")
			_USAGE
			;;
		"set")
			[ -z "$2" ] && deb main:empty arg_2 && exit 1
			_CHECK 2>/dev/null
			case $2 in
				"0")
					alpinesetup && FLAG_m="all" && _SETENV
					;;
				"1")
					alpinesetup && FLAG_m="sim" && _SETENV
					;;
				"2")
					FLAG_m="all" && _SETENV
					;;
				"3")
					FLAG_m="sim" && _SETENV
					;;
				*)
					deb main:wrong number && exit 1
					;;
			esac
			;;
		*)
			deb main:wrong arg && _USAGE && exit 1
			;;
	esac
	
	while [ -z "${FLAG_R}" ];do
		echo -n "reboot? (Yes/No)" ; read INPUT
		case ${INPUT} in
			("yes"|"Yes"|"YES")
				echo reboot
				;;
			("no"|"No"|"NO")
				FLAG_R="T"
				;;
			*)
				echo " YES OR NO"
				;;
		esac
	done
}

_MAIN $1 $2 $3
