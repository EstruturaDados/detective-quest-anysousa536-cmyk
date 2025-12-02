

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
#include<stdbool.h>

typedef struct sala {
    const char* nome;
    struct sala* esquerda;
    struct sala* direita;
    struct pista* pistaAssociada;
} sala;

typedef struct pista {
    const char* texto;
    struct pista* proxima;
} pista;

// declarações de funções
sala* criarSala(const char* nome);
void conectarSalas(sala* sala1, sala* sala2, char direcao);
void explorarSalas(sala* salaAtual);
void inserirBST(pista** raiz, const char* texto);
void buscarPista(pista* raiz, const char* texto);
void ListarPistas(pista* raiz);
void conectarpistas(sala* sala, const char* textoPista);

//função para criar uma nova sala
sala* criarSala(const char* nome) {// aloca memória para uma nova sala
    sala* novaSala = (sala*)malloc(sizeof(sala));
    novaSala->nome = nome;
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    novaSala->pistaAssociada = NULL;
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
    
    char escolha;// variável para armazenar a escolha do usuário
    printf("Voce esta na sala: %s \n", salaAtual->nome);// exibe o nome da sala atual
    printf("Escolha uma direcao para explorar:\n");
    printf("(E)squerda, (D)ireita, (C)oletar pista ou (S)air\n");
    scanf(" %c", &escolha);           
    limparBuffer(); // Limpa o buffer de entrada
    if (escolha == 'E' || escolha == 'e') {
        if (salaAtual->esquerda != NULL) {
            printf("Indo para a sala: %s\n", salaAtual->esquerda->nome);
        } else {
            printf("Nao ha sala a esquerda..\n");
            printf("Escolha a outra direcao (D).\n");
            scanf(" %c", &escolha);
            printf(" \n");

        }

    } else if (escolha == 'D' || escolha == 'd' ) {
        if (salaAtual->direita != NULL) {
            printf("Indo para a sala: %s\n", salaAtual->direita->nome);
        } else {
            printf("Nao ha sala a direita..\n");
            printf("Escolha a outra direcao (E).\n");
            scanf(" %c", &escolha);
            printf("             \n");
        }

    } else if (escolha == 'C' || escolha == 'c') {
        if (salaAtual != NULL) { 
            printf("Coletando pistas na sala: %s\n", salaAtual->nome);//
            if (salaAtual->pistaAssociada != NULL) {
                printf("----------------------------------------------------\n");
                printf("PISTA COLETADA: %s\n", salaAtual->pistaAssociada->texto);// exibe a pista associada à sala
            } else {
                printf("Nenhuma pista encontrada nesta sala.\n");
            }
        } else {
            printf("Sala invalida.\n");
            printf("              \n");
        }
     // Após coletar a pista, o jogador pode escolher outra ação
        printf("------------------------------------------------------------\n");
        printf("Escolha outra acao.\n");
        printf("(E)squerda ou (D)ireita para navegar entre as salas ou (S) para sair\n");
        scanf(" %c", &escolha);
        printf("                \n");
        limparBuffer(); // Limpa o buffer de entrada

    } else if (escolha == 'S' || escolha == 's') {
        (salaAtual == NULL);
        printf("Saindo da exploracao de salas.\n");
        printf("----------------------------------\n");
        printf("          Fim da Aventura         \n");
        printf("----------------------------------\n");
        exit(0);
    } else {
        printf("Opcao invalida. Tente novamente.\n");
    }
}

//criando pistas
void criarpistas(sala* sala, const char* textoPista) {
    pista* novaPista = (pista*)malloc(sizeof(pista));
    novaPista->texto = textoPista;
    novaPista->proxima = NULL;
    sala->pistaAssociada = novaPista;
}

//Exibir pistas em ordem alfabética
void ListarPistas(pista* raiz) {
    if (raiz != NULL) {
        ListarPistas(raiz->proxima);
        printf("Pista: %s\n", raiz->texto);
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
    
    // Conectando salas
    conectarSalas(halldeentrada, biblioteca, 'E');// Conecta hall de entrada à biblioteca à esquerda
    conectarSalas(biblioteca, cozinha, 'D');// Conecta biblioteca à cozinha à direita
    conectarSalas(halldeentrada, saladeestar, 'E');// Conecta hall de entrada à sala de estar à esquerda
    conectarSalas(saladeestar, sotao, 'D');// Conecta sala de estar ao sotao à direita

    // Criando pistas e associando-as às salas
    criarpistas(halldeentrada, "Um sapato sujo de lama encontrado perto da porta.");
    criarpistas(biblioteca, "Um livro antigo sobre venenos misteriosos.");  
    criarpistas(cozinha, "Uma faca com manchas de sangue na bancada.");
    criarpistas(saladeestar, "Um bilhete rasgado com uma mensagem ameaçadora.");
    criarpistas(sotao, "Pegadas que levam a uma janela quebrada.");
    
    // Iniciando exploração das salas
    explorarSalas(halldeentrada);
    explorarSalas(biblioteca);
    explorarSalas(cozinha);
    explorarSalas(saladeestar);
    explorarSalas(sotao);
    printf("----------------------------------\n");
    printf("Voce chegou ao fim da ultima sala!   \n");
    printf("Agora, aqui estao todas as pistas que voce coletou durante sua aventura:\n");
    // Exibindo todas as pistas coletadas em ordem alfabética
    printf("--------------------------------------------------\n");
    printf("   --------    Pistas Coletadas    ----------     \n");
    printf("--------------------------------------------------\n");
    ListarPistas(halldeentrada->pistaAssociada);
    ListarPistas(biblioteca->pistaAssociada);
    ListarPistas(cozinha->pistaAssociada);
    ListarPistas(saladeestar->pistaAssociada);
    ListarPistas(sotao->pistaAssociada);

     printf("----------------------------------\n");
     printf("          Fim da Aventura         \n");
     printf("----------------------------------\n");
    return 0;
}
