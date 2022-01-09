# Define boost path. SET this variable from environment when running make to provide your path to boost!

boost ?= /usr/local/boost_1_78_0
# Define boost path for library linking. SET this variable from environment when running make to provide your path to boost!
#boostlib ?= /usr/local/boost_1_78_0/stage/lib


# Define output path. If not given from outside just working directory
outpath ?= 

# Define compiler include paths commands. ! May be wrong use fo CXXFLAGS !

#CXXFLAGS = '-I$(boost)# -L$(boostlib)'


# Define c++ version
lv = -std=c++14

# Define sub-directories to look for files. Can be easily renamed then. # ifs = Interfaces, lo = Logic, mo = Model, net = Networking, ui = UI
ifs = Interfaces
lo = Logic
mo = Model
net = Networking
ui = UI
sc = ../Source

# Define compiler include paths command for final linking and header include highest level
carg = $(lv) -I $(ifs) -I $(mo) -I $(lo) -I $(ui) -I $(sc) -I $(net)
# Define compiler include paths for ui building
cargUI = $(lv) -I $(ifs) -I $(sc) -I $(ui)
# Define compiler include paths for logic building
cargLO = $(lv) -I $(ifs) -I $(sc) -I $(mo) -I $(lo)

# Define executable file name to be able to rename easily.
exeName = maedn

# Linking
$(outpath)$(exeName): CppMenschAergereDichNicht.o CppDebugHelper.o CppExportImport.o CppClassMainLogicBase.o CppClassMainLogicDefault.o CppClassMainLogicEasy.o CppClassMainLogicHard.o CppClassDice.o CppClassBoard.o CppClassGamePiece.o CppClassStatistics.o CppClassJumpPair.o CppClassRuleSet.o CppClassKI.o
	g++ $(lv) -o $(outpath)$(exeName) CppMenschAergereDichNicht.o CppDebugHelper.o CppExportImport.o CppClassMainLogicBase.o CppClassMainLogicDefault.o CppClassMainLogicEasy.o CppClassMainLogicHard.o CppClassDice.o CppClassBoard.o CppClassGamePiece.o CppClassStatistics.o CppClassJumpPair.o CppClassRuleSet.o CppClassKI.o
	rm -f *.o
# Source
CppMenschAergereDichNicht.o: CppMenschAergereDichNicht.cpp 
	g++ $(carg) -o CppMenschAergereDichNicht.o -c CppMenschAergereDichNicht.cpp

CppDebugHelper.o: CppDebugHelper.cpp
	g++ $(lv) -o CppDebugHelper.o -c CppDebugHelper.cpp

CppExportImport.o: CppExportImport.cpp
	g++ $(carg) -o CppExportImport.o -c CppExportImport.cpp

# Logic
CppClassMainLogicBase.o: $(lo)/CppClassMainLogicBase.cpp
	g++ $(carg) -o CppClassMainLogicBase.o -c $(lo)/CppClassMainLogicBase.cpp
CppClassMainLogicDefault.o: $(lo)/CppClassMainLogicDefault.cpp
	g++ $(carg) -o CppClassMainLogicDefault.o -c $(lo)/CppClassMainLogicDefault.cpp
CppClassMainLogicHard.o: $(lo)/CppClassMainLogicHard.cpp
	g++ $(carg) -o CppClassMainLogicHard.o -c $(lo)/CppClassMainLogicHard.cpp
CppClassMainLogicEasy.o: $(lo)/CppClassMainLogicEasy.cpp
	g++ $(carg) -o CppClassMainLogicEasy.o -c $(lo)/CppClassMainLogicEasy.cpp
CppClassDice.o: $(lo)/CppClassDice.cpp
	g++ $(carg) -o CppClassDice.o -c $(lo)/CppClassDice.cpp
CppClassKI.o: $(lo)/CppClassKI.cpp
	g++ $(carg) -o CppClassKI.o -c $(lo)/CppClassKI.cpp

# Model
CppClassBoard.o: $(mo)/CppClassBoard.cpp
	g++ $(cargLO) -o CppClassBoard.o -c $(mo)/CppClassBoard.cpp
CppClassGamePiece.o: $(mo)/CppClassGamePiece.cpp
	g++ $(cargLO) -o CppClassGamePiece.o -c $(mo)/CppClassGamePiece.cpp
CppClassJumpPair.o: $(mo)/CppClassJumpPair.cpp
	g++ $(cargLO) -o CppClassJumpPair.o -c $(mo)/CppClassJumpPair.cpp
CppClassRuleSet.o: $(mo)/CppClassRuleSet.cpp
	g++ $(cargLO) -o CppClassRuleSet.o -c $(mo)/CppClassRuleSet.cpp
CppClassStatistics.o: $(mo)/CppClassStatistics.cpp
	g++ $(cargLO) -o CppClassStatistics.o -c $(mo)/CppClassStatistics.cpp
#CppStructsForConfigAndState.o: $(mo)/CppStructsForConfigAndState.hpp
#	g++ $(cargLO) -o CppStructsForConfigAndState.o -c $(mo)/CppStructsForConfigAndState.hpp


# Networking

# UI

# Test compiling only
testc: CppMenschAergereDichNicht.o CppDebugHelper.o CppClassDice.o CppClassBoard.o CppClassGamePiece.o CppClassJumpPair.o CppClassRuleSet.o CppClassMainLogic.o
# Test all compiling
testAll: CppMenschAergereDichNicht.cpp CppDebugHelper.cpp $(lo)/CppClassDice.cpp $(mo)/CppClassBoard.o $(mo)/CppClassGamePiece.o $(mo)/CppClassJumpPair.o $(mo)/CppClassRuleSet.o $(lo)/CppClassMainLogic.o
	g++ $(carg) -o testAll CppMenschAergereDichNicht.cpp CppDebugHelper.cpp $(lo)/CppClassDice.cpp $(mo)/CppClassBoard.o $(mo)/CppClassGamePiece.o $(mo)/CppClassJumpPair.o $(mo)/CppClassRuleSet.o $(lo)/CppClassMainLogic.o
# make
run: $(outpath)$(exeName)
	./$(outpath)$(exeName) 4 3 4 0 1 0 Torsten Niklas Ingmar
mostlyclean:
	rm -f *.o a.out $(mo)/*.o $(lo)/*.o $(ui)/*.o $(ifs)/*.o $(net)/*.o $(mo)/*.out $(lo)/*.out $(ui)/*.out $(ifs)/*.out $(net)/*.out
clean:
	rm -f *.exe *.out *.o $(exeName) ../$(exeName) $(outpath)$(exeName) $(mo)/*.o $(lo)/*.o $(ui)/*.o $(ifs)/*.o $(net)/*.o $(mo)/*.out $(lo)/*.out $(ui)/*.out $(ifs)/*.out $(net)/*.out