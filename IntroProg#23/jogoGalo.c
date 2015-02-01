#include <stdio.h>
#include <stdlib.h>

#define CLEAR_INPUT while (!getchar ())

/* Define-se a largura (e altura) do tabuleiro. 
Por padr�o � utilizado 3. */
#define DIM 3

/* � definida uma vari�vel global "vez" que cont�m o n�me-
ro da jogada atual. */
int vez;

/* Aqui s�o declaradas todas as fun��es utilizadas ao lon-
go do programa. S�o declaradas aqui, mas s� s�o definidas
posteriormente. Desta forma, podemos chamar as fun��es de
qualquer local, independemente da sua posi��o relativa no
c�digo.*/
int mostrarMenu(void);
void jogar(int tabuleiro[][DIM]);
void mostrarTabuleiro(int tabuleiro[][DIM]);
void limparTabuleiro(int tabuleiro[][DIM]);
void efetuarJogada(int tabuleiro[][DIM]);
int verificarPosicao(int tabuleiro[][DIM], int linha, int coluna);
int verificarFim(int tabuleiro[][DIM], int vez);
int verificarLinhas(int tabuleiro[][DIM]);
int verificarColunas(int tabuleiro[][DIM]);
int verificarDiagonais(int tabuleiro[][DIM]);
int verificarEmpate(int tabuleiro[][DIM]);
void limparEcra(void);

int main()
{
	int tabuleiro[DIM][DIM],
		continuar;

	do
	{
		vez = 1;
		continuar = mostrarMenu();

		if (continuar == 1)
			jogar(tabuleiro);

		CLEAR_INPUT;

	} while (continuar);

	return 0;
}

/* Fun��o cujo objetivo principal � mostrar o menu e recolher
a op��o selecionada. */
int mostrarMenu(void)
{
	int opcao;

	printf("\n        __                          _           ___      _ ");
	printf("\n        \\ \\  ___   __ _  ___     __| | ___     / _ \\__ _| | ___  ");
	printf("\n         \\ \\/ _ \\ / _` |/ _ \\   / _` |/ _ \\   / /_\\/ _` | |/ _ \\ ");
	printf("\n      /\\_/ / (_) | (_| | (_) | | (_| | (_) | / /_\\\\ (_| | | (_) |");
	printf("\n      \\___/ \\___/ \\__, |\\___/   \\__,_|\\___/  \\____/\\__,_|_|\\___/ ");
	printf("\n                  |___/                                          \n");

	printf("1 - Jogar\n");
	printf("0 - Sair\n");
	printf("\nOp��o: ");

	scanf(" %d", &opcao);

	if (opcao != 0 || opcao != 1) {
		printf("\nOp��o Inv�lida. Tente novamente.\n");
	}

	limparEcra();
	return opcao;
}

/* Este m�todo � o principal respons�vel pelo andamento do jo-
go, contendo o loop principal. */
void jogar(int tabuleiro[][DIM])
{
	int continua;

	/* Primeiro limpa o tabuleiro que recebeu.*/
	limparTabuleiro(tabuleiro);

	do
	{
		/* Depois, limpa o ecr�, mostra o tabuleiro e permite-
		efetuar as jogadas at� ao jogo acabar. */
		limparEcra();
		mostrarTabuleiro(tabuleiro);
		efetuarJogada(tabuleiro);

	} while (verificarFim(tabuleiro, vez) != 1);
}

/* Este procedimento � utilizado para mostrar o tabuleiro no ecr�.
Um dos par�metros consiste no tabuleiro para ser imprimido. Infor-
ma��es:

	0 corresponde a nada (espa�o branco);
	1 corresponde ao X;
	Qualquer outro valor corresponde � O. */
void mostrarTabuleiro(int tabuleiro[][DIM])
{
	int linha, coluna;
	printf("\n\a\7");

	for (linha = 0; linha < DIM; linha++)
	{
		for (coluna = 0; coluna < DIM; coluna++)
		{
			if (tabuleiro[linha][coluna] == 0)
				printf("   ");
			else
				if (tabuleiro[linha][coluna] == 1)
					printf(" X ");
				else
					printf(" O ");

			if (coluna != (DIM - 1))
				printf(" | ");
		}
		putchar('\n');
	}
	putchar('\n');
}

/* O objetivo desta fun��o � limpar o tabuleiro, colocando to-
dos os espa�os com 0, pois estes podem conter "lixo" da mem�-
ria RAM. */
void limparTabuleiro(int tabuleiro[][DIM])
{
	int linha, coluna;

	for (linha = 0; linha < DIM; linha++)
		for (coluna = 0; coluna < DIM; coluna++)
			tabuleiro[linha][coluna] = 0;
}

/* Este procedimento est� encarregue da jogada atual, adicio-
nando-a ao tabuleiro ou n�o.*/
void efetuarJogada(int tabuleiro[][DIM])
{
	int linha, coluna;

	/* Incrementa-se um valor � vari�vel vez.*/
	vez++;
	printf("\n--> Jogador %d \n", (vez % 2) + 1);

	do
	{
		/* Neste ciclo, � pedida a linha e a coluna para efetu-
		ar a jogada. � decrementado um valor da vari�vel da co-
		luna e da linha, pois o tabuleiro est� armazenado  num
		array e os arrays s�o zero-indexed. */

		printf("Linha: ");
		scanf("%d", &linha);
		linha--;

		CLEAR_INPUT;

		printf("Coluna: ");
		scanf("%d", &coluna);
		coluna--;

		CLEAR_INPUT;

		/* Aqui confirma-se se a posi��o est� livre e se efeti-
		vamente existe. */
		if (verificarPosicao(tabuleiro, linha, coluna) == 0)
			printf("Posi��o ocupada ou inexistente. Tente novamente.\n");

	} while (verificarPosicao(tabuleiro, linha, coluna) == 0);

	/* Coloca-se o valor corresponde ao jogador que  jogou  na
	linha e coluna corretas. */
	if (vez % 2)
		tabuleiro[linha][coluna] = -1;
	else
		tabuleiro[linha][coluna] = 1;
}

/* Nesta fun��o que pede como argumentos o tabuleiro, linha  e
coluna, � verificada a exist�ncia e disponibilidade de uma po-
si��o no tabuleiro.

Retorna 0 se a posi��o estiver indispon�vel ou em caso de inexis-
t�ncia e retorna 1 se estiver dispon�vel. */
int verificarPosicao(int tabuleiro[][DIM], int linha, int coluna)
{
	if (linha < 0 || linha > (DIM - 1))
		return 0;

	if (coluna < 0 || coluna > (DIM - 1))
		return 0;

	if (tabuleiro[linha][coluna] != 0)
		return 0;

	return 1;
}

/* Com esta fun��o, verificamos se j� estamos no fim do jogo ou
n�o. Verificam-se as linhas, colunas, diagonais ou se h�  algum
empate. Caso nenhum dos casos ocorra, � retornado o valor 0 e o
jogo continua. */
int verificarFim(int tabuleiro[][DIM], int vez)
{
	char mensagem[] = "\n\nFim do jogo. O Jogador %d venceu!\n\n";
	int jogadorAtual = (vez % 2) + 1;

	if (verificarLinhas(tabuleiro))
	{
		printf(mensagem, jogadorAtual);
		mostrarTabuleiro(tabuleiro);
		return 1;
	}

	if (verificarColunas(tabuleiro))
	{
		printf(mensagem, jogadorAtual);
		mostrarTabuleiro(tabuleiro);
		return 1;
	}

	if (verificarDiagonais(tabuleiro))
	{
		printf(mensagem, jogadorAtual);
		mostrarTabuleiro(tabuleiro);
		return 1;
	}

	if (verificarEmpate(tabuleiro))
	{
		printf("Fim do Jogo. Houve um empate.\n\n");
		mostrarTabuleiro(tabuleiro);
		return 1;
	}

	return 0;
}

/* Nesta fun��o s�o verificadas as somas do conte�do de to-
das as linhas do tabuleiro. se alguma for igual a DIM ou a 
-DIM, quer dizer que algum jogador ganhou. */
int verificarLinhas(int tabuleiro[][DIM])
{
	int linha, coluna,
		soma;

	for (linha = 0; linha < DIM; linha++)
	{
		soma = 0;

		for (coluna = 0; coluna < DIM; coluna++)
			soma += tabuleiro[linha][coluna];

		if (soma == DIM || soma == (-1)*DIM)
			return 1;
	}

	return 0;
}

/* Nesta fun��o s�o verificadas as somas do conte�do de to-
das as colunas do tabuleiro. se alguma for igual a DIM ou a
-DIM, quer dizer que algum jogador ganhou. */
int verificarColunas(int tabuleiro[][DIM])
{
	int linha, coluna,
		soma;

	for (coluna = 0; coluna < DIM; coluna++)
	{
		soma = 0;

		for (linha = 0; linha < DIM; linha++)
			soma += tabuleiro[linha][coluna];

		if (soma == DIM || soma == (-1)*DIM)
			return 1;
	}

	return 0;
}

/* Esta fun��o faz o mesmo que as fun��es anteriores
s� que verificando a soma das duas diagonais do tabuleiro. */
int verificarDiagonais(int tabuleiro[][DIM])
{
	int linha,
		primeiraDiagonal = 0,
		segundaDiagonal = 0;

	for (linha = 0; linha < DIM; linha++)
	{
		primeiraDiagonal += tabuleiro[linha][linha];
		segundaDiagonal += tabuleiro[linha][DIM - linha - 1];
	}

	if (primeiraDiagonal == DIM || primeiraDiagonal == (-1)*DIM ||
		segundaDiagonal == DIM || segundaDiagonal == (-1)*DIM)
		return 1;

	return 0;
}

/* Se nenhum utilizador tiver ganho, esta fun��o � chamada de forma
a saber se h� alguma casa vazia ou n�o. Caso haja, quer dizer que o 
jogo ainda n�o terminou. Caso n�o haja, quer dizer que os jogadores
ficaram empatados. */
int verificarEmpate(int tabuleiro[][DIM])
{
	int linha, coluna;

	for (linha = 0; linha < DIM; linha++)
		for (coluna = 0; coluna < DIM; coluna++)
			if (tabuleiro[linha][coluna] == 0)
				return 0;

	return 1;
}

/* Utilizamos este m�todo para limpar a janela da linha de co-
mandos, imprimindo 100 linhas em branco. Poder�amos, simples-
mente, utilizar os comandos de sistema "cls" e "clear", mas por
motivos de seguran�a n�o se deve faz�-lo. */
void limparEcra(void)
{
	int count = 0;

	while (count != 100)
	{
		putchar('\n');
		count++;
	}
}