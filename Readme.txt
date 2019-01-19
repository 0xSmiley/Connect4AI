Trabalho feito por:
	Jose Antonio Prazeres Tavares 201410791
	Nuno Miguel Pereira Correia Lopes 201505531


Como compilar o programa:
	Comando: g++ "nome do ficheiro.cpp" -o "nome do executável"
	Exemplo: g++ cuatroEmLinha.cpp -o cuatroEmLinha

Como correr o programa:
	Comando: ./"nome do executável"
	Exemplo: ./cuatroEmLinha


Input:
	Escolha do algoritmo:
		1- Minimax;
		2- Alpha-Beta.
	Turno inicial:
		1- CPU;
		2- Player.
	Como jogar:
		Basta selecionar a coluna que pretende jogar, as colunas estão numeradas de 0 a 6.


Output:
	Matrix onde jogou o Player seguida pela matrix onde jogou o CPU. Referindo ainda em que posição jogou o CPU.
		Exemplo:

		 0   1   2   3   4   5   6 
		______________________________
		| - | - | - | - | - | - | -  |
		______________________________
		| - | - | - | - | - | - | -  |
		______________________________
		| - | - | - | - | - | - | -  |
		______________________________
		| - | - | - | - | - | - | -  |
		______________________________
		| - | - | - | - | - | - | -  |
		______________________________
		| - | - | - | X | - | - | -  |










		  0   1   2   3   4   5   6 
		______________________________
		| - | - | - | - | - | - | -  |
		______________________________
		| - | - | - | - | - | - | -  |
		______________________________
		| - | - | - | - | - | - | -  |
		______________________________
		| - | - | - | - | - | - | -  |
		______________________________
		| - | - | - | - | - | - | -  |
		______________________________
		| - | - | O | X | - | - | -  |
		O CPU jogou na posição 2

Versão linguagem C++ 11
SO Mac OS Sierra