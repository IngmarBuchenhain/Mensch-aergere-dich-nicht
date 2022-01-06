#include "CppClassKI.hpp"
KI::KI(int endField, int numberFields){
    playerEndField = endField;
    numberOfFields = numberFields;
}
std::pair<IGamePiece_SPTR, std::pair<int, bool>> KI::chooseGamePiece(std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces)
{
    //std::pair<IGamePiece_SPTR, std::pair<int, bool>> result;
    // Simple "KI"
    // 1. Go into target area if possible
    // 1.1 If multiple possible, take nearest
    if (getBestPieceToWalkIntoTargetArea(possiblePieces))
    {
        return returnValue;
    }
    // 2. If not, walk with piece already in target area if possible
    // 2.1 If multiple possible, take furthest.
    if (getBestPieceToWalkInTargetArea(possiblePieces))
    {
        return returnValue;
    }
    // 3. If not, go from house to field if possible
    if(getPieceToWalkOnField(possiblePieces)){
        return returnValue;
    }
    // 4. If not, walk with piece nearest to target area. If multiple possibilities always throw.
    getBestPieceToWalkOutside(possiblePieces);
        return returnValue;
    
}
int KI::getDistanceToEnd(int position){
    int distance;
    if(position <= playerEndField){
        distance = playerEndField - position;
    } else {
        distance = numberOfFields - (position - playerEndField);
    }
     return distance;
}

bool KI::getBestPieceToWalkIntoTargetArea(std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces)
{
    std::pair<IGamePiece_SPTR, std::pair<int, bool>> result;
    bool resultEmpty = true;
    std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>>::iterator it = possiblePieces.begin();

    while (it != possiblePieces.end())
    {
        std::vector<std::pair<int, bool>> valueToTest = it->second;
        for (int index = 0; index < valueToTest.size(); index++)
        {
            if (valueToTest[index].second)
            {
                if (resultEmpty)
                {
                    result.first = it->first;
                    result.second = valueToTest[index];
                    resultEmpty = false;
                }
                else if (result.second.first < valueToTest[index].first)
                {
                    result.first = it->first;
                    result.second = valueToTest[index];
                }
            }
        }
        it++;
    }
    if (!resultEmpty)
    {
        returnValue = result;
        return true;
    }
    return false;
}

bool KI::getBestPieceToWalkInTargetArea(std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces)
{
    std::pair<IGamePiece_SPTR, std::pair<int, bool>> result;
    bool resultEmpty = true;
    std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>>::iterator it = possiblePieces.begin();

    while (it != possiblePieces.end())
    {
        if (it->first->isInTargetArea())
        {
            if (resultEmpty)
            {
                result.first = it->first;
                result.second = it->second[0];
                resultEmpty = false;
            }
            else if (result.first->getPosition() < it->first->getPosition())
            {
                result.first = it->first;
                result.second = it->second[0];
            }
        }
        it++;
    }
    if (!resultEmpty)
    {
        returnValue = result;
        return true;
    }
    return false;
}

bool KI::getPieceToWalkOnField(std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces)
{
    std::pair<IGamePiece_SPTR, std::pair<int, bool>> result;
    bool resultEmpty = true;
    std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>>::iterator it = possiblePieces.begin();

    while (it != possiblePieces.end())
    {
        if (it->first->getPosition() == 0)
        {
            if (resultEmpty)
            {
                result.first = it->first;
                result.second = it->second[0];
                resultEmpty = false;
            }
            break;
        }
        it++;
    }
    if (!resultEmpty)
    {
        returnValue = result;
        return true;
    }
    return false;
}


bool KI::getBestPieceToWalkOutside(std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>> &possiblePieces)
{
    std::pair<IGamePiece_SPTR, std::pair<int, bool>> result;
    bool resultEmpty = true;
    std::map<IGamePiece_SPTR, std::vector<std::pair<int, bool>>>::iterator it = possiblePieces.begin();

    while (it != possiblePieces.end())
    {
        if (it->first->getPosition() != 0 && !(it->first->isInTargetArea()))
        {
            // Check which new position is best. Some "random" behaviour here. Take what new position is nearer to end.
            std::vector<std::pair<int, bool>> currentWalk = it->second;
            int indexOfChoosenWalk = 0;
            int tempDistance = 4200; // Magic number. Extra high to be always wrong in first try.
            for(int index = 0; index < currentWalk.size(); index++){
               if(getDistanceToEnd(currentWalk[index].first) < tempDistance){
                   tempDistance = currentWalk[index].first;
                   indexOfChoosenWalk = index;
               }
            }

            if (resultEmpty)
            {
                result.first = it->first;
                result.second = it->second[indexOfChoosenWalk];
                resultEmpty = false;
            } else{
                // Check if the current is nearer to target area. If so, take the current, even if the old one would have thrown.
                if(getDistanceToEnd(result.second.first) > tempDistance){
                    result.first = it->first;
                    result.second = it->second[indexOfChoosenWalk];
                }
            }
     
        }
        it++;
    }
    if (!resultEmpty)
    {
        returnValue = result;
        return true;
    }
    return false;
}