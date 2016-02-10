#!/bin/bash
program="$1"
outputfile="$2"
tfolder="$3"
echo Start
echo $tfolder > log.txt
for folder_name in $(ls $tfolder);
do
	folder=$tfolder"/"$folder_name
	for tests in $(ls $folder)
	do
		testfolder=$folder"/"$tests
		./$program $testfolder"/test.txt" > resultt.txt
		filediff=$(diff $outputfile $testfolder"/result.txt");
		filedifff=$(diff resultt.txt $testfolder"/Cresult.txt");

		if [ "$filediff" == "" ]; then
			if [ "$filedifff" == "" ]; then
				echo $(tput setaf 2)-e"\t"$tests "Test: Success" 
			else
				echo $(tput setaf 1)-e"\t"$tests "Test: Failure"
				echo $tests "Testing: Started" >> log.txt
				echo $tests "result.txt: Success" >> log.txt
				echo $tests "Cresult.txt: Failure" >> log.txt
				echo $filedifff >> log.txt
				echo $tests "Testing: Complete" >> log.txt
			fi
		else
			echo $(tput setaf 1)-e "\t"$tests "Test: Failure"
			echo $tests "Testing: Started" >> log.txt
			echo $tests "result.txt: Failure" >> log.txt
			echo $tests "Cresult.txt: Unknown" >> log.txt
			echo $filediff >> log.txt
			echo $filedifff >> log.txt
			echo $tests "Testing: Complete" >> log.txt
		fi
	done
done
echo $(tput setaf 7)Done


# for file_name in $( ls -d */ | grep -v login );
# 	do
# 		$program $file_name"/test.txt" > resultt.txt
# 		filediff=$(diff $outputfile $file_name"/result.txt");
# 		filedifff=$(diff resultt.txt $file_name"/resultC.txt");

# 		if [ "$filediff" == "" ];then
# 			echo $file_name "Test: Success" 
# 		else
# 			echo $file_name "Test: Failure" 
# 			echo $filediff >> log.txt
# 		fi
# 	done





# for file_name in $( ls | grep login );
# 	do
# 		$program $file_name"/test.txt"  > resultt.txt
# 		filediff=$(diff $outputfile $file_name"/result.txt");

# 		if [ "$filediff" == "" ];then
# 			echo $file_name "Test: Success" 
# 		else
# 			echo $file_name "Test: Failure" 
# 			echo $filediff >> log.txt
# 		fi
# 	done

# for file_name in $( ls -d */ | grep -v login );
# 	do
# 		$program $file_name"/test.txt" > resultt.txt
# 		filediff=$(diff $outputfile $file_name"/result.txt");
# 		filedifff=$(diff resultt.txt $file_name"/resultC.txt");

# 		if [ "$filediff" == "" ];then
# 			echo $file_name "Test: Success" 
# 		else
# 			echo $file_name "Test: Failure" 
# 			echo $filediff >> log.txt
# 		fi
# 	done
