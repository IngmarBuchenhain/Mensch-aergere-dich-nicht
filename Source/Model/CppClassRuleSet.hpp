#ifndef MAEDN_RULE_SET_HPP
#define MAEDN_RULE_SET_HPP

#include<memory>

/**
 * Representation of the rules of a maedn-game. An object of this class is read-only, as it has only private properties describing the rules.
 * Rules are configured on instantiation.
 * Default constructor for default rules (All properties are 'false').
 * 
 */
class RuleSet
{
    // Different rule properties. Must be 'false' for default rule set!
    bool mustThrowOtherPiecesIntern;
    bool mustThrowOwnPiecesIntern;
    bool throwAlsoBackwardsIntern;

    bool jumpOverPiecesInTargetAreaIntern;
    bool walkByTargetAreaIfNotPossibleToWalkInIntern;

    bool saveOnStartFieldIntern;
    bool mustAlwaysFreeStartFieldIntern; 
    bool allowedToUseOutsidePieceOnSixWhenPiecesLeftHomeIntern;

    bool onlyRollThreeTimesIfNoPieceOutAndTargetAreaOnEndIntern;

    bool jumpOnEdgesIntern;

    bool goWithAnotherPieceOnSecondRollOfDiceIntern;

    bool playUntilAllPlayersFinishedIntern;

public:
    /**
    * Default rules constructor.
    * Everything is set to 'false'.
    */
    RuleSet();

public:
    /**
    * Individual constructor. 
    * Special rules are possible. Some combinations may not be sensible.
    */
    RuleSet(bool mustThrowOtherPieces, bool mustThrowOwnPieces, bool throwAlsoBackwards, bool jumpOverPiecesInTargetArea, bool walkByTargetAreaIfNotPossibleToWalkIn, bool saveOnStartField, bool mustAlwaysFreeStartField, bool allowedToUseOutsidePieceOnSixWhenPiecesLeftHome, bool onlyRollThreeTimesIfNoPieceOutAndTargetAreaOnEnd, bool jumpOnEdges, bool goWithAnotherPieceOnSecondRollOfDice, bool playUntilAllPlayersFinished);

    // Public methods for reading the values of the rule set.
public:
    bool mustThrowOtherPieces();

public:
    bool mustThrowOwnPieces();

public:
    bool throwAlsoBackwards();

public:
    bool jumpOverPiecesInTargetArea();

public:
    bool walkByTargetAreaIfNotPossibleToWalkIn();

public:
    bool saveOnStartField();

public:
    bool mustAlwaysFreeStartField();

public:
    bool allowedToUseOutsidePieceOnSixWhenPiecesLeftHome();

public:
    bool onlyRollThreeTimesIfNoPieceOutAndTargetAreaOnEnd();

public:
    bool jumpOnEdges();

public:
    bool goWithAnotherPieceOnSecondRollOfDice();
public:
    bool playUntilAllPlayersFinished();
};

typedef std::unique_ptr<RuleSet> RuleSet_UPTR;

#endif