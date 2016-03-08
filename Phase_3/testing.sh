#!/bin/bash

# 5 command line inputs
# the program name
# the bank account's file
# the bank transaction file name
# the folder where the tests are stored
# (option) a specific folder to run the test on
program="$1"
bankaccountfile="$2"
banktransactionfile="$3"
TestingFolder="$4"

#check for if there a specific folder of tests to run
if [ "$5" == "" ]; then
	TransactionFolder=""
else
	TransactionFolder="$5"
fi

#get the start time and date
start=$(date +%s%N)
date=$(date +"%m-%d-%y-%T")
echo Start
echo "" > log.txt

#if the bank trastaction fie already exits, delete it
if [ -e $banktransactionfile ]; then
	rm $banktransactionfile
fi


# get all the folder in the Testing folder, and pipeline then grep to see if
#there is a specific folder that you want to run test on
for Transaction_Folders in $(ls $TestingFolder | grep "$TransactionFolder");
do
	#get all tests in the folder
	folder=$TestingFolder"/"$Transaction_Folders
	for Test_Folders in $(ls $folder)
	do
		#create the bank transaction file
		touch $banktransactionfile
		Active_Test=$folder"/"$Test_Folders

		#run the program with the bank accounts file, the bank transation file
		# and the testing file as arguments
		./$program $bankaccountfile $banktransactionfile $Active_Test"/test.txt" > CommandLineResult.txt
		
		#use status variable to check if Test_Folders pass
		status=""
		echo $Test_Folders "Testing: Started" >> log.txt
		
		#diff the Bank transaction file and the Test's results 
		#output to the log file the results
		filediff=$(diff $banktransactionfile $Active_Test"/result.txt");
		if [ "$filediff" == "" ]; then
			echo -e "\t"$Test_Folders "Result: Success" >> log.txt
		else
			#log that it failed and the result so the diff file. also add
			#to status that on of the output failed
			echo -e "\t"$Test_Folders "Result: Failure" >> log.txt
			echo -e "\t"$filediff >> log.txt
			status="Fail"
		fi

		#diff the command int output and the Test's commandline results
		#output to the log file the results
		filediff=$(diff CommandLineResult.txt $Active_Test"/commandlineResult.txt");
		if [ "$filediff" == "" ]; then
			echo -e "\t"$Test_Folders "Command Line Result: Success" >> log.txt
		else
			#log that it failed and the result so the diff file. also add
			#to status that on of the output failed
			echo -e "\t"$Test_Folders "Command Line Result: Failure" >> log.txt
			echo -e "\t"$filediff >> log.txt
			status="Fail"
		fi
		echo $Test_Folders "Testing: Complete" >> log.txt
		echo "" >> log.txt
		
		#remove a dummy file showing the results of the previous test 
		rm $Active_Test"/Result/"*.test

		#show the results of the test and create the appropriate file to
		# show the result of the test
		if [ "$status" == "" ]; then
			echo -e "\e[32m  "$Transaction_Folders": "$Test_Folders "Test - Success" 
			touch $Active_Test"/Result/"Success.test
		else
			echo -e "\e[31m  "$Transaction_Folders": "$Test_Folders "Test - Failure"
			touch $Active_Test"/Result/"Failure.test	
		fi

		#move the bank transaction file and the command line result to the Result folder
		mv $banktransactionfile $Active_Test"/Result/"$banktransactionfile
		mv CommandLineResult.txt $Active_Test"/Result/"CommandLineResult.txt
	done
done

#calculate the time it took to run the result, and display it
end=$(date +%s%N)
result=$(((end-start)/1000000))
echo -e "\e[39mTime to Complete: " $result "ms"

#write the results to the log file
echo "Time to Complete: " $result "ms" >> log.txt

#if the there was a specific Transaction tested, include that Transaction
# name in the log file name
#log file name include the date and time of when the test is run
if [ "$TransactionFolder" == "" ]; then
	mv log.txt Logs/"log_All_"$date".log"	
else
	mv log.txt Logs/"log_"$TransactionFolder"_"$date".log"
fi
echo Done