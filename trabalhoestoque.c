#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[100];
    int quantidade;
    float preco;
} Produto;


void linha (){
    for (int i = 0; i < 50; i++){
        printf("-");
    }

}
void InserirProduto(Produto** estoque, int* tamanho, char* nome, int quantidade, float preco, int* max) {
    Produto novoProduto;
    strcpy(novoProduto.nome, nome);
    novoProduto.quantidade = quantidade;
    novoProduto.preco = preco;
    
    if (*tamanho >= *max){
        (*estoque) = (Produto*)realloc(*estoque, (*tamanho + 1) * sizeof(Produto));
        (*max)++;
    }
    (*estoque)[*tamanho] = novoProduto;
    (*tamanho)++;
}

void aumentarEstoque(Produto* estoque, int tamanho, int codigo, int quantidade) {
    if (codigo >= 0 && codigo < tamanho) {
        estoque[codigo].quantidade += quantidade;
    }
}

void modificarPreco(Produto* estoque, int tamanho, int codigo, float preco) {
    if (codigo >= 0 && codigo < tamanho) {
        estoque[codigo].preco = preco;
    }
}

void consultarEstoque(Produto* estoque, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d %s %d\n", i, estoque[i].nome, estoque[i].quantidade);
    }
    linha();

}

void consultarSaldo(int saldo){
    printf("Saldo: %d\n", saldo);
    linha();
}

finalizarExpediente(Produto* estoque, int tam, float caixa){
    FILE* arquivo;
    
}

int main() {
    int tamanhoEstoque = 0;
    float caixa = 0;
    int espacoEstoque = 0;

    Produto* estoque = NULL;
    char comando[3];


    FILE* arquivo;
    arquivo = fopen("dados.txt", "r");
    if (arquivo != NULL) {
        fscanf(arquivo, "%f", &caixa);
        while (!feof(arquivo)) {
            Produto novoProduto;
            fscanf(arquivo, "%s %d %f", novoProduto.nome, &novoProduto.quantidade, &novoProduto.preco);
            InserirProduto(&estoque, &tamanhoEstoque, novoProduto.nome, novoProduto.quantidade, novoProduto.preco, &espacoEstoque);
        }
        fclose(arquivo);
    } else {
        scanf("%d", &espacoEstoque);
        estoque = (Produto*)malloc(espacoEstoque * sizeof(Produto));
        scanf("%f", &caixa);
    }

    while (1) {
        scanf("%s", comando);

        if (strcmp(comando, "IP") == 0) {
            char nome[100];
            int quantidade;
            float preco;
            scanf("%s %d %f", nome, &quantidade, &preco);
            
            InserirProduto(&estoque, &tamanhoEstoque, nome, quantidade, preco, &espacoEstoque);
        } else if (strcmp(comando, "AE") == 0) {
            int codigo, quantidade;
            scanf("%d %d", &codigo, &quantidade);

            aumentarEstoque(estoque, tamanhoEstoque, codigo, quantidade);
        } else if (strcmp(comando, "MP") == 0) {
            int codigo;
            float preco;
            scanf("%d %f", &codigo, &preco);
            
            modificarPreco(estoque, tamanhoEstoque, codigo, preco);
        } else if (strcmp(comando, "VE") == 0) {
            
        } else if (strcmp(comando, "CE") == 0) {
            consultarEstoque(estoque, tamanhoEstoque);
        } else if (strcmp(comando, "CS") == 0) {
            consultarSaldo(caixa);
        } else if (strcmp(comando, "FE") == 0) {
            finalizarExpediente(estoque, tamanhoEstoque, caixa);
            break;
        }
    }

    free(estoque);

    return 0;
}