run:
	clear
	g++ main.cpp -o main
	./main
clean:
	rm main *.txt

testing: run
	./testing.sh main batf.txt Tests

CreateTest: run
	./testing.sh main batf.txt Tests Create