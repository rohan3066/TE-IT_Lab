create()
{
    echo "Enter address book name"

    read ab

    #check address book is available or not in current directory

    res=` ls | grep $ab | wc -w`

    if [ $res -gt 0 ]
    then
        echo "Error:file is alredy existing"

    else
       
       touch $ab
       echo "Address book created successfully"

    fi
}

display()
{
    echo "Enter address book name"

    read ab

    #check address book is available or not in current directory

    res=` ls | grep $ab | wc -w`

    if [ $res -gt 0 ]
    then
        cat $ab

    else
       
      echo "Error : File is not exiting!!" 

    fi

}


insert()
{
    echo "Enter address book name"

    read ab

    #check address book is available or not in current directory

    res=` ls | grep $ab | wc -w`

    if [ $res -gt 0 ]
    then
        echo "Enter your email"
        read email

        len=`cat $ab | grep $email | wc -w`
        if [ $len -gt 0 ]
        then    
            echo "Error: email already present"

        else
            echo "Enter first name,last name,mobile no"
            read fname lname mobile 

            record=`echo $fname $lname $email $mobile`

            echo $record >> $ab
            echo "record inserted!!"
        fi

    else
       echo "Error file is not exit!!"

    fi


}

while [ true ]

do 
    echo "***********MENU*****************"
    echo "1.Create Address Book"
    echo "2.Display Address Book"
    echo "3.Insert Book record"
    echo "7.Exit"
    echo "*********************************"

    echo "Enter choice"

    read choice

    case $choice in 

        1) create ;;
        2)display ;;
        3)insert ;;
        7)exit ;;
        *) echo "Wrong choice!!"

    esac

done