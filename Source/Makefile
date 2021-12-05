MenschAergereDichNicht.out: CppMenschAergereDichNicht.o CppDebugHelper.o
	g++ -std=c++11 -o MenschAergereDichNicht.out CppMenschAergereDichNicht.o CppDebugHelper.o
CppMenschAergereDichNicht.o: CppMenschAergereDichNicht.cpp 
	g++ -std=c++11 -o CppMenschAergereDichNicht.o -c CppMenschAergereDichNicht.cpp
CppDebugHelper.o: CppDebugHelper.cpp
	g++ -std=c++11 -o CppDebugHelper.o -c CppDebugHelper.cpp
run: MenschAergereDichNicht.out
	./MenschAergereDichNicht.out
clean:
	rm *.out *.o