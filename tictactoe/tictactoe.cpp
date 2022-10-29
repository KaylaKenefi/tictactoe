#include <iostream>
using namespace std;
#define BSIZE 4
// global variables
char board[BSIZE][BSIZE] = { {'-', '-', '-'}, {'-', '-', '-'}, {'-', '-', '-'} },
player = 'X', player_ai = 'O', game_choice;
int x, y, ai_wins, player_wins;

void create_board(char fill)
{
  for (int i = 0; i < BSIZE - 1; i++) {
    for (int j = 0; j < BSIZE - 1; j++) { board[i][j] = fill;}
} }
void print_board() {
  // Top bar
  cout << "  1 2 3 \n";
  // Second Row
  cout << "1";
  for (int i = 0; i < BSIZE; i++) {cout << " " << board[0][i];}
  cout << endl;
  // Third Row
  cout << "2";
  for (int i = 0; i < BSIZE; i++) {cout << " " << board[1][i];}
  cout << endl;
  // Fourth Row
  cout << "3";
  for (int i = 0; i < BSIZE; i++) {cout << " " << board[2][i];}
  cout << endl;
}
bool check_win(char player)
{
  // Checking to see if the player has won the game
  return
    board[0][0] == player && board[0][1] == player && board[0][2] == player || // rows
    board[1][0] == player && board[1][1] == player && board[1][2] == player ||
    board[2][0] == player && board[2][1] == player && board[2][2] == player ||
    board[0][0] == player && board[1][0] == player && board[2][0] == player || // column
    board[0][1] == player && board[1][1] == player && board[2][1] == player ||
    board[0][2] == player && board[1][2] == player && board[2][2] == player ||
    board[0][0] == player && board[1][1] == player && board[2][2] == player || // diag
    board[2][0] == player && board[1][1] == player && board[0][2] == player;
}
bool check_tie()
{
  if (!check_win(player) || !check_win(player_ai)) {
    if (board[0][0] == '-' || board[0][1] == '-' || board[0][2] == '-' ||
      board[1][0] == '-' || board[1][1] == '-' || board[1][2] == '-' ||
      board[2][0] == '-' || board[2][1] == '-' || board[2][2] == '-') return false;
  } else return true;
}
// random ai placement on the 3x3 board
void place_ai() {
  while (1) {
    x = rand() % 3;
    y = rand() % 3;
    if (board[x][y] == player || board[x][y] == player_ai) {
      continue;
    }
    else {
      board[x][y] = player_ai;
    }
    break;
} }
bool place_user(int x, int y) {
  // Places the user at the requested spot
  if (x <= 3 || y <= 3) {
    if (board[x - 1][y - 1] == player_ai || board[x - 1][y - 1] == player) {
      return false;
    } else if (board[x - 1][y - 1] == '-') {
      board[x - 1][y - 1] = player;
      return true;
    }
  } else return false;
}
void game()
{
  cout << "You are X's\n";
  int turns_taken = 0;
  while (1) {
    // This is the beginning of the game
    print_board();

    cout << "Where would you like to place you character at?\nRow: ";
    cin >> x;
    cout << "Column: ";
    cin >> y;

    cout << endl;

    if (place_user(x, y)) {
      if (check_tie()) {
        cout << "It's a Tie!\n";
        print_board();
        break;
      }
      if (check_win(player)) {
        cout << "Player " << player << " Won!\n";
        player_wins += 1;
        print_board();
        break;
      } else {
        if (turns_taken <= 8) {
          place_ai();
          cout << "AI's turn" << endl;
          turns_taken += 2;
          if (check_win(player_ai)) {
            cout << "The AI has won!\n";
            ai_wins += 1;
            print_board();
            break;
      } } }
      continue;
    }
    else {
      cout << "Sorry that doesn't exist on the board.\nTry again\n";
      continue;
} } }
int main()
{
  create_board('-');
  while (1) {
    game();
    cout << "Would you like to play again(Y or N)? ";
    cin >> game_choice;
    cout << endl;

    if (game_choice == 'Y' || game_choice == 'y') {
      create_board('-');
      cout << "Player " << player << " won " << player_wins << " times.\nPlayer " << player_ai << " won " << ai_wins << " times.\n" << endl;
      continue;
    } else if (game_choice == 'N' || game_choice == 'n') {
      cout << "Player " << player << " won " << player_wins << " times.\nPlayer " << player_ai << " won " << ai_wins << " times.\n" << endl;
      break;
    } else cout << "Sorry that's not quiet right.\nEnter a Y for yes or a N for no.\n";
 } }
