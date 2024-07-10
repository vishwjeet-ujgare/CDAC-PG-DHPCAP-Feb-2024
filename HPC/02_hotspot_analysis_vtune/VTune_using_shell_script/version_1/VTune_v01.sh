echo ""
echo "================================================"
echo "1 : vtune version name "
echo "================================================"


echo "Enter version from available list   of VTune : "
module avail | grep '\<vtune'

echo "" 
read -p "Enter vtune version to load : " VTUNE_VERSION
module load $VTUNE_VERSION
# echo "$VTUNE_VERSION"

echo ""
echo "==============================================="
echo "2 : Project dir "
echo "==============================================="
read -p "Enter a absolute path for project dir : " ABSOLUTE_PATH
echo "$ABSOLUTE_PATH"

echo "-"
echo "-"
echo "-"



if [ -d "$ABSOLUTE_PATH" ]; then

    REPORT_FOLDER_NAME="${ABSOLUTE_PATH##*/}"
    REPORT_FILE_ABSOLUTE_PATH="$ABSOLUTE_PATH/$REPORT_FOLDER_NAME.vtune"
   
    if [ -f "$REPORT_FILE_ABSOLUTE_PATH" ]; then
        echo "==============================================="
        echo "Report already exist at : "
        echo "$REPORT_FILE_ABSOLUTE_PATH"

        echo "=============================================="
        read -p "Do you want to open existing report yes/no : " WANT_TO_OPEN

        if [ "$WANT_TO_OPEN" == "yes" ]; then
            echo "Opening generated report using  Vtune-gui  "
            echo "==============================================="
            echo "-"
            echo "-"
        
            vtune-gui "$REPORT_FILE_ABSOLUTE_PATH"
        else
            echo "---------------------Exist---------------------"
        fi
        
    else
        echo ""
        echo "==============================================="
        echo "3: executable file"
        echo "==============================================="
        read -p "Enter a absolute path for executable file : " EXECUTABLE_FILE_PATH

        echo ""
        echo "==============================================="
        echo "4: Creating And Running VTune command "
        echo "==============================================="
        echo "-"
        echo "-"
        echo "-"
        echo "-"
        
        read -p "Enter Folder name , we will store your report in it : " REPORT_FOLDER_NAME
        
        REPORT_ABSOLUTE_FOLDER_PATH="$ABSOLUTE_PATH/$REPORT_FOLDER_NAME"
       

        echo "command created...."
        echo "vtune --collect=hotspot --result-dir=$REPORT_ABSOLUTE_FOLDER_PATH -- $EXECUTABLE_FILE_PATH" 
        echo "-"
        echo "-"
        echo "-"
        echo "-"
        echo "Running / Executing command ...."

        vtune --collect=hotspot --result-dir="$REPORT_ABSOLUTE_FOLDER_PATH" -- "$EXECUTABLE_FILE_PATH"

        echo "-"
        echo "-"
        echo "-"
        echo "Report Generated Successfully !"
        ech "-"
        ech "-"
        ech "-"
        ech "-"

        echo "==============================================="
        echo "5 :Open generated report using  Vtune-gui  "
        echo "==============================================="
        echo "-"
        echo "opening generated report"

        REPORT_FILE_ABSOLUTE_PATH="$REPORT_ABSOLUTE_FOLDER_PATH/$REPORT_FOLDER_NAME.vtune"
        vtune-gui "$REPORT_FILE_ABSOLUTE_PATH"

    fi
else
    echo "Folder Does not exist.."
fi



