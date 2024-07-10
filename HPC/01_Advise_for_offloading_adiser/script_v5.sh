#!/bin/bash

echo ""
echo "Available Module Advisor  "

# Retriving all availble module which include advisor
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



# https://tinyurl.com/intel-advisor-script




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




echo ""
echo "--------------------------------------------------------"
echo "Now you have to choose File on which you want to perform profiling"

echo "Choose following option :"
        echo "       1. Enter Program file"
        echo "       2. Enter Executable file"
echo "--------------------------------------------------------"
read -p "Enter your choose : " selected_compilation_opt


echo "-----------------------------------------"

export APP_EXECUTABLE

while true; do
    case $selected_compilation_opt in
        1)
            echo "You have selected option 1"
            echo "You want to compile C or C++ file"
            echo "Please enter path of a code file that you want to compile below "
            read -p "Enter your file path here: " entered_compilation_file_path
            echo "-"
            echo "-"

            # -f check does this path exist or not
            if [ -f "$entered_compilation_file_path" ]; then
                
                ## operator removes the longest prefix that matches this pattern,
                entered_compilation_file_name="${entered_compilation_file_path##*/}"
                file_extension="${entered_compilation_file_name##*.}"
                filename_without_extension="${entered_compilation_file_name%.*}"
                
                if [ "$file_extension" == "c" ] || [ "$file_extension" == "cpp" ]; then
                    echo "---------------------------------------------"
                        echo "File path: $entered_compilation_file_path"
                        echo "File Name : $entered_compilation_file_name"
                        echo "File extension: $file_extension"
                        echo "Executable file name will be : $filename_without_extension"
                    echo "---------------------------------------------"
                else
                    echo "Did not find C Or CPP file please check you file extention"
                fi

                if [ "$file_extension" == "c" ]; then
                    
                    gcc -o./executable_output_files/$filename_without_extension $entered_compilation_file_name
                    echo "File successfully compiled : /executable_output_files/$filename_without_extension"
                    
                    APP_EXECUTABLE=$filename_without_extension
                    echo "$APP_EXECUTABLE"
                    echo "-"
                    echo "-"
                    echo "-"

                elif [ "$file_extension" == "cpp" ]; then

                    g++ -o./executable_output_files/$filename_without_extension $entered_compilation_file_name
 
                    echo "File successfully compiled In: /executable_output_files/$filename_without_extension"
                    APP_EXECUTABLE=$filename_without_extension
                    echo "$APP_EXECUTABLE"
                    echo "-"
                    echo "-"
                    echo "-"

                    break
                else
                    echo "Invalid file extension. Please enter a C or C++ file."
                fi
            else
                 echo ""
                    echo "Invalid executable file path. Please enter a valid executable file path."
                    echo "-"
                    echo "-"
                    echo "----------------------------------------------"
                    echo "Please re-enter valid file path"
                    echo "----------------------------------------------"
            fi
            ;;
        2)
            while true; do
                echo ""
                echo "Enter the path for a executable application/file for profiling "
                read -p "Enter executable file name  Here : " entered_compilation_file_path

                if [ -f "$entered_compilation_file_path" ]; then
                        APP_EXECUTABLE="$entered_compilation_file_path"
                        echo "Path name : $APP_EXECUTABLE"
                   
                        exit_loop=true
                    break
                else
                    echo ""
                    echo "Invalid executable file path. Please enter a valid executable file path."
                    echo "-"
                    echo "-"
                    echo "----------------------------------------------"
                    echo "Please re-enter valid file path"
                    echo "----------------------------------------------"
                fi
            done

            if [ "$exit_loop" = true ]; then
             break
            fi
            ;;
        *)
            echo "Please choose 1 or 2 only"
            ;;
    esac
done

echo "---------------------------------------------"

echo ""
echo "we will create a folder in current dir and store report in it "
read -p "Enter a folder name : " OUTPUT_FOLDER_NAME

# Ask the user for the where you want to store report

if [ $selected_compilation_opt -eq 1 ]; then
    # Run the application with Offload Advisor
    echo ""
    echo "Executing Advisor command as : "
    echo "advisor --collect=offload --config=$TARGET_DEVICE --project-dir=$OUTPUT_FOLDER_NAME -- ./executable_output_files/"$APP_EXECUTABLE
    echo ""
    echo "-"
    echo "-"
    echo "-"

    advisor --collect=offload --config=$TARGET_DEVICE --project-dir=$OUTPUT_FOLDER_NAME -- ."/executable_output_files/"$APP_EXECUTABLE
elif [ $selected_compilation_opt -eq 2 ]; then

    echo ""
    echo "Executing Advisor command as : "
    echo "advisor --collect=offload --config=$TARGET_DEVICE --project-dir=$OUTPUT_FOLDER_NAME -- $APP_EXECUTABLE"
    echo ""
    echo "-"
    echo "-"
    echo "-"
    # write app executable path in double qoute
    advisor --collect=offload --config=$TARGET_DEVICE --project-dir=$OUTPUT_FOLDER_NAME -- "$APP_EXECUTABLE"
fi



# /home/user14/Vishwjeet_Ujgare/HPC Programming/profiling Demo/mmult_serial


