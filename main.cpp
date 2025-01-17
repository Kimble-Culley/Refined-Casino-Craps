#include <iostream>
#include <iomanip>

using namespace std;

const int min_bet = 10, max_bet = 200;

struct GameState{
    float player_balance = 500;
    float total_bet_amount = 0;
    float bet_pass = 0;
    float bet_dont_pass = 0;
    float bet_come = 0;
    float bet_dont_come = 0;
    int current_point = 0;
    bool active_game = false;
    bool active_bet = false;
    string player_choice = "0";
};

void print_menu(GameState &game);
void pre_menu();
void active_menu();
void game_logic(GameState &game);
int dice_logic();
void win_condition(GameState &game, int running_point);
bool bet_check(GameState &game);
void bet_reset(GameState &game);


int main(){
    GameState game;
    srand(time(0));

    print_menu(game);

    while(game.active_game || game.player_balance > min_bet || game.active_bet){
        cin >> game.player_choice;
        if(game.player_choice == "4"){
            break;
        }

        game_logic(game);
    }
    if(game.player_balance < min_bet){
        cout << "You've lost too much money, come back another day and try again :(" << endl;
        cout << endl;
        cout << "GAME OVER" << endl;
    }
    else{
        cout << "Come again soon :)" << endl;
        cout << endl;
        cout <<"GAME EXITED" << endl;
    }
    return 0;
}

void print_menu(GameState &game){
    if(!game.active_game){
        cout << "Off" << endl;
        }
    cout << setw(22) << "Don't" << endl;
    cout << "   Point   Come   Come" << endl;
    cout << "   =====  =====  =====" << endl;

    string points[6] = {"4","5","Six","8","Nine","10"};
    int num_points[6] = {4,5,6,8,9,10}; 

    for(int i = 0; i < 6; i++){
    if(game.current_point == num_points[i] && game.active_game){
      cout << "On" << setw(6) << points[i] << endl;
    }else{
    cout << setw(8) << points[i] << endl;
    }
  }
  cout << endl;
  cout << "Don't Come:" << game.bet_dont_come  << endl;
  cout << setw(11) << "Come:" << game.bet_come << endl;
  cout << "Don't Pass:" << game.bet_dont_pass  << endl;
  cout << setw(11) << "Pass:" << game.bet_pass << endl;
  cout << "Chips Balance: $" << game.player_balance << endl;
  cout << endl;

    if(!game.active_game && game.player_balance < min_bet && !game.active_bet){
        return;
    }
    else if(!game.active_game){
        pre_menu();
    }
    else{
        active_menu();
    }
}

void pre_menu(){
  cout << setw(12) << "Bet Menu" << endl;
  cout << "1.) Bet Pass Line" << endl;
  cout << "2.) Bet Don't Pass Line" << endl;
  cout << "3.) Roll the Dice" << endl;
  cout << "4.) Quit" << endl;
  cout << "Your Choice? ";
}

void active_menu(){
  cout << setw(12) << "Bet Menu" << endl;
  cout << "1.) Bet Come" << endl;
  cout << "2.) Bet Don't Come" << endl;
  cout << "3.) Roll the Dice" << endl;
  cout << "4.) Quit" << endl;
  cout << "Your Choice? ";
}

void game_logic(GameState &game){
    int running_point = 0;

    if(game.player_choice == "1" || game.player_choice == "2"){
        while(!bet_check(game));
    }
    else if(game.player_choice == "3"){
        if(!game.active_game){
            game.current_point = dice_logic();
        }
        else{
            running_point = dice_logic();
        }

        win_condition(game, running_point);
        print_menu(game);
    }
    else{
        cout << "Unknown option selected, please type 1,2,3, or 4 ";
    }
}

int dice_logic(){
    string diePrint[6][5] = {
        {"+-------+","|       |","|   *   |","|       |","+-------+"},
        {"+-------+","| *     |","|       |","|     * |","+-------+"},
        {"+-------+","| *     |","|   *   |","|     * |","+-------+"},
        {"+-------+","| *   * |","|       |","| *   * |","+-------+"},
        {"+-------+","| *   * |","|   *   |","| *   * |","+-------+"},
        {"+-------+","| *   * |","| *   * |","| *   * |","+-------+"},
    };
    
  int die1 = 0, die2 = 0;

  die1 = rand() % 6;
  die2 = rand() % 6;

    cout << die1 << " " << die2 << endl;
  for(int i = 0; i < 5; i++){
    cout << diePrint[die1][i] << " " << diePrint[die2][i] << endl;
  }

  return(die1 + die2 + 2);
}

void win_condition(GameState &game, int running_point){

  if(game.active_game != true){
    if(game.current_point == 7 || game.current_point == 11){
      cout << "Shoot has rolled " << game.current_point << ". Right bettors win." << endl;
      
      if(game.bet_come > 1 || game.bet_pass > 1){
       game.player_balance += ((game.bet_come + game.bet_pass)*2); 
       cout << "You win $" << ((game.bet_come + game.bet_pass)*2) << endl;
      }
      bet_reset(game);
    }
    else if(game.current_point == 2 || game.current_point == 3 || game.current_point == 12){
      cout << "Shoot has rolled " << game.current_point << ". Wrong bettors win." << endl;
      if(game.bet_dont_come > 0 || game.bet_dont_pass > 0){
        game.player_balance += ((game.bet_dont_come + game.bet_dont_pass)*2);
        cout << "You win $" << ((game.bet_dont_come + game.bet_dont_pass)*2) << endl;
      }
      bet_reset(game);
    }
    else{
      game.active_game = true;
      cout << "On " << game.current_point << endl;

    }
  }
  else{
    if(game.current_point == running_point){
      cout << "Point is reached! Right bettors win." << endl;
      if(game.bet_come > 1 || game.bet_pass > 1){
       game.player_balance += ((game.bet_come + game.bet_pass)*2); 
       cout << "You win $" << ((game.bet_come + game.bet_pass)*2) << endl;
      }
      bet_reset(game);
    }
    else if(running_point == 7){
      cout << "Seven out! Shooter retires. Wrong bettors win." << endl;
      if(game.bet_dont_come > 0 || game.bet_dont_pass > 0){
        game.player_balance += ((game.bet_dont_come + game.bet_dont_pass)*2);
        cout << "You win $" << ((game.bet_dont_come + game.bet_dont_pass)*2);
      }
      bet_reset(game);
    }
  }
}

bool bet_check(GameState &game){
    if(game.total_bet_amount > 190){
        cout << "Each round has a $200 bet limit, and $10 minimum bet" << endl;
        cout << "So no softlocking :) try again!" << endl;
        if(!game.active_game){
                pre_menu();
            }
            else{
                active_menu();
            } 
        return 1;
    }

    int temp_bet = 0;
    cout << "You have $" << game.player_balance << ". How much do you wish to bet? ";
    cin >> temp_bet;
    if((temp_bet >= min_bet) &&  (temp_bet <= max_bet) && (temp_bet + game.total_bet_amount <= 200) && (temp_bet <= game.player_balance)){
        game.active_bet = true;
        game.total_bet_amount = temp_bet;
        game.player_balance -= temp_bet;
        if(game.player_choice == "1"){
            if(!game.active_game){
                game.bet_pass = temp_bet;
                pre_menu();
            }
            else{
                game.bet_come = temp_bet;
                active_menu();
            }  
        }
        else if(game.player_choice == "2"){
            if(!game.active_game){
                game.bet_dont_pass = temp_bet;
                pre_menu();
            }
            else{
                game.bet_dont_come = temp_bet;
                active_menu();
            } 
        }
        return 1; 
    }
    cout << "Sorry, the amount $" << temp_bet << " is invalid." << endl;
    cout << "Here are the betting rules for this table:" << endl;
    cout << "Minumum bet is $10, and maximum bet is $200." << endl;
    cout << "You may not bet more than $200 in one round." << endl;
    cout << "Please try again :)" << endl;
    return 0;
}

void bet_reset(GameState &game){
    game.total_bet_amount = 0;
    game.bet_come = 0;
    game.bet_pass = 0;
    game.bet_dont_come = 0;
    game.bet_dont_pass = 0;
    game.active_bet = false;
    game.active_game = false;
}