#!/bin/bash

PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

read -p "Please input your project name: " projectName      # 提示使用者輸入

echo -e "\nYour project name is: ${projectName}" # 結果由螢幕輸出