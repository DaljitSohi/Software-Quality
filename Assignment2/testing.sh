#!/bin/bash
program="$1"
outputfile="$2"
tfolder="$3"

if [ "$4" == "" ]; then
	transFolder=""
else
	transFolder="$4"
fi
start=$(date +%s%N)

date=$(date +"%m-%d-%y-%T")
echo Start
echo "" > log.txt
for folder_name in $(ls $tfolder | grep "$transFolder");
do
	folder=$tfolder"/"$folder_name
	for tests in $(ls $folder)
	do
		touch BankAccountTransaction.txt
		testfolder=$folder"/"$tests
		./$program $testfolder"/test.txt" > resultt.txt
		
		status=""
		echo $tests "Testing: Started" >> log.txt
		
		filediff=$(diff $outputfile $testfolder"/result.txt");
		if [ "$filediff" == "" ]; then
			echo -e "\t"$tests "Result: Success" >> log.txt
		else
			echo -e "\t"$tests "Result: Failure" >> log.txt
			echo -e "\t"$filediff >> log.txt
			status="Fail"
		fi

		filediff=$(diff resultt.txt $testfolder"/commandlineResult.txt");
		if [ "$filediff" == "" ]; then
			echo -e "\t"$tests "Command Line Result: Success" >> log.txt
		else
			echo -e "\t"$tests "Command Line Result: Failure" >> log.txt
			echo -e "\t"$filediff >> log.txt
			status="Fail"
		fi
		echo $tests "Testing: Complete" >> log.txt
		echo "" >> log.txt

		if [ "$status" == "" ]; then
			echo -e "\e[32m  "$folder_name": "$tests "Test - Success" 
		else
			echo -e "\e[31m  "$folder_name": "$tests "Test - Failure"
		fi
		mv BankAccountTransaction.txt BankAccountTransaction2.txt
	done
done

end=$(date +%s%N)
result=$(((end-start)/1000000))
echo -e "\e[39mTime to Complete: " $result "ms"

rm Logs/*
echo "Time to Complete: " $result "ms" >> log.txt
if [ "$transFolder" == "" ]; then
	mv log.txt Logs/"log_All_"$date".log"	
else
	mv log.txt Logs/"log_"$transFolder"_"$date".log"
fi
# rm resultt.txt BankAccountTransaction.txt
echo Done