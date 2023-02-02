#!/usr/bin/env bash

bin=$(dirname "${BASH_SOURCE-$0}")
bin=$(
  cd "$bin" >/dev/null || exit
  pwd
)
cd "$bin" || exit

declare -r log_path=/tmp/shell.log
declare -r qt_dir=/home/li/Software/qt-6.4.2/6.4.2/gcc_64
declare -r target=ch01

function run_cmd() {
  local out_file=${log_path}
  local date_format="+%Y-%m-%d %H:%M:%S"

  echo -e "\033[32m [INFO] [$(date "$date_format")] | $* \033[0m" | tee -a "${out_file}"
  local cmd=$1
  shift

  $cmd "$@"
  local return_code=$?

  if [ ${return_code} -ne 0 ]; then
    echo -e "\033[31m [ERROR][$(date "$date_format")] |「ERRORCODE=${return_code}」| $cmd $* \033[0m" | tee -a "${out_file}"
    exit 1
  fi
}

function start() {
  export LD_LIBRARY_PATH=$LD_LIBRATY_PATH:$bin/lib64
  export QT_QPA_PLATFORM_PLUGIN_PATH=${qt_dir}/plugins/platforms

  local cmd="${bin}/${target}"
  run_cmd "${cmd}"
}

"$@"
