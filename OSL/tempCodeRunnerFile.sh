

create()
{
    echo "Enter address book name"

    read ab

    #check address book is available or not in current directory

    res=` ls | grep &ab | wc -w`

    if [ $res -gt 0 ]
    then
        echo "Error:file is alredy existing"

    else
       
       touch $ab
       echo "Address book created successfully"

    fi
}

while [ true ]

do 
    echo "***********MENU*****************"
    echo "1.Create Address Book"
    echo "2.Display Address Book"
    echo "7.Exit"
    echo "*********************************"

    echo "Enter choice"

    read choice

    case $choice in 

        1) create ;;
        2)exit ;;
        *) echo "Wrong choice!!"

    esac

done