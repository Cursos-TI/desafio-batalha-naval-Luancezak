// nivel novato


#include <stdio.h>

// Tamanho do tabuleiro
#define TAMANHO 10
// Tamanho fixo dos navios
#define TAM_NAVIO 3

// Função para inicializar o tabuleiro com água (valor 0)
void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("  ");
    for (int j = 0; j < TAMANHO; j++) {
        printf("%d ", j); // cabeçalho com números das colunas
    }
    printf("\n");

    for (int i = 0; i < TAMANHO; i++) {
        printf("%d ", i); // número da linha
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para posicionar navio no tabuleiro
int posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char orientacao) {
    // Verifica se o navio cabe no tabuleiro
    if ((orientacao == 'H' && coluna + TAM_NAVIO > TAMANHO) ||
        (orientacao == 'V' && linha + TAM_NAVIO > TAMANHO)) {
        return 0; 
    }

    // Verifica sobreposição
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (orientacao == 'H' && tabuleiro[linha][coluna + i] != 0) {
            return 0; // Já tem navio nessa posição
        } else if (orientacao == 'V' && tabuleiro[linha + i][coluna] != 0) {
            return 0;
        }
    }

    // Posiciona o navio (valor 3)
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (orientacao == 'H') {
            tabuleiro[linha][coluna + i] = 3;
        } else {
            tabuleiro[linha + i][coluna] = 3;
        }
    }

    return 1; 
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];

    // Inicializa o tabuleiro com água (0)
    inicializarTabuleiro(tabuleiro);

    // Define as coordenadas e orientações dos navios
    int linhaNavio1 = 2, colunaNavio1 = 4; // Navio 1 horizontal
    int linhaNavio2 = 5, colunaNavio2 = 7; // Navio 2 vertical

    // Posiciona os navios no tabuleiro
    if (!posicionarNavio(tabuleiro, linhaNavio1, colunaNavio1, 'H')) {
        printf("Erro ao posicionar o Navio 1!\n");
    }

    if (!posicionarNavio(tabuleiro, linhaNavio2, colunaNavio2, 'V')) {
        printf("Erro ao posicionar o Navio 2!\n");
    }

    // Exibe o tabuleiro final com os navios posicionados
    printf("\n=== TABULEIRO ===\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}


// nivel aventureiro 
#include <stdio.h>

#define TAMANHO 10
#define TAM_NAVIO 3

// Inicializa o tabuleiro com água (valor 0)
void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Exibe o tabuleiro formatado
void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("    ");
    for (int j = 0; j < TAMANHO; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO; i++) {
        printf("%2d |", i);
        for (int j = 0; j < TAMANHO; j++) {
            printf(" %d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Verifica se a posição já está ocupada
int posicaoOcupada(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    return tabuleiro[linha][coluna] != 0;
}

// Posiciona navio horizontal ou vertical
int posicionarNavioLinear(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char orientacao) {
    if ((orientacao == 'H' && coluna + TAM_NAVIO > TAMANHO) ||
        (orientacao == 'V' && linha + TAM_NAVIO > TAMANHO)) {
        return 0;
    }

    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha + (orientacao == 'V' ? i : 0);
        int c = coluna + (orientacao == 'H' ? i : 0);
        if (posicaoOcupada(tabuleiro, l, c)) {
            return 0;
        }
    }

    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha + (orientacao == 'V' ? i : 0);
        int c = coluna + (orientacao == 'H' ? i : 0);
        tabuleiro[l][c] = 3;
    }

    return 1;
}

// Posiciona navio na diagonal (tipo: 'P' para principal ou 'S' para secundária)
int posicionarNavioDiagonal(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char tipo) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = tipo == 'P' ? linha + i : linha + i;
        int c = tipo == 'P' ? coluna + i : coluna - i;

        if (l < 0 || l >= TAMANHO || c < 0 || c >= TAMANHO || posicaoOcupada(tabuleiro, l, c)) {
            return 0;
        }
    }

    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = tipo == 'P' ? linha + i : linha + i;
        int c = tipo == 'P' ? coluna + i : coluna - i;
        tabuleiro[l][c] = 3;
    }

    return 1;
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    inicializarTabuleiro(tabuleiro);

    // Posicionar 2 navios horizontais/verticais
    if (!posicionarNavioLinear(tabuleiro, 1, 1, 'H')) {
        printf("Erro ao posicionar navio horizontal!\n");
    }
    if (!posicionarNavioLinear(tabuleiro, 5, 2, 'V')) {
        printf("Erro ao posicionar navio vertical!\n");
    }

    // Posicionar 2 navios diagonais
    if (!posicionarNavioDiagonal(tabuleiro, 0, 0, 'P')) { // Diagonal principal
        printf("Erro ao posicionar navio diagonal principal!\n");
    }
    if (!posicionarNavioDiagonal(tabuleiro, 0, 9, 'S')) { // Diagonal secundária
        printf("Erro ao posicionar navio diagonal secundária!\n");
    }

    // Exibir o tabuleiro final
    printf("\n=== TABULEIRO FINAL ===\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}

// nivel mestre

#include <stdio.h>

#define TAB 10
#define HAB 5  // Tamanho das matrizes de habilidade (5x5)

// Inicializa o tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAB][TAB]) {
    for (int i = 0; i < TAB; i++) {
        for (int j = 0; j < TAB; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Exibe uma matriz genérica (usada para habilidades ou tabuleiro)
void exibirMatriz(int matriz[][HAB], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

// Gera uma matriz em forma de CONE (origem no topo)
void gerarCone(int cone[HAB][HAB]) {
    for (int i = 0; i < HAB; i++) {
    for (int j = 0; j < HAB; j++) {
        if (j >= HAB / 2 - i && j <= HAB / 2 + i) {
        cone[i][j] = 1;
        } else {
        cone[i][j] = 0;
    }
    }
}
}

// Gera uma matriz em forma de CRUZ (origem no centro)
void gerarCruz(int cruz[HAB][HAB]) {
    for (int i = 0; i < HAB; i++) {
    for (int j = 0; j < HAB; j++) {
    if (i == HAB / 2 || j == HAB / 2) {
                cruz[i][j] = 1;
    } else {
                cruz[i][j] = 0;
            }
        }
    }
}

// Gera uma matriz em forma de OCTAEDRO (losango)
void gerarOctaedro(int octaedro[HAB][HAB]) {
    for (int i = 0; i < HAB; i++) {
        for (int j = 0; j < HAB; j++) {
            if (abs(i - HAB / 2) + abs(j - HAB / 2) <= HAB / 2) {
                octaedro[i][j] = 1;
            } else {
                octaedro[i][j] = 0;
}
}
}
}

int main() {
    int tabuleiro[TAB][TAB];
    int cone[HAB][HAB], cruz[HAB][HAB], octaedro[HAB][HAB];

    inicializarTabuleiro(tabuleiro);
    gerarCone(cone);
    gerarCruz(cruz);
    gerarOctaedro(octaedro);

    // Exibindo as matrizes das habilidades
    printf("=== Habilidade: CONE ===\n");
    exibirMatriz(cone, HAB);

    printf("\n=== Habilidade: CRUZ ===\n");
    exibirMatriz(cruz, HAB);

    printf("\n=== Habilidade: OCTAEDRO ===\n");
    exibirMatriz(octaedro, HAB);

    return 0;
}
