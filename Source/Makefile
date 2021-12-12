# Define boost path. SET this variable from environment when running make to provide your path to boost!
boost ?= /Users/Ingmar/VisualStudioCode/Boost/boost_1_78_0
# Define boost path for library linking. SET this variable from environment when running make to provide your path to boost!
boostlib ?= /Users/Ingmar/VisualStudioCode/Boost/boost_1_78_0/stage/lib

# Define output path. If not given from outside just working directory
outpath ?= 

# Define compiler include paths commands. ! May be wrong use fo CXXFLAGS !
CXXFLAGS = '-I$(boost) -L$(boostlib)'

# Define c++ version
lv = -std=c++11

# Define sub-directories to look for files. Can be easily renamed then. # ifs = Interfaces, lo = Logic, mo = Model, net = Networking, ui = UI
ifs = Interfaces
lo = Logic
mo = Model
net = Networking
ui = UI

# Define compiler include paths command for final linking
carg = $(lv) -I $(ifs)

# Define executable file name to be able to rename easily.
exeName = maedn

# Linking
$(outpath)$(exeName): CppMenschAergereDichNicht.o CppDebugHelper.o CppClassMainLogic.o
	g++ $(lv) -o $(outpath)$(exeName) CppMenschAergereDichNicht.o CppDebugHelper.o CppClassMainLogic.o

# Source
CppMenschAergereDichNicht.o: CppMenschAergereDichNicht.cpp 
	g++ $(carg) -o CppMenschAergereDichNicht.o -c CppMenschAergereDichNicht.cpp

CppDebugHelper.o: CppDebugHelper.cpp
	g++ $(lv) -o CppDebugHelper.o -c CppDebugHelper.cpp

# Logic
CppClassMainLogic.o: $(lo)/CppClassMainLogic.cpp
	g++ $(carg) -o CppClassMainLogic.o -c $(lo)/CppClassMainLogic.cpp

# Model

# Networking

# UI

# make
run: $(outpath)$(exeName)
	./$(outpath)$(exeName)
mostlyclean:
	rm -f *.o
clean:
	rm -f *.exe *.out *.o $(exeName) ../$(exeName) $(outpath)$(exeName)