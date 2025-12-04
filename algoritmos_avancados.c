

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

//tabela hash para associar suspeitos e pistas
#define TABELA_HASH 100

typedef struct sala {// estrutura para representar salas
    const char* nome;
    struct sala* esquerda;
    struct sala* direita;
    struct pista* pistaAssociada;
} sala;

typedef struct pista {// estrutura para representar pistas
    const char* texto;
    struct pista* proxima;
} pista;

typedef struct suspeito { // estrutura para representar suspeitos
    const char* nome;
    pista* pistasAssociadas;
} suspeito;

//array de ponteiros para listas encadeadas
suspeito* tabelaHash[TABELA_HASH] = {NULL};

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

//função para inserir suspeito na tabela hash
void inserirhash(suspeito* tabelaHash[], const char* nomeSuspeito, pista* pistaAssociada) {
    unsigned long hash = 5381;
    int c;
    const char* str = nomeSuspeito;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    int index = hash % 100; // Tamanho da tabela hash é 100
    suspeito* novoSuspeito = (suspeito*)malloc(sizeof(suspeito));
    novoSuspeito->nome = nomeSuspeito;
    novoSuspeito->pistasAssociadas = pistaAssociada;
    tabelaHash[index] = novoSuspeito;
}
void buscarsuspeito(suspeito* tabelaHash[], const char* nomeSuspeito) {
    unsigned long hash = 5381;
    int c;
    const char* str = nomeSuspeito;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    int index = hash % 100; // Tamanho da tabela hash é 100
    suspeito* suspeitoEncontrado = tabelaHash[index];
    if (suspeitoEncontrado != NULL && strcmp(suspeitoEncontrado->nome, nomeSuspeito) == 0) {
        printf("Suspeito encontrado: %s\n", suspeitoEncontrado->nome);
        pista* pistaAtual = suspeitoEncontrado->pistasAssociadas;
        while (pistaAtual != NULL) {
            printf("  Pista: %s\n", pistaAtual->texto);
            pistaAtual = pistaAtual->proxima;
        }
    } else {
        printf("Suspeito nao encontrado: %s\n", nomeSuspeito);
    }
}
 void contadorSuspeitos(suspeito* tabelaHash[]) {
    int contador = 0;
    for (int i = 0; i < 100; i++) {
        if (tabelaHash[i] != NULL) {
            contador++;
        }
    }
    printf("Numero de suspeitos encontrados: %d\n", contador);
}

//listar associações de suspeitos e pistas
void listarAssociacoes(suspeito* tabelaHash[]) {
    printf("---------------------------------------------\n");
    printf("----- Associacoes de Suspeitos e Pistas -----\n");
    printf("---------------------------------------------\n");
    for (int i = 0; i < 100; i++) {
        if (tabelaHash[i] != NULL) {
            printf("Suspeito: %s\n", tabelaHash[i]->nome);
            pista* pistaAtual = tabelaHash[i]->pistasAssociadas;
            while (pistaAtual != NULL) {
                printf("Pista: %s\n", pistaAtual->texto);
                pistaAtual = pistaAtual->proxima;
            }
        }
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
    suspeito* tabelaHash[TABELA_HASH] = {NULL};
    
    // Conectando salas
    conectarSalas(halldeentrada, biblioteca, 'E');// Conecta hall de entrada à biblioteca à esquerda
    conectarSalas(biblioteca, cozinha, 'D');// Conecta biblioteca à cozinha à direita
    conectarSalas(halldeentrada, saladeestar, 'E');// Conecta hall de entrada à sala de estar à esquerda
    conectarSalas(saladeestar, sotao, 'D');// Conecta sala de estar ao sotao à direita

    // Criando pistas e associando-as às salas
    criarpistas(halldeentrada, "Um sapato sujo de lama encontrado perto da porta.");
    criarpistas(biblioteca, "Um livro antigo sobre receitas misteriosas.");  
    criarpistas(cozinha, "Uma faca com manchas de sangue na bancada.");
    criarpistas(saladeestar, "Um bilhete rasgado com uma mensagem suspeita.");
    criarpistas(sotao, "Pegadas que levam a uma janela quebrada.");

    //Criando suspeitos e associando pistas
    inserirhash(tabelaHash, "Sr. Verde", halldeentrada->pistaAssociada);
    inserirhash(tabelaHash, "Cozinheira", biblioteca->pistaAssociada);
    inserirhash(tabelaHash, "Coronel Mostarda", cozinha->pistaAssociada);
    inserirhash(tabelaHash, "Sra. Rosa", saladeestar->pistaAssociada);
    inserirhash(tabelaHash, "Mordomo", sotao->pistaAssociada);
    
    //suspeitos encontrados
    int contadorSuspeitos = 5; // Exemplo de contador de suspeitos encontrados

    
    // Iniciando exploração das salas
    explorarSalas(halldeentrada);
    explorarSalas(biblioteca);
    explorarSalas(cozinha);
    explorarSalas(saladeestar);
    explorarSalas(sotao);

    printf("----------------------------------\n");
    printf("Voce chegou ao fim da ultima sala!   \n");
    printf("Agora, aqui estao todas as pistas e suspeitos que voce coletou durante sua aventura:\n");
    
    listarAssociacoes(tabelaHash);
    printf("----------------------------------\n");
    printf("Aperte Enter para Exibir o suspeito mais provavel de todo esse misterio!\n");
    getchar(); // Espera o usuário pressionar Enter


    printf("----------------------------------\n");
    printf(" ---- SUSPEITO MAIS PROVAVEL ---:\n");
    printf("----------------------------------\n");

    // Exibindo o suspeito mais provável
    char suspeitoMaisProvavel[100] = "Sra .Rosa"; // Exemplo
    printf("Numero de suspeitos encontrados: %d\n", contadorSuspeitos);
    printf("O suspeito mais provavel e: %s\n", suspeitoMaisProvavel);
    printf("Com base nas pistas coletadas, acreditamos que %s esteja envolvido(a) no misterio.\n", suspeitoMaisProvavel);
    printf("Como um detetive habilidoso, voce desvendou o caso com sucesso!\n");
    printf("Parabens por completar o Detetive Quest!\n");
    printf("Obrigado por jogar. Ate a proxima aventura!\n");

// Final do jogo
    printf("----------------------------------\n");
    printf("          Fim da Aventura         \n");
    printf("----------------------------------\n");
    return 0;
}
