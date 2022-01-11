#include "CppClassRuleSet.hpp"

/**
* Default rules constructor.
* Everything is set to 'false'.
*/
RuleSet::RuleSet()
{
    mustThrowOtherPiecesIntern = false;
    mustThrowOwnPiecesIntern = false;
    throwAlsoBackwardsIntern = false;

    jumpOverPiecesInTargetAreaIntern = false;
    walkByTargetAreaIfNotPossibleToWalkInIntern = false;

    saveOnStartFieldIntern = false;
    mustAlwaysFreeStartFieldIntern = false;
    allowedToUseOutsidePieceOnSixWhenPiecesLeftHomeIntern = false;

    onlyRollThreeTimesIfNoPieceOutAndTargetAreaOnEndIntern = false;

    jumpOnEdgesIntern = false;

    goWithAnotherPieceOnSecondRollOfDiceIntern = false;

    playUntilAllPlayersFinishedIntern = false;
}

/**
* Individual constructor. 
* Special rules are possible. Some combinations may not be sensible.
*/
RuleSet::RuleSet(bool mustThrowOtherPieces, bool mustThrowOwnPieces, bool throwAlsoBackwards, bool jumpOverPiecesInTargetArea, bool walkByTargetAreaIfNotPossibleToWalkIn, bool saveOnStartField, bool mustAlwaysFreeStartField, bool allowedToUseOutsidePieceOnSixWhenPiecesLeftHome, bool onlyRollThreeTimesIfNoPieceOutAndTargetAreaOnEnd, bool jumpOnEdges, bool goWithAnotherPieceOnSecondRollOfDice, bool playUntilAllPlayersFinished)
{
    mustThrowOtherPiecesIntern = mustThrowOtherPieces;
    mustThrowOwnPiecesIntern = mustThrowOwnPieces;
    throwAlsoBackwardsIntern = throwAlsoBackwards;

    jumpOverPiecesInTargetAreaIntern = jumpOverPiecesInTargetArea;
    walkByTargetAreaIfNotPossibleToWalkInIntern = walkByTargetAreaIfNotPossibleToWalkIn;

    saveOnStartFieldIntern = saveOnStartField;
    mustAlwaysFreeStartFieldIntern = mustAlwaysFreeStartField;
    allowedToUseOutsidePieceOnSixWhenPiecesLeftHomeIntern = allowedToUseOutsidePieceOnSixWhenPiecesLeftHome;

    onlyRollThreeTimesIfNoPieceOutAndTargetAreaOnEndIntern = onlyRollThreeTimesIfNoPieceOutAndTargetAreaOnEnd;

    jumpOnEdgesIntern = jumpOnEdges;

    goWithAnotherPieceOnSecondRollOfDiceIntern = goWithAnotherPieceOnSecondRollOfDice;

    playUntilAllPlayersFinishedIntern = playUntilAllPlayersFinished;
}

// Public methods for reading the values of the rule set.
bool RuleSet::mustThrowOtherPieces()
{
    return mustThrowOtherPiecesIntern;
}

bool RuleSet::mustThrowOwnPieces()
{
    return mustThrowOwnPiecesIntern;
}

bool RuleSet::throwAlsoBackwards()
{
    return throwAlsoBackwardsIntern;
}

bool RuleSet::jumpOverPiecesInTargetArea()
{
    return jumpOverPiecesInTargetAreaIntern;
}

bool RuleSet::walkByTargetAreaIfNotPossibleToWalkIn()
{
    return walkByTargetAreaIfNotPossibleToWalkInIntern;
}

bool RuleSet::saveOnStartField()
{
    return saveOnStartFieldIntern;
}

bool RuleSet::mustAlwaysFreeStartField()
{
    return mustAlwaysFreeStartFieldIntern;
}

bool RuleSet::allowedToUseOutsidePieceOnSixWhenPiecesLeftHome()
{
    return allowedToUseOutsidePieceOnSixWhenPiecesLeftHomeIntern;
}

bool RuleSet::onlyRollThreeTimesIfNoPieceOutAndTargetAreaOnEnd()
{
    return onlyRollThreeTimesIfNoPieceOutAndTargetAreaOnEndIntern;
}

bool RuleSet::jumpOnEdges()
{
    return jumpOnEdgesIntern;
}

bool RuleSet::goWithAnotherPieceOnSecondRollOfDice()
{
    return goWithAnotherPieceOnSecondRollOfDiceIntern;
}

bool RuleSet::playUntilAllPlayersFinished()
{
    return playUntilAllPlayersFinishedIntern;
}