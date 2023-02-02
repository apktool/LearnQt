#!/usr/bin/env bash

bin=$(dirname "${BASH_SOURCE-$0}")
bin=$(
  cd "$bin" >/dev/null || exit
  pwd
)
cd "$bin" || exit

declare -r log_path=/tmp/shell.log
declare -r build_dir=${bin}/build
declare -r qt_dir=/home/li/Software/qt-6.4.2/6.4.2/gcc_64
declare -r qt_output=${bin}/output
declare -r qt_target=ch01

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

function build() {
  local cmd="cmake -S ${bin} -B ${build_dir} -DCMAKE_PREFIX_PATH=${qt_dir}"
  run_cmd "${cmd}"
}

function release() {
  local cmd="cd ${build_dir}"
  run_cmd "${cmd}"

  cmd="make"
  run_cmd "${cmd}"

  cmd="rm -rf ${qt_output}"
  run_cmd "${cmd}"

  cmd="mkdir -p ${qt_output}/lib64"
  run_cmd "${cmd}"

  lib_array=($(ldd ${qt_target} | grep -o "/.*" | grep -o "/.*/[^[:space:]]*"))
  for lib in "${lib_array[@]}"; do
    cmd="cp ${lib} ${qt_output}/lib64"
    run_cmd "${cmd}"
  done

  cmd="cp ${build_dir}/${qt_target} ${qt_output}"
  run_cmd "${cmd}"

  cmd="cp ${bin}/start.bash ${qt_output}"
  run_cmd "${cmd}"
}

"$@"
