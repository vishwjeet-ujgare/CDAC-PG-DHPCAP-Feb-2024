#!/bin/bash

# Function to echo text in color
echo_color() {
    local color="$1"
    shift
    echo -e "\e[${color}m$@\e[0m"
}

echo "=================================================="
echo "Flat profile and call graph using Gprof"
echo "=================================================="
echo ""

echo_color "1;32" "Example: gcc -pg -o my_application my_application.c"

echo "Above command compiles the program with profiling enabled and creates an executable."
echo "--------------------------------------------------"

while true; do
    echo "Enter the path for the application/program."
    echo "You can enter either the full path or just the filename if it's in the current directory."
    echo "---------------------------------------------------"

    read -p "Enter path here: " EXECUTABLE_FILE_PATH

    # Check if EXECUTABLE_FILE_PATH is empty or null
    if [ -z "$EXECUTABLE_FILE_PATH" ]; then
        echo "Please enter a file name."
    elif [ ! -e "$EXECUTABLE_FILE_PATH" ]; then
        echo_color "1;31"  "File '$EXECUTABLE_FILE_PATH' does not exist. Please enter a valid file path."
echo "=================================================="

    else
        # Extracting filename with and without extension from the path entered
        FILE_NAME=$(basename "$EXECUTABLE_FILE_PATH")

        FILE_NAME_WITH_EXT="$FILE_NAME"  # Assuming $FILE_NAME already has extension
        FILE_NAME_WITHOUT_EXT="${FILE_NAME%.*}"

        echo -n "File name without extension:"
        echo_color "1;33" "$FILE_NAME_WITHOUT_EXT"

        echo -n "File name with extension:"
        echo_color "1;33" "$FILE_NAME_WITH_EXT"

        echo "--------------------------------------------------"

        # Compile with gcc if path exists
        gcc -pg -o "$FILE_NAME_WITHOUT_EXT" "$FILE_NAME_WITH_EXT"
        if [ $? -eq 0 ]; then
            echo_color "1;32" "Compilation successful"
                echo "-Now run your '$FILE_NAME_WITHOUT_EXT' file"
                echo -n "-it will  create a file : "
                echo_color "1;34" "gmon.out"


        else
            echo_color "1;31" "Compilation failed"
            exit
           fi
        break
    fi
done

echo "--------------------------------------------------"


attempt=1
while [ $attempt -le 3 ]; do
    read -p "Is your executable in the current folder? (Y/n or YES/no): " IS_EXECUTABLE_IN_CURRENT_FOLDER

    case $IS_EXECUTABLE_IN_CURRENT_FOLDER in
        [Yy]|[Yy][Ee][Ss])
          echo "----------------------------------------------"
            echo "executing file ....."
            echo "      --"
            echo "      --"
            echo "      --"
            #  when the executable is in the current folder
             ./$FILE_NAME_WITHOUT_EXT
            
            echo "-------------------------------------------"
            echo_color "1;32" "gmon.out is ready"
            break
            ;;
        [Nn]|[Nn][Oo])
            echo "--------------------------------------------------"
            echo_color "1;31" "Please then keep you executable in current folder for now "
            break
            ;;
        *)
        echo "--------------------------------------------------"
            echo "Invalid input. Please enter Y/y/YES/yes/N/n/NO/no."
            echo_color "1;31" "attempt : $attempt"

            if [ $attempt -eq 3 ]; then
                echo_color "1;31" "You have exhausted your attempts. Exiting program..."
                echo "      -"
                echo "      -"
                echo "      -"
                echo "exited"
                exit 1
            else
                ((attempt++))
            fi
            ;;
    esac
done


echo "----------------------------------"
report_file = "${FILE_NAME_WITHOUT_EXT}_report.txt"
echo "$rep"
 # Check if $FILE_NAME_WITHOUT_EXT.txt already exists
            if [ -f "$report_file" ]; then
                # File exists, replace it and notify the user
                
                echo_color "1;33" "Output file $report_file already exists"

                echo "Replacing..."
                echo "      -"
                echo "      -"

                rm $report_file
                echo "File removed...."
            fi
        
# File does not exist, create it and notify the user
echo "-----------------------------------------------"
echo "creating a file ..."
echo "      -"
echo "      -"
echo "      -"

touch $report_file
echo_color "1;32" "Output file $report_file created."
echo "File created in the current directory."
echo "-------------------------------------------------"

gprof $FILE_NAME_WITHOUT_EXT gmon.out > $FILE_NAME_WITHOUT_EXT.txt
         
       