#include <stdio.h>
#include <string.h>
#include <conio.h>

// DEFINE TIPO CLASS
typedef struct Class
{
	char nome[20];
	int hp;
	int dadoDano;
	char nomeAtaque[20];
	int hpMax;
} Class;

// DEFINE TIPO ENTITY
typedef struct Entity
{
	char nome[20];
	Class class;
} Entity;

void startGame();
void mainMenu();
void luta(Entity inimigo);
int atkTotal(int dadoDano);
int atkDef(int dadoDano);
void newGame();
void recuperaHp();
void salvarJogo();
void carregarJogo();
int pontos;

// Classes do Player
Class mago = {"mago", 30, 12, "Bola de Fogo", 30};
Class escudeiro = {"escudeiro", 80, 4, "Escudada", 80};
Class guerreiro = {"guerreiro", 50, 8, "Corte rápido", 50};

// Classes de Monstros
Class goblinClass = {"goblin", 40, 4, "Corte raso", 40};
Class ogroClass = {"ogro", 70, 6, "Garras", 70};
Class dragaoClass = {"dragao", 120, 12, "Chuva de fogo", 120};

// DECLARAÇÃO DE ENTITYS
Entity player;
Entity goblin;
Entity ogro;
Entity dragao;

int main()
{
	player.class.hp = 0;

	strcpy(goblin.nome, goblinClass.nome);
	goblin.class = goblinClass;

	strcpy(ogro.nome, ogroClass.nome);
	ogro.class = ogroClass;

	strcpy(dragao.nome, dragaoClass.nome);
	dragao.class = dragaoClass;

	startGame();

	return 0;
}

void recuperaHp()
{
	system("cls");
	int opt;
	printf("\nBem vindo a enfermaria\nVoce tem %d pontos, gaste 10 pontos para recuperar hp igual a seu hp total, seu hp atual e de: %d\n", pontos, player.class.hp);
	printf("\nDeseja gastar 10 pontos para recuerar %d de hp? Digite 1 para Sim\n", player.class.hpMax);
	scanf("%d", &opt);
	if (opt == 1)
	{
		if (pontos <= 10)
		{
			printf("Pontos insuficientes para realizar a cura, desculpe :(");
			getch();
			return;
		}
		else
		{
			pontos -= 10;
			player.class.hp += player.class.hpMax;
			system("cls");
			printf("\nNova pontuacao: %d\nHp recuperado: %d\nHp atual: %d\n", pontos, player.class.hpMax, player.class.hp);
			getch();
		}
	}
	else
	{
		system("cls");
		printf("\nVolte Sempre\n");
		return;
	}
}
// Função do menu principal, exibe o loop while faz com que sempre que um combate acabe o jogador volte para o menu principal e só finaliza se selecionar a opção 4: Sair
void mainMenu()
{

	int opt;
	while (opt != 5)
	{
		if (pontos <= 0)
		{
			system("cls");
			printf("\nVoce chegou ao fim dos seus pontos totais, seu antigo corpo foi levado e um novo desafiante entra na arena!\n\nPREPARE-SE PARA UM NOVO JOGO!!");
			getch();
			newGame();
		}
		system("cls");
		printf("\n===============MENU PRINCIPAL===============\n");
		printf("\nOla %s, voce e um %s com %d de HP e possui %d pontos\n", player.nome, player.class.nome, player.class.hp, pontos);
		printf("\nEscolha seu inimigo:\nOpcao 1: goblin (Easy)\nOpcao 2: Ogro (Medium)\nOpcao 3: Dragao (Hard)\nOpcao 4: Gastar pontos para recuperar HP\nOpcao 5: Sair\n");
		scanf("%d", &opt);
		switch (opt)
		{
		case 1:
			luta(goblin);
			break;
		case 2:
			luta(ogro);
			break;
		case 3:
			luta(dragao);
			break;
		case 4:
			recuperaHp();
			break;
		case 5:
			salvarJogo();
			return;
			break;
		default:
			printf("Opcao invalida");
			getch();
			break;
		}
	}
}

void startGame()
{
	int opt;
	printf("\nOla, deseja iniciar um novo jogo? 1 - Novo Jogo | 2 - Carregar Ultimo Jogo Salvo\n");
	scanf("%d", &opt);

	switch (opt)
	{
	case 1:
		newGame();
		break;
	case 2:
		carregarJogo();
		break;
	default:
		printf("Opcao invalida, tente novamente");
	}
}

void newGame()
{
	char nome[20];
	int classOpt;
	system("cls");
	pontos = 12;
	printf("\nVoce comecara seu jogo com 12 pontos, vencer te dara mais pontos e perder removera pontos\n");
	getch();
	printf("\nDigite seu nome\n");
	scanf("%s", &nome);
	printf("\nEscolha sua classe: 1 - Mago | 2 - Escudeiro | 3 - Guerreiro\n");
	scanf("%d", &classOpt);
	strcpy(player.nome, nome);
	player.class.hp = 0;
	while (player.class.hp == 0)
	{
		switch (classOpt)
		{
		case 1:
			player.class = mago;
			break;
		case 2:
			player.class = escudeiro;
			break;
		case 3:
			player.class = guerreiro;
			break;
		default:
			printf("Opção invalida");
		}
	}
	player.class.hp = player.class.hpMax;
	mainMenu();
}

void luta(Entity inimigo)
{
	inimigo.class.hp = inimigo.class.hpMax;
	int pontosApostados = inimigo.class.dadoDano;
	int dmg;
	int atkType;
	int dmgToPlayer;
	// loop while que sempre testa se o player e o inimigo terminaram o turno vivos
	while (inimigo.class.hp > 0 && player.class.hp > 0)
	{
		// Menu de apresentação do inimigo e seleção do tipo de ataque
		system("cls");
		printf("\nA sua frente voce ve um %s com %d de vida escolha como ataca-lo\n", inimigo.nome, inimigo.class.hp);
		printf("\nOpcao 1: Ataque total (causa o dobro do seu dado de dano mas recebe um ataque total em sequencia)\n");
		printf("\nOpcao 2: Ataque e Defesa (Causa um dado de dano mas recebe a metade do dano normal\n");
		scanf("%d", &atkType);

		// Switch para calcular o dano que o player causara e o dano que receberá de volta caso o inimigo sobreviva baseado no tipo de ataque selecionado
		switch (atkType)
		{
		case 1:
			dmg = atkTotal(player.class.dadoDano);
			dmgToPlayer = atkTotal(inimigo.class.dadoDano);
			break;
		case 2:
			dmg = atkDef(player.class.dadoDano);
			dmgToPlayer = (atkDef(inimigo.class.dadoDano) / 2);
			break;
		}
		system("cls");
		printf("\nVoce atacou seu inimigo %s com %s causando %d de dano\n", inimigo.nome, player.class.nomeAtaque, dmg);
		getch();
		// Reduzindo hp do inimigo
		inimigo.class.hp -= dmg;

		// Testa se o inimigo morreu, se sim exibe mensagem de vitória e retorna ao menu principal, se não, exibe a vida restante do inimigo
		if (inimigo.class.hp <= 0)
		{
			printf("\nVoce Ganhou\n");
			pontos += pontosApostados * 2;
			printf("\nVoce ganhou %d pontos\nPotuacao atual: %d", (pontosApostados * 2), pontos);
			getch();
			return;
		}
		system("cls");
		printf("\n%s ainda tem %d de vida\n", inimigo.nome, inimigo.class.hp);
		getch();
		// Exibe o dano recebido pelo player e reduz o hp do player
		system("cls");
		printf("\n\n%s te atacou com %s e causou %d de dano\n", inimigo.nome, inimigo.class.nomeAtaque, dmgToPlayer);
		getch();

		player.class.hp -= dmgToPlayer;

		if (player.class.hp <= 0)
		{
			printf("\nVoce foi derrotado!\n");
			pontos -= pontosApostados;
			printf("\nVoce perdeu %d pontos\nPotuacao atual: %d", pontosApostados, pontos);
			getch();
		}

		// Exibe a vida restante do player
		system("cls");
		printf("\nVoce ainda tem %d de vida\n", player.class.hp);
		getch();
	}
}

int atkTotal(int dadoDano)
{
	return ((rand() % dadoDano) + 1) * 2;
}
int atkDef(int dadoDano)
{
	return ((rand() % dadoDano) + 1);
}

void salvarJogo()
{
	FILE *file = fopen("savegame.txt", "w");
	if (file == NULL)
	{
		printf("Erro ao salvar o jogo.\n");
		return;
	}

	fprintf(file, "%s\n", player.nome);
	fprintf(file, "%s\n", player.class.nome);
	fprintf(file, "%d\n", player.class.hp);
	fprintf(file, "%d\n", pontos);

	fclose(file);
	printf("Jogo salvo com sucesso!\n");
}

void carregarJogo()
{
	FILE *file = fopen("savegame.txt", "r");
	if (file == NULL)
	{
		printf("Nenhum jogo salvo encontrado.\n");
		return;
	}

	char className[20];

	fscanf(file, "%s", player.nome);
	fscanf(file, "%s", className);
	// Determinar a classe do jogador baseado no nome da classe
	if (strcmp(className, "mago") == 0)
	{
		player.class = mago;
	}
	else if (strcmp(className, "escudeiro") == 0)
	{
		player.class = escudeiro;
	}
	else if (strcmp(className, "guerreiro") == 0)
	{
		player.class = guerreiro;
	}

	fscanf(file, "%d", &player.class.hp);
	fscanf(file, "%d", &pontos);

	fclose(file);
	printf("Jogo carregado com sucesso!\n");
	mainMenu();
}