#!/bin/bash

echo ""
echo "Available Module Advisor  "

available_modules=$(module avail | grep advisor)

all_avail_module_list=()

i=1
for module in $available_modules;do 
    if [[ $module =~ ^advisor ]];then
        all_avail_module_list+=("$module")
        echo "      "$i. ${all_avail_module_list[$((i-1))]}
        i=$((i+1))
    fi 
done


while true; do
    echo ""
    read -p "Enter your choice: " advisor_opt

    if [ -z "$advisor_opt" ];then
        echo "Invalid input. Please enter a number."
    elif ! [[ $advisor_opt =~ ^[0-9]+$ ]];then
        echo "Invalid input. Please enter a number."
    elif [ $advisor_opt -gt ${#all_avail_module_list[@]} ];then
        echo "Invalid choice. Please enter a number between 1 and ${#all_avail_module_list[@]}."
    else
        module load ${all_avail_module_list[$((advisor_opt-1))]}
        break
    fi
done

my_array=( "1. xehpg_256xve : Intel® Arc™ graphics with 256 vector engines", 

           "2. xehpg_512xve : Intel® Arc™ graphics with 512 vector engines",

           "3.    gen12_tgl : Intel® Iris® Xe graphics",

           "4.    gen12_dg1 : Intel® Iris® Xe MAX graphics",

           "5.    gen11_icl : Intel® Iris® Plus graphics",

           "6.     gen9_gt2 : Intel® HD Graphics 530",

           "7.     gen9_gt3 : Intel® Iris® Graphics 550",

           "8.     gen9_gt4 : Intel® Iris® Pro Graphics 580",

           "9.     Enter manually.."
)


my_target_device_list=("xehpg_256xve" "xehpg_512xve" "gen12_tgl" "gen12_dg1" "gen11_icl" "gen9_gt2" "gen9_gt3" "gen9_gt4")


echo ""
echo "================================================"
echo "Available Target device list."
echo "Enter target device name from list only."
echo ""

for element in "${my_array[@]}"; do
  echo "$element"
done

echo "=============================================="


export TARGET_DEVICE 
while true
do

    read -p "Enter your target device choice: " TARGET_DEVICE_OPT
 
    if [[ $TARGET_DEVICE_OPT -ge 1 && $TARGET_DEVICE_OPT -le 8 ]]; then
       
        TARGET_DEVICE=${my_target_device_list[$((TARGET_DEVICE_OPT - 1))]}
        echo "Your Target device is : $TARGET_DEVICE"
    break

    elif [ $TARGET_DEVICE_OPT -eq 9 ]; then

        read -p "Enter your target device name:" TARGET_DEVICE
        
    until [[ " ${my_target_device_list[@]}" =~ "$TARGET_DEVICE" ]]
        do
            echo ""
            echo "XXXXXXXXXXXX"
            echo "Enter only available version for  device "
            read -p "Enter the target device name: " TARGET_DEVICE
        done
  
        echo "Your Target device is: $TARGET_DEVICE !"
   
   break
    else
        echo "You are entering wrong option. Please choose a valid option."
        echo ""

    fi
done


# Ask the user for the path to the application executable
echo ""
echo "Enter the path for a executable application/file for profiling:"
read -p "Enter Here : " APP_EXECUTABLE


# Ask the user for the where you want to store report

echo ""
echo "we will create a folder in current dir and store report in it "
read -p "Enter a folder name : " OUTPUT_FOLDER_NAME

# Run the application with Offload Advisor
echo ""
echo "Executing Advisor command as : "
echo "advisor --collect=offload --config=$TARGET_DEVICE --project-dir=$OUTPUT_FOLDER_NAME -- $APP_EXECUTABLE"
echo ""
echo "-"
echo "-"
echo "-"

# write app executable path in double qoute
advisor --collect=offload --config=$TARGET_DEVICE --project-dir=$OUTPUT_FOLDER_NAME -- "$APP_EXECUTABLE"

# /home/user14/Vishwjeet_Ujgare/HPC Programming/profiling Demo/mmult_serial


