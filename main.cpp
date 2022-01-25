#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <algorithm>


using namespace std;

class Player {
public:
	int space_occupied;
	string name = " ";
	char symbol = ' ';
	int wins{};

	vector<int>placement;
	void add_to_placement(int value) {
		placement.push_back(value);
	}
	char converter(int val) {
		char placement;
		switch (val)
		{
		case 1:
			placement = '1';
			break;
		case 2:
			placement = '2';
			break;
		case 3:
			placement = '3';
			break;
		case 4:
			placement = '4';
			break;
		case 5:
			placement = '5';
			break;
		case 6:
			placement = '6';
			break;
		case 7:
			placement = '7';
			break;
		case 8:
			placement = '8';
			break;
		case 9:
			placement = '9';
			break;
		}

		return placement;
	}
};
class Board {
public:
	vector<vector<char>>board = {
		{'1','2','3'},{'4','5','6'},{'7','8','9'}
	};

	void print_board() {
		
		cout<<" "<<board[0][0]<<" | "<<" "<<board[0][1]<<" | "<<" "<<board[0][2]<<endl;
		cout<<"-------------\n";
		cout<<" "<<board[1][0]<<" | "<<" "<<board[1][1]<<" | "<<" "<<board[1][2]<<endl;
		cout<<"-------------\n";
		cout<<" "<<board[2][0]<<" | "<<" "<<board[2][1]<<" | "<<" "<<board[2][2]<<endl;

	}
	
	char check_board(Player p){
		for(int i=0; i<3; i++){
			if(board[i][0]==board[i][1] && board[i][1]==board[i][2]){
				return board[i][0];
			}
			if(board[0][i]==board[1][i] && board[1][i]==board[2][i]){
				return board[0][i];
			}

		}
		if(board[0][0]==board[1][1] && board[1][1]==board[1][3]){
			return board[0][0];
		}
		if(board[0][2]==board[1][1] &&board[1][1]==board[2][0]){
			return board[1][1];
		}
		return '0';
	}
	char add_to_board(Player p) {
		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < board[i].size(); j++) {
				char place = p.converter(p.space_occupied);;
				if ((board[i][j])== place) {
					board[i][j] = p.symbol;
					//cout <<board[i][j] <<" ";
				//}
				//else {
				//	cout << board[i][j] <<" " ;
				}
		
			//cout << endl;
		}
	}
	print_board();
	return check_board(p);
	}
	
};

class Computer: public Player{
	public:
		void check_already_used(vector<int>opp, int space){
			vector<int>::iterator it;
			it=find(opp.begin(), opp.end(), space);
			if(it!=opp.end()){
				cout<<space<<" already taken"<<endl;
				check_already_used(opp, (rand()%9+1));	
			}
			else if(self_taken(space)){
				cout<<"recalculating..."<<endl;
				check_already_used(opp, (rand()%9+1));
			}
			else{
				add_to_placement(space);
				space_occupied=space;
				
			}
		}
		bool self_taken(int space){
			for(int i=0; i<placement.size(); i++){
				if(placement[i]==space){
					return true;
				}
			}
			return false;
		}


};

bool react(char response) {
	
	if (response == 'Y' || response == 'y') {
		return true;
	}
	return false;
}
void game(Player one, Player two, Board board) {
	char winner='0';
	string n = " ";
	int turns{};
	cout << "Player one, what name do you want to go by? ";
	cin >> n;
	one.name = n;
	cout<< "Player two, what name do you want to go by? ";
	cin >> n;
	two.name = n;

	//SET GAME
	cout << one.name << " choose your symbol(X/O): ";
	cin >> one.symbol;
	if (one.symbol == 'X' || one.symbol=='x') {
		two.symbol = 'O';
	}
	else {
		two.symbol = 'X';
	}
	
	//BEGIN GAME
	while ((winner=='0')||turns >7){
		cout << one.name << " Where do you want to place the " << one.symbol << ": ";
		cin >> one.space_occupied;
		one.add_to_placement(one.space_occupied);
		++turns;
		winner=board.add_to_board(one);
		if(winner=='0'){
			cout << two.name << " Where do you want to place the " << two.symbol << ": ";
			cin >> two.space_occupied;
			two.add_to_placement(two.space_occupied);
			winner=board.add_to_board(two);
			++turns;
		}
		
	}
	if((toupper(winner)==toupper(one.symbol))){
		cout<<one.name<<" wins"<<endl;
		++one.wins;
		return;
	}
	else if((toupper(winner)==toupper(two.symbol))){
		cout<<two.name<<" wins"<<endl;
		++two.wins;
		return;
	}
	else{
		cout<<"It's a tie!"<<endl;
		return;
	}
	
}
void game(Player one, Board board) {
	string name;
	char symbol;
	int step_one{};
	char winner='0';
	int turns{};
	Computer challenger;
	challenger.name="Challenger";

	cout<<"Player one, what name do you want to go by?: ";
	cin>>name;
	one.name=name;
	
	while(step_one==0){
		cout<<one.name<<" do you want to be 'X' or 'O'?: ";
		cin>>symbol;
		if(symbol=='X'|| symbol=='x'){
		one.symbol=toupper(symbol);
		challenger.symbol='O';
		step_one=1;
		}
		else if(symbol=='O'|| symbol=='o'){
		one.symbol=toupper(symbol);
		challenger.symbol='X';
		step_one=1;
		}
		else{
		cout<<"You havent made a valid choice. Please try again";
		}

	}

	while ((winner=='0')||turns >7){
		cout << one.name << " where do you want to place the " << one.symbol << ": ";
		cin >> one.space_occupied;
		one.add_to_placement(one.space_occupied);
		winner=board.add_to_board(one);
		++turns;
		if(winner=='0'){
			srand(time(NULL));
		/*challenger.add_to_placement(challenger.check_already_used(challenger.placement, challenger.space_occupied));
		cout<<challenger.name<<" went to spot "<<challenger.space_occupied;
		++turns;
		winner=board.add_to_board(challenger);
		*/
			challenger.check_already_used(one.placement,(rand()%9+1));
			cout<<challenger.name<<" went to spot "<<challenger.space_occupied<<endl;
			winner=board.add_to_board(challenger);
			++turns;
		}
		
	}
	if((toupper(winner)==toupper(one.symbol))){
		cout<<one.name<<" wins"<<endl;
		return;
	}
	else if((toupper(winner)==toupper(challenger.symbol))){
		cout<<challenger.name<<" wins"<<endl;
		return;
	}
	else{
		cout<<"It's a tie!"<<endl;
		return;
	}

}
void play_game(Player one, Board board) {
	board.print_board();
	char response;
	cout << "Will another player be joining(Y/N : if no player then the computer will play you): ";
	cin >> response;
	if (react(response)) {
		Player two;
		game(one, two,board);
		cout<<one.name<<" wins: "<<one.wins<<endl;
		cout<<two.name<<" wins: "<<two.wins<<endl;
	}
	else {
		game(one, board);
	}
	
	
}
int main() {
	Board newBoard;
	char response = 'Y';
	while((response == 'Y' || response == 'y')){
		cout << "Do you want to play tic-tac-toe?(Y/N): ";
		cin >> response;
		if(react(response)){
			Player one;
			play_game(one, newBoard);
		}	
	}
	
	cout << "Hope you enjoyed" << endl;
	


	return 0;
}