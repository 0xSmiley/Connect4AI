/*
Trabalho feito por:
	Jose Antonio Prazeres Tavares
		201410791
	Nuno Miguel Pereira Correia Lopes
		201505531
*/

#include <chrono>
#include <iostream>
#include <list>
#include <queue>
#include <algorithm>

#define INFINITO 9999

using namespace std;

int turnCPU;
class node{
public:
	char board[6][7];
	int nivel;
	int jogada;
	node (){
		memset(board,'-',sizeof(board));
		nivel=0;
		jogada=0;
	}
	list<node> descendentes(){
		list<node> desc;
		node temp;

		for(int i=0;i<6;i++)							// Igualar o init.board do filho com o do pai
			for(int j=0;j<7;j++){
				temp.board[i][j]=board[i][j];
			}
		for (int j=6; j>=0; j--)						// Verificar coluna a coluna uma posição onde se possa jogar
			for(int i=5; i>=0;i--){
				if(board[i][j]=='-'){
					char player='O';
					if (turnCPU==1) player = 'X';
					temp.board[i][j]=player;			// Marcamos a posição
					temp.nivel=nivel+1;
					temp.jogada=j;

					desc.push_front(temp);				// Inserir na lista
					temp.board[i][j]='-';				// Remover a jogada para não interferir com as proximas iterações
					break;
				}
			}
		return desc;									//return lista de descendentes
	}
};

node init;
node temp;

void desenhaTabuleiro(node &state);
void jogaPlayer();
void jogaCPU(int algoritmo);
int win(node &no);
bool empate(node &no);
bool efetuaJogada(int posicion,char player);
bool horizontal(node &no,int x,int y);
bool vertical(node &no,int x,int y);
bool diagonalUm(node &no,int x,int y);
bool diagonalDois(node &no,int x,int y);
bool terminal(node &temp);
void minimax(node &state);
int maxValue(node &state);
int minValue(node &state);
int utility (node &state);
int heuristica(node &state);
int horizontalHeuristica(node &state,int x,int y);
int verticalHeuristica(node &state,int x,int y);
int diagonalUmHeuristica(node &state,int x,int y);
int diagonalDoisHeuristica(node &state,int x,int y);
void alphaBeta(node &state);
int maxValueAlphaBeta(node &state,int alpha,int beta);
int minValueAlphaBeta(node &state, int alpha,int beta);


bool diagonalDois(node &no,int x,int y){
	char c=no.board[x][y];
	if (c=='-') return false;

	if (x-4<=2 && y+4<=7){

		for(int i =0; i <4; i++){
			if(no.board[x-i][y+i] != c) return false;
		}
		return true;
	}
	return false;
}
bool diagonalUm(node &no,int x,int y){
	char c=no.board[x][y];
	if (c=='-') return false;
	if (x+4<=6 && y+4<=7){
		for(int i =0; i < 4; i++){
			if(no.board[x+i][y+i] != c) return false;
		}
		return true;
	}
	return false;
}
bool vertical(node &no, int x,int y){
	char c=no.board[x][y];
	if (c=='-') return false;
	if (x+4 <=6){

		for(int i=x+1; i<x+4; i++){
			if(no.board[i][y]!=c) return false;
		}
		return true;
	}
	return false;
}
bool horizontal(node &no,int x,int y){
	char c=no.board[x][y];
	if (c=='-') return false;
	if (y+4 <=7){

		for(int j=y+1; j<y+4; j++){
			if(no.board[x][j]!=c) return false;
		}
		return true;

	}
	return false;
}

int diagonalDoisHeuristica(node &state,int x,int y){
	int heuristica=0,contX=0,contO=0;
	bool seguidoX=false, seguidoO=false;

	for(int i=0;i<4;i++){
		if(state.board[x-i][y+i]=='X'){
			seguidoO=false;
			contX++;

			if(contX==1)
				heuristica+=-1;
			else if(contX==2 && seguidoX)
				heuristica+=-9;
			else if(contX==3 && seguidoX)
				heuristica+=-40;
			seguidoX=true;
		}

		else if(state.board[x-i][y+i]=='O'){
			seguidoX=false;
			contO++;

			if(contO==1)
				heuristica+=1;
			else if(contO==2 && seguidoO)
				heuristica+=9;
			else if(contO==3 && seguidoO)
				heuristica+=40;
			seguidoO=true;
		}
		else{
			seguidoO=false;
			seguidoX=false;
		}
	}

	return heuristica;
}
int diagonalUmHeuristica(node &state,int x,int y){
	int heuristica=0,contX=0,contO=0;
	bool seguidoX=false, seguidoO=false;

	for(int i=0;i<4;i++){
		if(state.board[x+i][y+i]=='X'){
			seguidoO=false;
			contX++;

			if(contX==1)
				heuristica+=-1;
			else if(contX==2 && seguidoX)
				heuristica+=-9;
			else if(contX==3 && seguidoX)
				heuristica+=-40;
			seguidoX=true;
		}

		else if(state.board[x-i][y+i]=='O'){
			seguidoX=false;
			contO++;

			if(contO==1)
				heuristica+=1;
			else if(contO==2 && seguidoO)
				heuristica+=9;
			else if(contO==3 && seguidoO)
				heuristica+=40;
			seguidoO=true;
		}
		else{
			seguidoO=false;
			seguidoX=false;
		}
	}

	return heuristica;
}
int verticalHeuristica(node &state,int x,int y){
	int heuristica=0,contX=0,contO=0;
	bool seguidoX=false, seguidoO=false;

	for(int i=0;i<4;i++){
		if(state.board[x+i][y]=='X'){
			seguidoO=false;
			contX++;

			if(contX==1)
				heuristica+=-1;
			else if(contX==2 && seguidoX)
				heuristica+=-9;
			else if(contX==3 && seguidoX)
				heuristica+=-40;
			seguidoX=true;
		}

		else if(state.board[x-i][y+i]=='O'){
			seguidoX=false;
			contO++;

			if(contO==1)
				heuristica+=1;
			else if(contO==2 && seguidoO)
				heuristica+=9;
			else if(contO==3 && seguidoO)
				heuristica+=40;
			seguidoO=true;
		}
		else{
			seguidoO=false;
			seguidoX=false;
		}
	}

	return heuristica;
}
int horizontalHeuristica(node &state,int x,int y){

	int heuristica=0,contX=0,contO=0;
	bool seguidoX=false, seguidoO=false;

	for(int i=0;i<4;i++){
		if(state.board[x][y+i]=='X'){
			seguidoO=false;
			contX++;

			if(contX==1)
				heuristica+=-1;
			else if(contX==2 && seguidoX)
				heuristica+=-9;
			else if(contX==3 && seguidoX)
				heuristica+=-40;
			seguidoX=true;
		}

		else if(state.board[x-i][y+i]=='O'){
			seguidoX=false;
			contO++;

			if(contO==1)
				heuristica+=1;
			else if(contO==2 && seguidoO)
				heuristica+=9;
			else if(contO==3 && seguidoO)
				heuristica+=40;
			seguidoO=true;
		}
		else{
			seguidoO=false;
			seguidoX=false;
		}
	}

	return heuristica;
}

int heuristica(node &state){
	int cont=0;
	for (int i=0; i<6; i++){
		for (int j=0;j<7;j++){
			cont+=horizontalHeuristica(state,i,j);
			cont+=verticalHeuristica(state,i,j);
			cont+=diagonalUmHeuristica(state,i,j);
			cont+=diagonalDoisHeuristica(state,i,j);
		}
	}
	return cont;
}

int maxValue(node &state){
	turnCPU=-1;
	list<node> desc;
	if (terminal(state)) return utility(state);

	int v=-INFINITO;
	desc=state.descendentes();
	node s;
	int t=v;

	while(!desc.empty()){
		s=desc.front();
		v=max(v, minValue(s));
		if (v>t){											// Guarda a jogada a efetuar
			t=v;
			if (s.nivel==init.nivel+1){
				temp=s;
			}
		}
		desc.pop_front();
	}
	return v;
}

int minValue(node &state){
	turnCPU=1;
	list<node> desc;

	if (terminal(state)) return utility(state);

	int v = INFINITO;
	desc=state.descendentes();
	node s;

	while(!desc.empty()){
		s=desc.front();
		desc.pop_front();
		v=min(v, maxValue(s));
	}
	return v;
}

int maxValueAlphaBeta(node &state,int alpha,int beta){
	turnCPU=-1;
	list<node> desc;
	int utilidade=0;
	if (terminal(state)) return utility(state);
	int v=-INFINITO;
	desc=state.descendentes();
	node s;
	int t=v;
	while(!desc.empty()){
		s=desc.front();
		desc.pop_front();
		v=max(v, minValueAlphaBeta(s,alpha,beta));

		if (v>t){											// Guarda a jogada a efetuar
			t=v;
			if (s.nivel==init.nivel+1){
				temp=s;
			}
		}

		if (v>=beta){										// Poda
			if (s.nivel==init.nivel+1){
				temp=s;
			}
			return v;
		}
		alpha=max(alpha,v);
	}
	return v;
}
int minValueAlphaBeta(node &state, int alpha,int beta){
	turnCPU=1;
	list<node> desc;
	if (terminal(state)) return utility(state);
	int v = INFINITO;
	desc=state.descendentes();
	node s;
	while(!desc.empty()){
		s=desc.front();
		desc.pop_front();
		v=min(v, maxValueAlphaBeta(s,alpha,beta));

		if (v <= alpha ){									// Poda
			return v;
		}

		beta=min(beta,v);
	}
	return v;

}

void minimax(node &state){

	maxValue(state);

}

void alphaBeta(node &state){

	maxValueAlphaBeta(state,-INFINITO,INFINITO);

}

int utility(node &state){

	if (win(state)==1) return -512; 					// Ganha Player
	else if (win(state)==-1) return 512; 			// Ganha CPU
	else if(empate(state)) return 0; 					// Empate
	else return heuristica(state);						// Limite de Profundidade

}

bool efetuaJogada(int posicion,char player){

	for (int i=5; i>=0; i--){
		if (init.board[i][posicion]=='-'){
			init.board[i][posicion]=player;
			return true;
		}
	}

	return false;
}

void desenhaTabuleiro(node &state){
	for(int i=0;i<10;i++)
		cout<<endl;

	for (int i=0;i<7;i++)
		cout<<"  "<<i<<" ";
	cout<<endl;
	for (int i=0; i<6; i++){
		cout << "______________________________"<< endl;
		for (int j=0;j<7;j++){
			cout<<"| "<<state.board[i][j]<<" ";
		}
		cout<<" |"<<endl;
		//cout << endl;
	}
}

void jogaPlayer(){

	int posicion;
	cout<<"Insira a posicao!"<<endl;
	while(1){
		cin>>posicion;
		if (posicion>=0 && posicion<=6 && efetuaJogada(posicion,'X')) break;
		else cout<<"Posicao nao valida, por favor insira uma nova posicao"<<endl;
	}
	init.nivel++;

}

bool terminal(node &temp){

	if(win(temp)!=0 || empate(temp) || temp.nivel-init.nivel >= 7)		// NO terminal: No vencedor, No perdedor ou No com profundidade 7 do init
		return true;

	return false;
}

void jogaCPU(int algoritmo){

	if(algoritmo==1)
   		minimax(init);
   	else
		alphaBeta(init);

	init=temp;

	turnCPU=-1;

}

int win(node &no){

	for (int i=0;i<6;i++)
		for (int j=0;j<7;j++){
			if (horizontal(no,i,j) || vertical(no,i,j) || diagonalUm(no,i,j) || diagonalDois(no,i,j)){
				if (no.board[i][j]=='X') return 1;
				else return -1;
			}
		}

	return 0;
}

bool empate(node &no){
	if (win(no)==0){
		for (int i=0;i<6;i++)
			for (int j=0;j<7;j++)
				if (no.board[i][j]=='-') return false;
	}

	return true;
}

int main() {
	int algoritmo;

	cout << "Pretende utilizar:"<< endl<<  "1-Min-Max;" << endl<< "2-Alpha-Beta."<< endl;
	cin>> algoritmo;
	if (algoritmo!=1 && algoritmo!=2){
		cout<<"comando nao valido"<<endl;
		exit(0);
	}
	cout<<"Escolha quem começa o jogo"<<endl<<"1-CPU"<<endl<<"2-Player"<<endl;
	int turno;
	cin>>turno;
	if (turno==1) turnCPU=-1;
	else if (turno==2) turnCPU=1;
	else{
		cout<<"comando nao valido"<<endl;
		exit(0);
	}


	memset (init.board, '-', sizeof(init.board));

	desenhaTabuleiro(init);

	while (true){
		if (turnCPU == 1){
			jogaPlayer();
		}
		else{
			jogaCPU(algoritmo);
		}
		desenhaTabuleiro(init);
		if (win(init)==-1){
			cout<<"Ganhou CPU!"<<endl;
			break;
		}
		else if (win(init)==1){
			cout << "Ganhou Player!"<<endl;
			break;
		}
		else if(empate(init)){
			cout <<"Empate!"<<endl;
			break;
		}
		if(turnCPU==-1)
			cout << "O CPU jogou na posição "<< init.jogada << endl;
		turnCPU*=-1;
	}
	return 0;
}
