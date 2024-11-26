#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar o jogador
typedef struct {
    char nome[50];
    int vitorias;
} Jogador;

// Fun��es principais
void menu();
void jogar();
void verRanking();
void mostrarCreditos();
void salvarRanking(Jogador jogador);
void inicializarTabuleiro(char tabuleiro[3][3]);
void exibirTabuleiro(char tabuleiro[3][3]);
int verificarVitoria(char tabuleiro[3][3], char simbolo);
void computadorJogar(char tabuleiro[3][3]);

int main() {
    menu();
    return 0;
}

void menu() {
    int opcao;

    do {
        printf("\n--- Menu ---\n");
        printf("1. Jogar\n");
        printf("2. Ver Ranking\n");
        printf("3. Cr�ditos\n");
        printf("4. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer

        switch (opcao) {
            case 1:
                jogar();
                break;
            case 2:
                verRanking();
                break;
            case 3:
                mostrarCreditos();
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Op��o inv�lida! Tente novamente.\n");
        }
    } while (opcao != 4);
}

void jogar() {
    char tabuleiro[3][3];
    int linha, coluna, jogadas = 0, vencedor = 0;
    Jogador jogador;
    strcpy(jogador.nome, "Jogador");
    jogador.vitorias = 0;

    inicializarTabuleiro(tabuleiro);

    printf("\nDigite seu nome: ");
    fgets(jogador.nome, 50, stdin);
    jogador.nome[strcspn(jogador.nome, "\n")] = '\0'; // Remover o '\n'

    while (jogadas < 9 && vencedor == 0) {
        exibirTabuleiro(tabuleiro);

        // Jogada do jogador
        printf("\nSua vez! Digite linha e coluna (0-2): ");
        scanf("%d %d", &linha, &coluna);
        getchar(); // Limpar buffer

        if (linha >= 0 && linha < 3 && coluna >= 0 && coluna < 3 && tabuleiro[linha][coluna] == ' ') {
            tabuleiro[linha][coluna] = 'X';
            jogadas++;
            vencedor = verificarVitoria(tabuleiro, 'X');
        } else {
            printf("Jogada inv�lida! Tente novamente.\n");
            continue;
        }

        if (vencedor || jogadas == 9) break;

        // Jogada do computador
        computadorJogar(tabuleiro);
        jogadas++;
        vencedor = verificarVitoria(tabuleiro, 'O');
    }

    exibirTabuleiro(tabuleiro);

    if (vencedor == 1) {
        printf("\nParab�ns, %s! Voc� venceu!\n", jogador.nome);
        jogador.vitorias++;
        salvarRanking(jogador);
    } else if (vencedor == -1) {
        printf("\nO computador venceu! Tente novamente.\n");
    } else {
        printf("\nEmpate! Boa partida.\n");
    }
}

void salvarRanking(Jogador jogador) {
    FILE *arquivo = fopen("ranking.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao salvar ranking.\n");
        return;
    }
    fprintf(arquivo, "Nome: %s - Vit�rias: %d\n", jogador.nome, jogador.vitorias);
    fclose(arquivo);
}

void verRanking() {
    FILE *arquivo = fopen("ranking.txt", "r");
    if (arquivo == NULL) {
        printf("\nNenhum ranking encontrado.\n");
        return;
    }

    char linha[100];
    printf("\n--- Ranking ---\n");
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha);
    }
    fclose(arquivo);
}

void mostrarCreditos() {
    printf("\n--- Cr�ditos ---\n");
    printf("Jogo da Velha desenvolvido como exemplo de P2.\n");
    printf("Por: Estudante de Ci�ncias da Computa��o.\n");
}

void inicializarTabuleiro(char tabuleiro[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
}

void exibirTabuleiro(char tabuleiro[3][3]) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", tabuleiro[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---+---+---\n");
    }
}

int verificarVitoria(char tabuleiro[3][3], char simbolo) {
    for (int i = 0; i < 3; i++) {
        // Linhas e colunas
        if ((tabuleiro[i][0] == simbolo && tabuleiro[i][1] == simbolo && tabuleiro[i][2] == simbolo) ||
            (tabuleiro[0][i] == simbolo && tabuleiro[1][i] == simbolo && tabuleiro[2][i] == simbolo)) {
            return 1;
        }
    }
    // Diagonais
    if ((tabuleiro[0][0] == simbolo && tabuleiro[1][1] == simbolo && tabuleiro[2][2] == simbolo) ||
        (tabuleiro[0][2] == simbolo && tabuleiro[1][1] == simbolo && tabuleiro[2][0] == simbolo)) {
        return 1;
    }
    return 0;
}

void computadorJogar(char tabuleiro[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[i][j] == ' ') {
                tabuleiro[i][j] = 'O';
                return;
            }
        }
    }
}
