# Define output path. If not given from outside just working directory
outpath ?= 

# Define c++ version
lv = -std=c++17

# Define sub-directories to look for files. Can be easily renamed then.
ifs = Interfaces
lo = Logic
mo = Model
ui = UI
sc = ../Source

# Define compiler command with version and include paths
build = g++ $(lv) -I $(ifs) -I $(sc) -I $(mo) -I $(lo) -I $(ui)
link = g++ $(lv)

# Define executable file name to be able to rename easily.
exeName = maedn

# Linking
$(outpath)$(exeName): CppMenschAergereDichNicht.o CppDebugHelper.o CppExportImport.o CppClassMainLogicBase.o CppClassMainLogicDefault.o CppClassMainLogicEasy.o CppClassMainLogicHard.o CppClassDice.o CppClassBoard.o CppClassGamePiece.o CppClassStatistics.o CppClassJumpPair.o CppClassRuleSet.o CppClassKI.o CppClassMainUI.o CppClassMainUILarge.o
	$(link) -o $(outpath)$(exeName) CppMenschAergereDichNicht.o CppDebugHelper.o CppExportImport.o CppClassMainLogicBase.o CppClassMainLogicDefault.o CppClassMainLogicEasy.o CppClassMainLogicHard.o CppClassDice.o CppClassBoard.o CppClassGamePiece.o CppClassStatistics.o CppClassJumpPair.o CppClassRuleSet.o CppClassKI.o CppClassMainUI.o CppClassMainUILarge.o

# Source
CppMenschAergereDichNicht.o: CppMenschAergereDichNicht.cpp 
	$(build) -c CppMenschAergereDichNicht.cpp

CppDebugHelper.o: CppDebugHelper.cpp
	$(build) -c CppDebugHelper.cpp

CppExportImport.o: CppExportImport.cpp
	$(build) -c CppExportImport.cpp

# Logic
CppClassMainLogicBase.o: $(lo)/CppClassMainLogicBase.cpp
	$(build) -c $(lo)/CppClassMainLogicBase.cpp
CppClassMainLogicDefault.o: $(lo)/CppClassMainLogicDefault.cpp
	$(build) -c $(lo)/CppClassMainLogicDefault.cpp
CppClassMainLogicHard.o: $(lo)/CppClassMainLogicHard.cpp
	$(build) -c $(lo)/CppClassMainLogicHard.cpp
CppClassMainLogicEasy.o: $(lo)/CppClassMainLogicEasy.cpp
	$(build) -c $(lo)/CppClassMainLogicEasy.cpp
CppClassDice.o: $(lo)/CppClassDice.cpp
	$(build) -c $(lo)/CppClassDice.cpp
CppClassKI.o: $(lo)/CppClassKI.cpp
	$(build) -c $(lo)/CppClassKI.cpp

# Model
CppClassBoard.o: $(mo)/CppClassBoard.cpp
	$(build) -c $(mo)/CppClassBoard.cpp
CppClassGamePiece.o: $(mo)/CppClassGamePiece.cpp
	$(build) -c $(mo)/CppClassGamePiece.cpp
CppClassJumpPair.o: $(mo)/CppClassJumpPair.cpp
	$(build) -c $(mo)/CppClassJumpPair.cpp
CppClassRuleSet.o: $(mo)/CppClassRuleSet.cpp
	$(build) -c $(mo)/CppClassRuleSet.cpp
CppClassStatistics.o: $(mo)/CppClassStatistics.cpp
	$(build) -c $(mo)/CppClassStatistics.cpp

# UI
CppClassMainUI.o: $(ui)/CppClassMainUI.cpp
	$(build) -c $(ui)/CppClassMainUI.cpp
CppClassMainUILarge.o: $(ui)/CppClassMainUILarge.cpp
	$(build) -c $(ui)/CppClassMainUILarge.cpp

# make
run: $(outpath)$(exeName) mostlyclean
	./$(outpath)$(exeName) 4 3 4 0 1 0 Torsten Ingmar Niklas
mostlyclean:
	rm -f *.o a.out $(mo)/*.o $(lo)/*.o $(ui)/*.o $(ifs)/*.o $(mo)/*.out $(lo)/*.out $(ui)/*.out $(ifs)/*.out
clean: mostlyclean
	rm -f *.exe *.out $(exeName) ../$(exeName) $(outpath)$(exeName)