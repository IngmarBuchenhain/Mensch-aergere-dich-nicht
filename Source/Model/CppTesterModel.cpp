#include "CppClassRuleSet.hpp"
#include "CppClassGamePiece.hpp"
#include "CppClassBoard.hpp"
#include "CppIJumpPair.hpp"
#include<iostream>

void printRules(RuleSet &rules){
    std::cout << rules.allowedToUseOutsidePieceOnSixWhenPiecesLeftHome();
    std::cout << rules.goWithAnotherPieceOnSecondRollOfDice();
    std::cout << rules.jumpOnEdges();
    std::cout << rules.jumpOverPiecesInTargetArea();
    std::cout << rules.mustAlwaysFreeStartField();
    std::cout << rules.mustThrowOtherPieces();
    std::cout << rules.mustThrowOwnPieces();
    std::cout << rules.onlyRollThreeTimesIfNoPieceOutAndTargetAreaOnEnd();
    std::cout << rules.playUntilAllPlayersFinished();
    std::cout << rules.saveOnStartField();
    std::cout << rules.throwAlsoBackwards();
    std::cout << rules.walkByTargetAreaIfNotPossibleToWalkIn();
    std::cout << std::endl;
}

int main(){
    // Test RuleSet
    RuleSet set1;
    RuleSet set2(false, true, false, true, false, true, false, true, false, true, false, true);

    RuleSet_UPTR set3(new RuleSet);
     RuleSet_UPTR set4(new RuleSet(true, true, false, true, false, true, false, true, false, true, false, true));
    printRules(set2);
    std::cout << set4->mustThrowOtherPieces() << std::endl;

     IGamePiece_SPTR p1(new GamePiece);
    IGamePiece_SPTR p2(new GamePiece);
    std::cout << p1->getPosition() << p1->isFinished() << p1->isInTargetArea();

    IJumpPair_SPTR j1(new JumpPair(2,3));
    std::cout << std::endl << j1->getFirst() << " " << j1->getSecond() << " " << j1->getPartnerOrNegative(2) << " " << j1->getPartnerOrNegative(3) << " " << j1->getPartnerOrNegative(4) << std::endl;

IBoard_SPTR board(new Board);
std::vector<int> testEnd = board->getEndFields();
for(int i = 0; i< testEnd.size(); i++){
    std::cout << std::endl << testEnd[i];
}

std::vector<std::vector<IGamePieceUI_SPTR>> pieces = board->getGamePieces();
}