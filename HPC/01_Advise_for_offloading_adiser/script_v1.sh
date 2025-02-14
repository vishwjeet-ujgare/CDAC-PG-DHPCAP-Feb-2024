#!/bin/bash

echo ""
echo "Available Module Advisor : "
module avail | grep advisor



echo ""
echo "Choose an option:"
echo "1. Load latest Advisor"
echo "2. Load a specific Advisor version"

echo ""
read -p "Enter your choice: " advisor_opt


## Using if statemetn

# if [ $advisor_opt -eq 1 ]; then
#     module load advisor/latest
# else
#     echo "Load Intel offload advisor module : "
#     read offload_advisor
#     module load $offload_advisor
# fi


# Load the Intel Offload Advisor module
case $advisor_opt in
    1) module load advisor/latest ;;
    2) 
        read -p "Enter a specific Advisor version :" offload_advisor_version
        module load $offload_advisor_version ;;
    *) 
        echo "Invalid option. Exiting."
        exit 1 ;;
esac

my_array=( "1. xehpg_256xve : Intel® Arc™ graphics with 256 vector engines", 

           "2. xehpg_512xve : Intel® Arc™ graphics with 512 vector engines",

           "3.    gen12_tgl : Intel® Iris® Xe graphics",

           "4.    gen12_dg1 : Intel® Iris® Xe MAX graphics",

           "5.    gen11_icl : Intel® Iris® Plus graphics",

           "6.     gen9_gt2 : Intel® HD Graphics 530",

           "7.     gen9_gt3 : Intel® Iris® Graphics 550",

           "8.     gen9_gt4 : Intel® Iris® Pro Graphics 580"

           "9.     Enter Manually."
)


my_target_device_list=("xehpg_256xve", "xehpg_512xve","gen12_tgl","gen12_dg1","gen11_icl","gen9_gt2","gen9_gt3","gen9_gt4")


echo ""
echo "================================================"
echo "Available Target device list."
echo "Enter target device name from list only."
echo ""

for element in "${my_array[@]}"; do
  echo "$element"
done

echo "=============================================="


# Ask the user for the target device (e.g. GPU, FPGA, etc.)
read -p "Enter the target device  name from above :" TARGET_DEVICE


until [[ " ${my_target_device_list[@]}" =~ "$TARGET_DEVICE" ]]
do
    echo ""
    echo "XXXXXXXXXXXX"
    echo "$TARGET_DEVICE is not available in above list!"
     echo "====================================="
    
    echo ""
    read -p "Enter the target device name from above: " TARGET_DEVICE
done

echo "Yout Target device :$TARGET_DEVICE is available !"

# # Check if entered name is in the array
# if [[ " ${my_target_device_list[@]} " =~ "$TARGET_DEVICE" ]]; then
#   echo "Yout Target device :$TARGET_DEVICE is available !"
# else
#   echo "$TARGET_DEVICE is not available in above list!"
# fi


# Ask the user for the path to the application executable
echo ""
echo "Enter the path for a executable application/file for profiling:"
echo "1. Do you want to enter full path"
echo "2. Enter file name from current dir"

read -p "Enter Here : "APP_EXECUTABLE


# Ask the user for the where you want to store report

echo ""
echo "we will create a folder in current dir and store report in it "
read -p "Enter a folder name : "OUTPUT_FOLDER_NAME

# Run the application with Offload Advisor
echo ""
echo "Executing Advisor command as : "
echo "advisor --collect=offload --accuracy=high --config=$TARGET_DEVICE --project-dir=./$OUTPUT_FOLDER_NAME -- ./$APP_EXECUTABLE"
echo ""
echo "-"
echo "-"
echo "-"

advisor --collect=offload --accuracy=high --config=$TARGET_DEVICE --project-dir=./$OUTPUT_FOLDER_NAME -- ./$APP_EXECUTABLE
