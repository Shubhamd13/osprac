#!/bin/bash
#Shell programming
#Write a program to implement an address book with options given below:
#a) Create address book. b) View address book. c) Insert a record. d) Delete a record.
#e) Modify a record. f) Exit.
addrbk="AddressBook.txt"
num=0
while [ "$choice" != "6" ]
do
	echo -e "Menu \n 1.Create\n 2.View\n 3.Insert\n 4.Delete\n 5.Modify\n 6.Exit\n"
	printf "Enter your choice:"
	read choice
	case $choice in
		1)
		if [ -a "$addrbk" ];then
			echo "File already exist"
			last=`tail -1 $addrbk`
			if [ -z "$last"  ]
			then
				#empty string
				num=0
			else
				num="${last:0:1}"
			fi
		else
			touch $addrbk
			echo "File created successfully"
		fi
		;;
		2)cat $addrbk
		;;
		3)if [ -a "$addrbk" ];then
		printf "Enter name :"
		read name
		printf "Enter address :"
		read address
		last=`tail -1 $addrbk`
			if [ -z "$last"  ]
			then
				#empty string
				num=0
			else
				num="${last:0:1}"
			fi
		num=`expr $num + 1`
		echo "$num . $name $address">>$addrbk
		fi
		;;
		4)
		echo "Enter num to del"
		read num
	        if grep "^$num" "$addrbk"
		then 
			echo "found"
			touch temporary
			grep  -v "^$num" $addrbk >> temporary
			rm $addrbk
			mv temporary $addrbk
		else echo "Not found"
		fi
		;;	
		5)
		echo "Enter num to Modify"
		read num
	        if grep "^$num" "$addrbk"
		then 
		#remove that record
			echo "found"
			touch temporary
			grep  -v "^$num" $addrbk >> temporary
			rm $addrbk
			mv temporary $addrbk
		#insert with new values
		printf "Enter new name :"
		read name
		printf "Enter new address :"
		read address 
		#Add
		echo "$num . $name $address">>$addrbk
		#Sort
		sort -o $addrbk $addrbk		
		else echo "Not found"
		fi
		;;
		6)echo "Bye.";;
		*)echo "Enter 1-6 only";;
	
	esac
done
