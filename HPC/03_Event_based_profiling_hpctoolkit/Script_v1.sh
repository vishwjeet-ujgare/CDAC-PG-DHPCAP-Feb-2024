#!/bin/bash

source /home/apps/spack/share/spack/setup-env.sh
spack load hpctoolkit

while true
do
    echo "Enter your choice (space separated) for the following events"
    echo "1. REALTIME"
    echo "2. CPUTIME"
    echo "3. perf::CACHE-MISSES"
    echo "4. MEMLEAK"
    echo "5. IO"

    read -p "Choice: " choice

       case "$choice" in

        *CPUTIME*REALTIME | *REALTIME*CPUTIME)
            echo "REALTIME and CPUTIME cannot be used together.. Try again!"
            ;;  # Added the missing ;; here
        *)
            if [[ "$choice" != *REALTIME* && "$choice" != *CPUTIME* ]]
            then
                echo "Must contain either REALTIME or CPUTIME"
                continue
            fi
            
            array=($choice)
            for i in "${array[@]}"
            do
                command+="-e $i "
            done
            break
    esac
done

### ask for location of executable file from user ###
while true
do
    echo "Enter path of executable file"
    read -r path
    if [[ -f "$path" ]]
    then
        file_name=$(basename $path)
        break
    else
        echo "File not found. Please enter path again."
    fi
done

echo "Do you want to run the with the tracer command ?"
read -p "Enter Y/N: " answer
if [[ $answer == Y || $answer == y ]]
then
    echo "Executing command: hpcrun $command -t $path"
    hpcrun $command -t $path
elif [[ $answer == N || $answer == n ]]
then
    hpcrun $command $path
fi
### compute program structure information ###
echo "Executing command: hpcstruct $file_name"
hpcstruct hpctoolkit-$file_name-measurements


### combine measurement data with program structure information ###
echo "Executing command: hpcprof hpctoolkit-$file_name-measurements"
hpcprof hpctoolkit-$file_name-measurements

### view the kernel-level profile and trace data ###
echo "Executing command: hpcviewer hpctoolkit-$file_name-measurements"
hpcviewer hpctoolkit-$file_name-database

 