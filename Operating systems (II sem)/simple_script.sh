#/bin/bash

grep "OK DOWNLOAD" cdlinux.ftp.log | cut -d"\"" -f 2,4 | grep "\.iso"| sort -u |grep -o "cdlinux-.*" >temp.txt

cut -d" " -f 1,7,9 cdlinux.www.log |grep '200$'|sort -u |cut -d " " -f 2|grep "\.iso"|grep -o "cdlinux-.*" |sed "s#?.*##" >>temp.txt

cat< temp.txt | sort | uniq -c | sort -n -r

