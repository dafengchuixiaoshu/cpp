#########################################################################
# Author: 丘安-刘千国
# Created on: 2018-01-09 11:17
#########################################################################
#!/bin/bash

mappdo=""

current_path=`pwd`
deallog_log_dir="${current_path}/../../deal_log"
mkdir -p ${deallog_log_dir}


# 判断是否是目录
function is_dir() {
        file_name=${1}
        r=`file ${file_name} | awk '{print $2}'`
        if [ "${r}" == "directory" ]; then
            echo "${file_name} is Directory"
            return 1
        fi

        return 0
}

# 判断文件是否正在使用
function is_using_file() {
        file_name=${1}
        user_pid=`fuser ${file_name}`
        if [ -n "${user_pid}" ]; then
            echo "========> ${file_name} Using By ${user_pid}"
            return 1
        fi

        return 0
}

# 移动文件
function mv_log_file() {
        file_name=${1}
        dir_name=${2}
        if [ -d ${dir_name} ]; then
            # 对应的目录已经，不用创建
            ${mappdo} mv ${file_name} ${dir_name}/
            echo "${mappdo} mv ${file_name} ${dir_name}/"
        else
            ${mappdo} mkdir ${dir_name}
            echo "${mappdo} mkdir ${dir_name}"

            ${mappdo} mv ${file_name} ${dir_name}/
            echo "${mappdo} mv ${file_name} ${dir_name}/"
        fi
}


############# 1. 归类日志
# 依次文件处理
function classify() {
   for file_name in `ls`
    do
        # 过滤掉脚本文件，避免脚本文件本身被删除
        if [ "${file_name}" == "deal_log.sh" ]; then
            continue
        fi

        # 过滤目录
        is_dir ${file_name}
        if [ $? -ne 0 ]; then
            continue            # 是目录就不用处理，continue
        fi

        # 过滤正在使用的文件
        is_using_file ${file_name}
        if [ $? -ne 0 ]; then
            continue            # 如果文件正在被使用，continue
        fi

        # 得到文件最后修改的日期
        day=`stat -t ${file_name} | awk '{print $13}' |awk '{print strftime ("%F",$0)}'`

        # 移动文件
        mv_log_file ${file_name} ${day}

        #printf "%s------%s\n" ${file_name} ${day}
        #break
    done
}


############# 2. 开始删除较早的日志
# 最早保留的时间点
function remove_log() {

    local bigger_time=`date +%s`
    local min_dir_name=""           # 记录最老的那个文件夹的名字
    for file_name in `ls`
    do
        is_dir ${file_name}
        if [ $? -eq 1 ]; then
            local this_time=`date -d "${file_name}" +%s`
            if [ ${bigger_time} -ge ${this_time} ]; then
                bigger_time=${this_time}
                min_dir_name=${file_name}
            fi
        fi
    done

    ${mappdo} rm -rf ${min_dir_name}
    echo `date "+%Y-%m-%d %H:%M:%S"`"=============== ${mappdo} rm -rf ${min_dir_name}" >> ${deallog_log_dir}/deal_log.log
}


############### while接口
function do_while() {
    echo `date "+%Y-%m-%d %H:%M:%S"`"===========Begin......" >> ${deallog_log_dir}/deal_log.log

    while true
    do
        # 归类文件
        classify

        # 尝试删除文件
        for per_num in `df -h | sed 1d | awk '{print $5}' | tr -d %`;
        do
            if [[ ${per_num} -ge 80 ]]; then
                echo `date "+%Y-%m-%d %H:%M:%S"`" df -h===============${per_num}" >> ${deallog_log_dir}/deal_log.log
                remove_log
            fi
        done;

        sleep 120
        #sleep 5
    done
}




##### 主调度流程
do_while
