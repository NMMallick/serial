#!/usr/bin/env bash
set -euo pipefail

PORT_ONE=20
PORT_TWO=21

start()
{
    #create the two linked pseudoterminals
    socat -d -d pty,raw,echo=0 pty,raw,echo=0 &

    #now create symbolic links to these terminals
    sudo ln -s /dev/pts/1 /dev/ttyUSB$1
    sudo ln -s /dev/pts/2 /dev/ttyUSB$2

    sudo chmod 666 /dev/ttyUSB$1
    sudo chmod 666 /dev/ttyUSB$2
}

#unlinks the symbolic links of the pseudoterminals
stop()
{

    sudo unlink /dev/ttyUSB"$1"
    sudo unlink /dev/ttyUSB"$2"

    ls /dev/ttyUSB*

    sudo killall socat
}


case "$1" in
    start)
	start "${PORT_ONE}" "{PORT_TWO}"
	;;
    stop)
	stop "${PORT_ONE}" "{PORT_TWO}"
	;;
    *)
	echo "Usage: $0 {start|stop}"
	;;
esac
