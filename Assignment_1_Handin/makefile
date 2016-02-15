
compile:
	g++ main.cpp -o main
	
run: compile
	./main

clean:
	rm main *.txt

testing: compile
	clear
	./testing.sh main batf.txt Tests $(ARGS)
	$(ARGS="")