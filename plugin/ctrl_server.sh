#!/bin/bash
ROOT_PATH=$(pwd)
BIN=${ROOT_PATH}/bin/udp_serverd
LOG=${ROOT_PATH}/log/ctrl_msg.log
CONF=${ROOT_PATH}/conf/server.conf

ctrl_shell_name=$(basename $0)

function usage()
{
	printf "%s/n" "./$ctrl_shell_name [(start/-s)|(stop/-t)|(resart/-r)|(status/-a)]"
}

function print_log()
{
	local log_time=$(date +%Y_%m_%d_%H:%M:%S)
	local msg=$1
	local level=$2
	echo "$log_time $msg $level">>$LOG
}

function check_server()
{
	local server_name=$(basename ${BIN})
	local pid=$(pidof ${server_name})
	if [ ! -z "${pid}" ];then
		return 0
	else
		return 1
	fi
}

function start_server()
{
	if check_server; then
		echo "server is already running"
		print_log "server is alreadly running" "[NOTICE]"
		return 
	fi
	local ip=$(grep -E '^SERVER_IP' $CONF|awk -F':' '{print $NF}')
	local port=$(grep -E '^PORT' $CONF|awk -F':' '{print $NF}')
	${BIN} ${ip} ${port}

	if check_server; then
		echo "start succes"
	fi
}

function stop_server()
{
	if check_server; then
		local server_name=$(basename ${BIN})
		local pid=$(pidof ${server_name})
		kill -9 $pid
	else
		echo "target process is not exist"
		return 
	fi

	if ! check_server; then
		echo "stop success"
		print_log "stop success" "[NOTICE]"
	fi
}

function restart_server()
{
	stop_server
	start_server
}

function status_server()
{
	if check_server; then
		local ip=$(grep -E '^SERVER_IP' $CONF|awk -F':' '{print $NF}')
		local port=$(grep -E '^PORT' $CONF|awk -F':' '{print $NF}')
		echo "server is running status ,pid :  $pid"
	else
		echo "server is not exist"
	fi
}

if [ $# -ne 1 ]; then
	usage
	exit 1
fi

case $1 in
	'start'|'-s' )
	start_server
	;;

	'stop'|'-t' )
	stop_server
	;;

	'resart'|'-r' )
	restart_server
	;;

	'status'|'-a' )
	status_server
	;;

	*)
	usage
	exit 1
esac
