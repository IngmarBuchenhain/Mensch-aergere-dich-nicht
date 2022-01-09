#include<vector>

#include "CppClassBoard.hpp"


/** *************************************
 * Constructors of Board                *
 * *************************************/

Board::Board(){
        numberOfWalkingFields = 40;
        numberOfHomes = 4;

        IJumpPair_SPTR firstPair(new JumpPair(5, 25));
        jumpFields.push_back(firstPair);
         // jumpFields.push_back(std::make_shared<IJumpPair>(15,35));
        
        startFields.push_back(1);
        startFields.push_back(11);
        startFields.push_back(21);
        startFields.push_back(31);
        
        endFields.push_back(39);
        endFields.push_back(9);
        endFields.push_back(19);
        endFields.push_back(29);

        // Create game pieces
        
        for(int playerNumber = 0; playerNumber < 4; playerNumber++){
            std::vector<IGamePiece_SPTR> team;
            for(int pieceNumber = 0; pieceNumber < 4; pieceNumber++){
                IGamePiece_SPTR piece(new GamePiece);
                team.push_back(piece);
            }
            teamsAndGamePieces.push_back(team);
        }
    }

    Board::Board(bool bigField, int numberOfPlayers, int numberOfPieces, bool spreadOnBoard){
                    if(numberOfPlayers > 4 || numberOfPieces > 4 || numberOfPieces < 3 || numberOfPlayers < 2){
                // Exception
            }
        if(bigField){
numberOfWalkingFields = 48;
        numberOfHomes = 6;


        //         jumpFields.push_back(std::make_shared<IJumpPair>(4,28));
        //   jumpFields.push_back(std::make_shared<IJumpPair>(12,36));
        //       jumpFields.push_back(std::make_shared<IJumpPair>(20,44));

        if(numberOfPlayers < 6 && spreadOnBoard) {
            if(numberOfPlayers == 2){
        startFields.push_back(1);
        startFields.push_back(25);

        
        endFields.push_back(48);
        endFields.push_back(24);

            } else if(numberOfPlayers == 3){
                        startFields.push_back(1);
        startFields.push_back(17);
              startFields.push_back(33);

        
        endFields.push_back(48);
        endFields.push_back(16);
        endFields.push_back(32);
            }
        } else{
        startFields.push_back(1);
        startFields.push_back(9);
        startFields.push_back(17);
        startFields.push_back(25);
                startFields.push_back(33);
        startFields.push_back(41);
        
        endFields.push_back(48);
        endFields.push_back(8);
        endFields.push_back(16);
        endFields.push_back(24);
                endFields.push_back(32);
        endFields.push_back(40);
        }
        

        } else {
numberOfWalkingFields = 40;
        numberOfHomes = 4;

        // jumpFields.push_back(std::make_shared<IJumpPair>(5,25));
        //   jumpFields.push_back(std::make_shared<IJumpPair>(15,35));
   if(numberOfPlayers == 2 && spreadOnBoard) {
         
        startFields.push_back(1);
        startFields.push_back(21);

        
        endFields.push_back(40);
        endFields.push_back(20);

           
        } else{
        startFields.push_back(1);
        startFields.push_back(11);
        startFields.push_back(21);
        startFields.push_back(31);
        
        endFields.push_back(40);
        endFields.push_back(10);
        endFields.push_back(20);
        endFields.push_back(30);
        }
        

        }
                

        // Create game pieces
        
        for(int playerNumber = 0; playerNumber < numberOfPlayers; playerNumber++){
            std::vector<IGamePiece_SPTR> team;
            for(int pieceNumber = 0; pieceNumber < numberOfPieces; pieceNumber++){
                IGamePiece_SPTR piece(new GamePiece);
                team.push_back(piece);
            }
            teamsAndGamePieces.push_back(team);
        }
    }


/** *************************************
 * Public methods of Board              *
 * *************************************/


std::vector<IGamePiece_SPTR> Board::getTeam(int player) {
    
    return teamsAndGamePieces[player];
}



    int Board::getNumberOfFields() {
        return numberOfWalkingFields;
    }


int Board::getNumberOfPlayers(){
    return teamsAndGamePieces.size();
}


    int Board::getNumberOfGamePiecesPerPlayer(){
        return teamsAndGamePieces[0].size();
    }


     int Board::getNumberOfHomes(){
         return numberOfHomes;
     } 

   std::vector<int> Board::getStartfields(){
       return startFields;
   }

   std::vector<int> Board::getEndFields(){
       return endFields;
   }
 
    std::vector<IJumpPair_SPTR> Board::getJumpFields(){
        return jumpFields;
    }


     std::vector<std::vector<IGamePieceUI_SPTR>> Board::getGamePieces(){
         std::vector<std::vector<IGamePieceUI_SPTR>> result;
         
        for(int index = 0; index < teamsAndGamePieces.size(); index++){
            std::vector<IGamePieceUI_SPTR> team;
            for(int i = 0; i < teamsAndGamePieces[index].size(); i++){
                team.push_back(teamsAndGamePieces[index][i]);
            }
            result.push_back(team);
        }

         return result;
     }

 


     std::vector<IGamePiece_SPTR> Board::getTargetAreaTeam(int player){
         std::vector<IGamePiece_SPTR> team = teamsAndGamePieces[player];
         std::vector<IGamePiece_SPTR> targetTeam;

         for(int index = 0; index < team.size(); index++){
             if(team[index]->isInTargetArea()){
                 targetTeam.push_back(team[index]);
             }
         }

         return targetTeam;
     }

  
     std::vector<IGamePiece_SPTR> Board::getHomeAreaTeam(int player){
          std::vector<IGamePiece_SPTR> team = teamsAndGamePieces[player];
         std::vector<IGamePiece_SPTR> homeTeam;

         for(int index = 0; index < team.size(); index++){
             if(team[index]->getPosition() == 0){
                 homeTeam.push_back(team[index]);
             }
         }

         return homeTeam;
     }

     std::vector<IGamePiece_SPTR> Board::getOutsideTeam(int player){
         std::vector<IGamePiece_SPTR> team = teamsAndGamePieces[player];
         std::vector<IGamePiece_SPTR> outsideTeam;
         for(int index = 0; index < team.size(); index++){
             if(team[index]->getPosition() != 0 && !team[index]->isInTargetArea()){
                 outsideTeam.push_back(team[index]);
             }
         }
         return outsideTeam;
     }

/** *************************************
 * Private methods of Board             *
 * *************************************/



