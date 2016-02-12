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
			echo $(tput setaf 2)"  "$folder_name": "$tests "Test - Success" 
		else
			echo $(tput setaf 1)"  "$folder_name": "$tests "Test - Failure" 
		fi
	done
done

end=$(date +%s%N)
result=$(((end-start)/1000000))
echo $(tput setaf 7)"Time to Complete: " $result "ms"

echo "Time to Complete: " $result "ms" >> log.txt
mv log.txt Logs/"log_"$date".log"
echo Done