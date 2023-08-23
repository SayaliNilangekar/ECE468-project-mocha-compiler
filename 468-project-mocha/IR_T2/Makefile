compiler: 
	mkdir -p generated
	mkdir -p build
	flex -o generated/scanner.cpp src/scanner.ll
	bison -d -o generated/parser.cpp src/parser.yy
	g++ -std=c++0x -c -o build/parser.o generated/parser.cpp -g
	g++ -std=c++0x -c -o build/scanner.o generated/scanner.cpp -g
	g++ -std=c++0x -c -o build/main.o src/main.cpp -g
	g++ -std=c++0x -c -o build/SymbolTable.o src/SymbolTable.cpp -g
	g++ -std=c++0x -o Micro build/scanner.o build/parser.o build/main.o build/SymbolTable.o -g


clean:
	rm -rf generated
	rm -rf build
	rm -f Micro

team:
	@echo "Team: Mocha"
	@echo " "
	@echo "Aishwarya Ray"
	@echo "Ray65"
	@echo " "
	@echo "Sayali Nilangekar"
	@echo "SayaliSN"
