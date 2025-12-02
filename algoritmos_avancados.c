

// Desafio Detective Quest
// Tema 4 - Árvores e Tabela Hash
// Este código inicial serve como base para o desenvolvimento das estruturas de navegação, pistas e suspeitos.
// Use as instruções de cada região para desenvolver o sistema completo com árvore binária, árvore de busca e tabela hash.


    // 🌱 Nível Novato: Mapa da Mansão com Árvore Binária
    //
    // - Crie uma struct Sala com nome, e dois ponteiros: esquerda e direita.
    // - Use funções como criarSala(), conectarSalas() e explorarSalas().
    // - A árvore pode ser fixa: Hall de Entrada, Biblioteca, Cozinha, Sótão etc.
    // - O jogador deve poder explorar indo à esquerda (e) ou à direita (d).
    // - Finalize a exploração com uma opção de saída (s).
    // - Exiba o nome da sala a cada movimento.
    // - Use recursão ou laços para caminhar pela árvore.
    // - Nenhuma inserção dinâmica é necessária neste nível.

    // 🔍 Nível Aventureiro: Armazenamento de Pistas com Árvore de Busca
    //
    // - Crie uma struct Pista com campo texto (string).
    // - Crie uma árvore binária de busca (BST) para inserir as pistas coletadas.
    // - Ao visitar salas específicas, adicione pistas automaticamente com inserirBST().
    // - Implemente uma função para exibir as pistas em ordem alfabética (emOrdem()).
    // - Utilize alocação dinâmica e comparação de strings (strcmp) para organizar.
    // - Não precisa remover ou balancear a árvore.
    // - Use funções para modularizar: inserirPista(), listarPistas().
    // - A árvore de pistas deve ser exibida quando o jogador quiser revisar evidências.

    // 🧠 Nível Mestre: Relacionamento de Pistas com Suspeitos via Hash
    //
    // - Crie uma struct Suspeito contendo nome e lista de pistas associadas.
    // - Crie uma tabela hash (ex: array de ponteiros para listas encadeadas).
    // - A chave pode ser o nome do suspeito ou derivada das pistas.
    // - Implemente uma função inserirHash(pista, suspeito) para registrar relações.
    // - Crie uma função para mostrar todos os suspeitos e suas respectivas pistas.
    // - Adicione um contador para saber qual suspeito foi mais citado.
    // - Exiba ao final o “suspeito mais provável” baseado nas pistas coletadas.
    // - Para hashing simples, pode usar soma dos valores ASCII do nome ou primeira letra.
    // - Em caso de colisão, use lista encadeada para tratar.
    // - Modularize com funções como inicializarHash(), buscarSuspeito(), listarAssociacoes().

  #include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct sala {
    const char* nome;
    struct sala* esquerda;
    struct sala* direita;
} sala;


//função para criar uma nova sala
sala* criarSala(const char* nome) {// aloca memória para uma nova sala
    sala* novaSala = (sala*)malloc(sizeof(sala));
    novaSala->nome = nome;
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

//função para conectar salas
void conectarSalas(sala* sala1, sala* sala2, char direcao) {// conecta duas salas em uma direção especificada
    if (direcao == 'E') {
        sala1->esquerda = sala2;
    } else if (direcao == 'D') {
        sala1->direita = sala2;
    }
}
//função para limpar o buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
//função para explorar as salas
void explorarSalas(sala* salaAtual) {
    printf("----------------------------------\n");
    printf(" --- Estrategia de Exploracao --- \n");
    printf("----------------------------------\n");
    printf("(E)squerda ou (D)ireita para navegar entre as salas\n");
    printf("                             \n");

    char escolha;// variável para armazenar a escolha do usuário
    printf("Voce esta na sala: %s \n", salaAtual->nome);// exibe o nome da sala atual
    printf("Escolha uma direcao (E/D) ou (S) para sair: ");// solicita ao usuário que escolha uma direção
    scanf(" %c", &escolha);// lê a escolha do usuário
    limparBuffer(); // Limpa o buffer de entrada
    if (escolha == 'E' || escolha == 'e') {
        if (salaAtual->esquerda != NULL) {
            printf("Indo para a sala: %s\n", salaAtual->esquerda->nome);
        } else {
            printf("Nao ha sala a esquerda..\n");
            printf("Escolha outra direcao.\n");
            scanf(" %c", &escolha);
        }
    } else if (escolha == 'D' || escolha == 'd' ) {
        if (salaAtual->direita != NULL) {
            printf("Indo para a sala: %s\n", salaAtual->direita->nome);
        } else {
            printf("Nao ha sala a direita..\n");
            printf("Escolha outra direcao.\n");
            scanf(" %c", &escolha);

        }
         } else if (escolha == 'S' || escolha == 's' ) {
            printf("Saindo da exploracao de salas.\n");
            printf("---------------------------------------------\n");
            printf("        Fim da Aventura Detetive Quest       \n");
            printf("---------------------------------------------\n");
            exit(0);// sai da função
        
    } else {
        printf("Direcao invalida. Tente novamente.\n");
    }
}
int main() {
    //cabeçalho do programa
    printf("---------------------------------------------\n");
    printf("           DETETIVE QUEST            \n");
    printf("---------------------------------------------\n");
    printf("Bem-vindo ao jogo Detetive Quest!\n");
    printf("Sua missao e explorar as salas, coletar pistas e resolver o misterio.\n");// descrição do jogo
    printf("---------------------------------------------\n");

    printf("Aperte Enter para iniciar sua aventura!\n");
    getchar(); // Espera o usuário pressionar Enter

    // Criando salas
    sala* halldeentrada = criarSala("hall de entrada");
    sala* biblioteca = criarSala("biblioteca");
    sala* cozinha = criarSala("cozinha");
    sala* saladeestar = criarSala("sala de estar");
    sala* sotao = criarSala("sotao");
    
    conectarSalas(halldeentrada, biblioteca, 'E');// Conecta hall de entrada à biblioteca à esquerda
    conectarSalas(biblioteca, cozinha, 'D');// Conecta biblioteca à cozinha à direita
    conectarSalas(halldeentrada, saladeestar    , 'E');// Conecta hall de entrada à sala de estar à esquerda
    conectarSalas(saladeestar, sotao, 'D');// Conecta sala de estar ao sotao à direita


    // Liberando memoria
    free(halldeentrada);
    free(biblioteca);
    free(cozinha);
    free(saladeestar);
    free(sotao);
    
    //menu de opcões
    int opcao;
    printf("---------------------------------------------\n");
    printf("           MENU DE OPCOES            \n");
    printf(" \n");
    printf("1. Explorar Salas\n");
    printf("2. Sair\n");
    printf("---------------------------------------------\n");
    printf("Escolha uma opcao:                        \n");
    scanf("%d", &opcao);
    limparBuffer(); // Limpa o buffer de entrada

    switch (opcao) {
        case 1: {
            // Loop para explorar salas até o usuário decidir sair
            while (1) {
            explorarSalas(halldeentrada);
            explorarSalas(biblioteca);
            explorarSalas(cozinha);
            explorarSalas(saladeestar);
            explorarSalas(sotao);
        }
            break;
        }
        case 2:
            printf("Saindo do jogo. Ate a proxima!\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
    }

    //fim do programa
    printf("---------------------------------------------\n");
    printf("        Fim da Aventura Detetive Quest       \n");
    printf("---------------------------------------------\n");
    return 0;
}

