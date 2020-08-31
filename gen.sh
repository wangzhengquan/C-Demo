#!/bin/bash
# Program:
#	Use function to repeat information.
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

# 创建
function create(){
	echo "Your choice is ${1}  ${2}"   # 這個 $1 必須要參考底下指令的下達
	mpath="${1}/${2}"
	mkdir ${mpath}
	cp -a Make* ${mpath} && cp systype.sh  ${mpath}
	cp -a template ${mpath}/src
	cp -a lib ${mpath} && cp -a include ${mpath}
  cp -a .gitignore ${mpath}
  echo "${mpath}: create success !"

}

function usage() {
	echo "Usage ${0} {create} projectPath projectName "
}

echo $#

# 参数数量小于3
if test $# -lt 3; then
	usage ${0}
	exit 1
fi

case ${1} in
  "create")
	create ${2} ${3} # 請注意， create 指令後面還有接參數！
	;;
 	
  *)
    usage ${0}
	exit 1
	;;
esac
