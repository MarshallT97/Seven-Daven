#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#include <string>
#include <array>
#include <locale>
using namespace std;

const int MAX = 52;
const char COLORS[4] = {'R','G','B'};

const char *rules =
"How To Play Seven Daven:\n\n"
"Attacking:\n\n"
"The person who attack during the turn is determine by their color.\n"
"This is the order on what color beats what: "
"Red(R) -> Green(G) -> Blue(B) -> Red(R)\n\n."
"Nomral damage output is determine by the card played by the attacker.\n"
"This is the card groups that will decide how much normal damage can the attacker output:\n"
"[1-6] = +1, [7] = +3, [8-13] = +2.\n\n"
"Damage Output:\n\n"
"If the attacking player card is greater then the defending player card then the attacking player damage gets a +1 of bonus damage.\n\n"
"If defending player card is greater then the attacking player card then the attacking player damage is reduced by 1 only if the defending player card - the attacking player card is greater than or equal to 3 or else the attacking player damage is normal.\n\n"
"Special Rules For 7:\n\n"
"If the attacking player plays the card 7, their damage ignore reduction.\n\n"
"If the defending player plays the card 7, the attacking player damage is reduced by 1.\n\n"
"If both players play a card 7 and do not have the same color then they both take +1 damage to health and ends the turn.\n\n"
"Matching:\n\n"
"If only both players color are the same and not the card they played, then no damage is done this turn and vice versa.\n\n"
"If both players color and card are the same then they both get +1 to health and if the card is 7 then it becomes +2 to health rather then +1.";


string myColor(char color){
  if(color == 'R'){
    return "Red";
  }
  else if(color == 'G'){
    return "Green";
  }
  else{
    return "Blue";
  }
}

void display(vector<int> hand,int size,char color,string who){
  cout << who << " Hand: ";
  for(int x = 0; x < size; x++){
    cout << hand[x] << " ";
  }
  cout << "\n" << who << " Color: " << myColor(color) << endl;
}

int attacker(char playerColor,char computerColor){
  //return 1 if player has color advantage
  //return 0 if both player and computer color are the same
  //return -1 if computer has color advantage

  if(playerColor == 'R'){
    if(computerColor == 'G'){
      return 1;
    }
    else if(computerColor == playerColor){
      return 0;
    }
    else{
      return -1;
    }
  }

  if(playerColor == 'G'){
    if(computerColor == 'B'){
      return 1;
    }
    else if(computerColor == playerColor){
      return 0;
    }
    else{
      return -1;
    }
  }

  if(playerColor == 'B'){
    if(computerColor == 'R'){
      return 1;
    }
    else if(computerColor == playerColor){
      return 0;
    }
    else{
      return -1;
    }
  }
}

int normalDMG(int cardNUM){
  if(cardNUM <= 6){
    cout << "Normal damage output is 1\n";
    return 1;
  }
  else if(cardNUM >= 8){
    cout << "Normal damage output is 2\n";
    return 2;
  }
  else{
    cout << "Normal damage output is 3\n";
    return 3;
  }
}

int finalDMG(int atker, int pCard, int cCard){
  int min = 3;
  //player attacking
  if(atker == 1){
    cout << "The player is attacking the computer!\n";
    if(pCard > cCard){
      //computer defending
      if(cCard != 7){
        cout << "Plus 1 to damage output\n";
        return normalDMG(pCard) + 1;
      }
      else{
        cout << "minus 1 to damage output\n";
        return normalDMG(pCard) - 1;
      }
    }
    else if(pCard == cCard){
      //both player and computer have same card but not color
      if(pCard == 7){
        //return -1 to handle special effect of 7
        cout << "Both players lose 1 HP\n";
        return -1;
      }
      else{
        //return 0 since they both have same number card
        cout << "No Damage was done this turn\n";
        return 0;
      }
    }
    else{
      //computer card is greater and on defense
      if(cCard - pCard >= min){
        if(pCard == 7){
          //player 7 card ignores the damage reduction
          cout << "Damage reduction was ignore\n";
          return normalDMG(pCard);
        }
        else{
          if(cCard == 7){
            cout << "-2 reduction to damage output\n";
            return 0;
          }
          else{
            cout << "Minus 1 to damage output\n";
            return normalDMG(pCard) - 1;
          }
        }
      }
      else{
        if(cCard == 7){
          //since the computer played the 7 card he reduce players damage by 1
          cout << "Minus 1 to damage output\n";
            return normalDMG(pCard) - 1;
          }
          else{
            cout << "Normal damage output\n";
            return normalDMG(pCard);
          }
      }
    }
  }
  else if(atker == -1){
    cout << "The computer is attacking the player!\n";
    if(cCard > pCard){
      //player defending
      if(pCard != 7){
        cout << "Plus 1 to damage output\n";
        return normalDMG(cCard) + 1;
      }
      else{
        cout << "minus 1 to damage output\n";
        return normalDMG(cCard) - 1;
      }
    }
    else if(cCard == pCard){
      //both player and computer have same card but not color
      if(cCard == 7){
        //return -1 to handle special effect of 7
        cout << "Both players lose 1 HP\n";
        return -1;
      }
      else{
        //return 0 since they both have same number card
        cout << "No Damage was done this turn\n";
        return 0;
      }
    }
    else{
      //player card is greater and on defense
      if(pCard - cCard >= min){
        if(cCard == 7){
          //computer 7 card ignores the damage reduction
          cout << "damage reduction was ignore\n";
          return normalDMG(cCard);
        }
        else{
          if(cCard == 7){
            cout << "-2 reduction to damage output\n";
            return 0;
          }
          else{
            cout << "Minus 1 to damage output\n";
            return normalDMG(cCard) - 1;
          }
        }
      }
      else{
        if(pCard == 7){
          //since the player played the 7 card he reduce players damage by 1
          cout << "Minus 1 to damage output\n";
            return normalDMG(cCard) - 1;
          }
          else{
            cout << "Normal damage output\n";
            return normalDMG(cCard);
          }
      }
    }
  }
  else{
    cout << "Both the player and computer have the same color!\n";
    if(pCard != cCard){
      cout << "No Damage was done this turn\n";
      return 0;
    }
    else if(pCard == 7){
      cout << "Both players gain 2 HP\n";
      return -3;
    }
    else{
      cout << "Both players gain 1 HP\n";
      return -2;
    }
  }
}

int main(){
  char playNOW;
  cout << rules << endl;
  cout << "\n\nReady to play?(type anything then enter): ";
  cin >> playNOW;

  bool main_game = true;
  while(main_game){
    vector<int> deck = {};
    vector<int> playerDeck = {};
    vector<int> computerDeck = {};
    int playerHP = 10;
    int computerHP = 10;
    int counter = 1;

    for(int x = 0; x < MAX; x++){
      if(counter % 14 == 0){
        counter = 1;
      }
      deck.push_back(counter);
      counter++;
    }

    srand(time(0));
    random_shuffle(deck.begin(),deck.end());

    //for(int x = 0; x < 10; x++){
      //cout << deck[x] << endl;
    //}

    //cout << endl;
    for(int x = 0; x < 5; x++){
      playerDeck.push_back(deck[0]);
      deck.erase(deck.begin());
      computerDeck.push_back(deck[0]);
      deck.erase(deck.begin());
    }

    bool game = true;
    int currTurn = 1;
    while(game){
      char playerColor = COLORS[rand() % 3];
      char computerColor = COLORS[rand() % 3];
      cout << "TURN " << currTurn << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
      display(playerDeck,playerDeck.size(),playerColor,"Player");
      //cout << rules << endl;

      int playerChoice;
      cout << "Enter the column number for the card you want:";
      cin >> playerChoice;
      playerChoice--;
      playerChoice = playerDeck[playerChoice];
      int computerChoice = computerDeck[rand() % computerDeck.size()];

      cout << "\nYou have chosen: " << playerChoice << endl;
      playerDeck.erase(remove(playerDeck.begin(),playerDeck.end(),playerChoice));
      //display(playerDeck,playerDeck.size(),playerColor,"Player");

      //cout << endl;

      cout << "Computer has chosen: " << computerChoice << endl;
      cout << "Computer Color: " << myColor(computerColor) << endl;
      computerDeck.erase(remove(computerDeck.begin(),computerDeck.end(),computerChoice));

      int whoATK = attacker(playerColor,computerColor);
      cout << endl;
      int atkDMG = finalDMG(whoATK,playerChoice,computerChoice);

      if(atkDMG == -1){
        playerHP--;
        computerHP--;
        cout << "\nPlayer HP: " << playerHP << endl;
        cout << "Computer HP: " << computerHP << endl;
      }
      else if(atkDMG == -2){
        playerHP++;
        computerHP++;
        cout << "\nPlayer HP: " << playerHP << endl;
        cout << "Computer HP: " << computerHP << endl;
      }
      else if(atkDMG == -3){
        playerHP += 2;
        computerHP += 2;
        cout << "\nPlayer HP: " << playerHP << endl;
        cout << "Computer HP: " << computerHP << endl;
      }
      else if(atkDMG != 0){
        if(whoATK == 1){
          cout << "\nThe Computer is hit for a total of: " << atkDMG;
          computerHP -= atkDMG;
        }
        else if(whoATK == -1){
          cout << "\nThe Player is hit for a total of: " << atkDMG;
          playerHP -= atkDMG;
        }
        cout << "\nPlayer HP: " << playerHP << endl;
        cout << "Computer HP: " << computerHP << endl;
      }
      else{
        if(whoATK == 1){
          cout << "\nThe Computer is hit for a total of: " << atkDMG;
        }
        else if(whoATK == -1){
          cout << "\nThe Player is hit for a total of: " << atkDMG;
        }
        cout << "\nPlayer HP: " << playerHP << endl;
        cout << "Computer HP: " << computerHP << endl;
      }

      if(playerDeck.size() == 0 && deck.size() != 0){
        for(int x = 0; x < 5; x++){
          playerDeck.push_back(deck[0]);
          deck.erase(deck.begin());
          computerDeck.push_back(deck[0]);
          deck.erase(deck.begin());
        }
      }

      if(playerHP <= 0){
        cout << "Winner: Computer\nLoser: Player\n";
        game = false;
      }
      if(computerHP <= 0){
        cout << "Winner: Player\nLoser: Computer\n";
        game = false;
      }
      if(computerHP <= 0 && playerHP <= 0){
        cout << "It a draw!\n";
        game = false;
      }
      if(deck.size() == 0){
        cout << "Well that all the cards in the deck.\n";
        cout << "Let see who won.\n";
        if(playerHP > computerHP){
          cout << "Looks like the player is the winner!\n";
          game = false;
        }
        else if(playerHP == computerHP){
          cout << "Looks like it a draw!\n";
          game = false;
        }
        else{
          cout << "Looks like the computer is the winner!\n";
          game = false;
        }
      }
      currTurn++;
      cout << endl;
    }
    char userANS;
    cout << "\nDo you wish to play again?(y:n): ";
    cin >> userANS;
    if(userANS == 'y' || userANS == 'Y'){
      cout << "Ok, Just let me reset the game\n\n";
    }
    else{
      cout << "Goodbye\n";
      main_game = false;
    }
  }
}
