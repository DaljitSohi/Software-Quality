#!/bin/bash
program="$1"
accountfile="$2"
outputfile="$3"
tfolder="$4"

if [ "$5" == "" ]; then
	transFolder=""
else
	transFolder="$5"
fi
start=$(date +%s%N)

date=$(date +"%m-%d-%y-%T")
echo Start
echo "" > log.txt
rm logChart.txt
for folder_name in $(ls $tfolder | grep "$transFolder");
do
	folder=$tfolder"/"$folder_name
	for tests in $(ls $folder)
	do
		touch $outputfile
		testfolder=$folder"/"$tests
		./$program $accountfile $outputfile $testfolder"/test.txt" > resultt.txt
		
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
		
		
		# rm $testfolder"/Result/"$outputfile
		# rm $testfolder"/Result/"resultt.txt

		if [ "$status" == "" ]; then
			echo -e "\e[32m  "$folder_name": "$tests "Test - Success" 
			echo -e $tests"\tWhatTestis\tSuccess\t\t\t"  >> logChart.txt
		else
			echo -e "\e[31m  "$folder_name": "$tests "Test - Failure"
			echo -e $tests"\tWhatTestis\tFailure\thow it fail\twhat error\thow fixed it"  >> logChart.txt
			
		fi
		mv $outputfile $testfolder"/Result/"$outputfile
		mv resultt.txt $testfolder"/Result/"resultt.txt
		# mkdir $testfolder"/Result"
		
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