
compile:
	g++ *.cpp *.h -o frontend

run: compile
	clear
	./frontend
clean:
	rm frontend *.txt

onetest: compile
	./frontend Tests/Create/create_admin_only/test.txt

localtext: compile
	./frontend test.tst

testing: compile
	./testing.sh frontend batf.txt Tests
