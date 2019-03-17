# Date : 2017.04.28
# Desc : Automatically install CVM on Linux
#!/usr/bin/bash

checkExecution()
{

    type ${1} > /dev/null 2>&1
    returnCode=$?
 
    if [ "x"${returnCode} == "x0" ]; then
        echo "${1} is found!"
    else
        exitCode=1
        echo "${1} is not found, you can use package manager available to install it!" 
        echo "Abort with code ${exitCode}"
        exit ${exitCode}
    fi
}

checkExecution supervisord

./compile.sh

set -x
mkdir /etc/cvm
mkdir /var/cvm
cp conf/cvm/* /etc/cvm
cp conf/supervisor/* /etc/cvm/supervisor.d/conf.d
cp bin/* /usr/bin
set +x
