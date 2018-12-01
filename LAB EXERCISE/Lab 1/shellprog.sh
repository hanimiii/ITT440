#!/bin/bash

cont=true

clear
echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
echo "+                        WELCOME!                         +"
echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
echo ""
echo -n "	Hi! What is your full name?: "
read nama
echo "	Hello $nama"
echo -n "	What can I call you?: "
read nama2
echo ""
echo "	Lets start this program! Are you ready $nama2?"
echo -n "	Press anything to continue! "
read any

while [ $cont == "true" ]
do
	clear
	echo "==========================================================="
	echo "                  Shell Programming               "
	echo "                  ~~~~~~~~~~~~~~~~~               "
	echo ""

	echo "	1. Calculate BMI "
	echo "	2. Temperature Converter"
	echo "	3. Simple Calculator"
	echo "	4. Check File"
	echo "	5. Append Name"
	echo "	6. KM Converter"
	echo "	7. Swap Two Number"
	echo "	8. String Compare"
	echo "	9. String Length"
	echo "	10. Quit"
	echo ""
	read -p "	Please choose the options: " ans

	if [ $ans -eq 10 ]
	then
		cont=false
	elif [ $ans -eq 1 ]
	then
		clear
		echo "==========================================================="
		echo "		   BMI CALCULATOR"
		echo "	Please enter all the details below: "
		echo "	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "
		echo ""
		echo -n "	Weight (kg): "
		read weight
		echo -n "	Height (m): "
		read height

		height=$(echo "scale=2; $height*$height"| bc)
		bmi=$(echo "scale=2; $weight/$height"| bc)

		echo ""
		echo "	Your bmi is $bmi"

		#if [ "$bmi" -ge "30" ];
		#then
		#	echo "	You are obese! Please go exercise!"
		#else	
		#	echo "	You are underweight! Go get yourself a pizza"
		#fi
		echo -n "	Press anything to continue! "
		read any
	elif [ $ans -eq 2 ]
	then
                clear
		echo "==========================================================="
 		echo "               TEMPERATURE CONVERTER"
                echo "  	Please enter all the details below: "
                echo "  	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "
                echo ""
		echo "	1. Fahrenheit -> Celcius"
		echo "	2. Celcius    -> Fahrenheit"
		echo ""
		echo -n "	Choose the options: "
		read fc

		if [ $fc -eq 1 ]
		then
			echo -n "	Enter Temperature (F) : "
			read tf
			tc=$(echo "scale=2; ($tf-32)*(5/9)" | bc)
			echo ""
			echo "	$tf F = $tc C"
			echo ""
		else
			echo -n "	Enter Temperature (C) : "
			read tc
			tf=$(echo "scale=2; $tc*(9/5)+32"| bc)
			echo ""
			echo "	$tc C = $tf F"
			echo ""
		fi

		echo -n "	Press anything to continue! "
		read any
	elif [ $ans -eq 3 ]
	then
		clear
        	echo "==========================================================="
        	echo "			SIMPLE CALCULATOR"
        	echo "			~~~~~~~~~~~~~~~~~"   
			echo ""
			i="y"
			while [ $i == "y" ]
			do
				echo -n "	Enter 1st no.: " 
				read n1
				echo -n "	Enter 2nd no.: "
				read n2

				echo ""
				echo "	1.Addition"
				echo "	2.Substraction"
				echo "	3.Multiplication"
				echo "	4.Division"
				echo ""
				echo -n "	Enter your choice: "
				read ch

				if [ $ch -eq 1 ]
				then
					sum=$(echo "scale=2; $n1+$n2"| bc)
				elif [ $ch -eq 2 ]
				then
					sum=$(echo "scale=2; $n1-$n2"| bc)
				elif [ $ch -eq 3 ]
				then
					sum=$(echo "scale=2; $n1*$n2"| bc)
				elif [ $ch -eq 4 ]
				then
					sum=$(echo "scale=2; $n1/$n2"| bc)
				else
					echo "Invalid Choice"
				fi			
				echo "	The sum is $sum"	
				echo ""
				echo -n "	Do you want to continue? (y/n): "
				read i
			done
	elif [ $ans -eq 4 ]
	then
		clear
                echo "==========================================================="
                echo "                  CHECK FILE"
                echo "                  ~~~~~~~~~~"
		echo -n "	Enter name file to check whether it exist or not: " 
		read filen
		if [ -e $filen ]
		then
			echo "	$filen found"
		else
			echo "	$filen not found"
		fi
		echo ""
		echo "	Press anything to continue! "
		read any
	elif [ $ans -eq 5 ]
	then
		clear
		echo "==========================================================="
                echo "			NAME APPEND"
                echo "			~~~~~~~~~~~"
                echo ""
		echo -n "		Enter Your Name: "
		read name
		echo "$name" >> name.txt
		echo ""
		echo "		Name Appended!"
		echo ""
		cat name.txt
		echo "		Press anything to continue! "
		read any
	elif [ $ans -eq 6 ] 
	then
		clear
		echo "==========================================================="
        echo "			KM CONVERTER"
        echo "			~~~~~~~~~~~~"
        echo ""
		echo -n "	Enter KM: "
		read km

		meter=$(echo "scale=2; $km*1000"| bc)
		feet=$(echo "scale=2; $meter*3.28"| bc)
		inches=$(echo "scale=2; $feet*12"| bc)
		cm=$(echo "scale=2; $feet*30.48"| bc)
		echo ""
		echo "	KM in meter : $meter"
		echo "	KM in feet  : $feet"
		echo "	KM in inches: $inches"
		echo "	KM in cm    : $cm"
		echo ""
		echo "	Press anything to continue! "
		read any
	elif [ $ans -eq 7 ] 
	then
		clear
		echo "==========================================================="
        echo "			SWAP TWO NUMBER"
        echo "			~~~~~~~~~~~~~~~"
        echo ""
		echo "	Enter Two Number to Swap"
		echo -n "	First No : " 
		read no1
		echo -n "	Second No: "
		read no2

		echo ""
		echo "	Before Swap: "
		echo "	First: $no1, Second: $no2"
		echo ""

		first=$no1
		second=$no2

		temp=$first
		first=$second
		second=$temp
		
		echo "	After Swap, numbers are: "
		echo "	First $first, Second: $second"
		echo ""
		echo "	Press anything to continue! "
		read any
	elif [ $ans -eq 8 ]
	then	
		clear
		echo "==========================================================="
        echo "			STRING COMPARE"
        echo "			~~~~~~~~~~~~~~"
		echo ""
		echo "	Enter Two String: "
		echo -n "	1st String: "
		read str1
		echo -n "	2nd String: "
		read str2
		echo ""
		if [ "$str1" == "$str2" ]; then
			echo "	Strings match"
		else
			echo "	Strings doesn't match"
		fi
		echo ""
		echo "	Press anything to continue! "
		read any
	elif [ $ans -eq 9 ]
	then	
		clear
		echo "==========================================================="
        echo "			STRING LENGTH"
        echo "			~~~~~~~~~~~~~"
		echo ""
		echo "	Enter Two String: "
		echo -n "	1st String: "
		read str1
		echo -n "	2nd String: "
		read str2
		echo ""

		size=${#str1}
		size2=${#str2}

		echo "	Length of 1st String is $size"
		echo "	Length of 2nd String is $size2"

		echo "	Press anything to continue! "
		read any
	#elif [ $ans -eq 10 ]
	#then	
	#	clear
	#	echo "==========================================================="
    #    echo "			STRING COLOR"
    #    echo "			~~~~~~~~~~~~"
	#	echo ""
	#	echo "	Enter 5 names: "
	#	read na1
	#	read na2 
	#	read na3
	#	read na4
	#	read na5

	#	echo ""
	#	echo "	Display names in colourful style: "
	#	echo "		\033[34m $na1"
	#	echo "		\033[35m $na2"
	#	echo "		\033[36m $na3"
	#	echo "		\033[37m $na4"
	#	echo "		\033[38m $na5"
	#	echo ""

	#	echo "	Display names in colourful highlighter: "
	#	echo "		\033[41m $na1"
	#	echo "		\033[42m $na2"
	#	echo "		\033[43m $na3"
	#	echo "		\033[44m $na4"
	#	echo "		\033[45m $na5"

	#	echo "	\033[0m"

	#	echo "	Press anything to continue! "
	#	read any
	else
		cont=true
	fi
	echo "==========================================================="
done