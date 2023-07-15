/*
 * Trabalho feito para a disciplina Introdução a Ciência da Computação 1
 * Professor: Rudinei Goulart
 * Integrantes: Isabela Farias - NUSP: 13823833
 *              Nicolas Carreiro - NUSP: 14600801
 * Descrição: Um mercadinho deseja manter seu estoque informatizado e utilizar um sistema para realizar suas vendas, consultas ao estoque e ao saldo atual do caixa. Para isso foi impletado 8 funções (contando com a main), cada função possui um comando especifico escolhido pelo o usuário. O objetivo desse código é implementar um sistema simples de gerenciamento de estoque e vendas. O programa permite a inserção de produtos no estoque, aumentar a quantidade de um produto, modificar o preço de um produto, realizar vendas e consultar o estoque e o saldo do caixa. O programa utiliza um arquivo para armazenar os dados do caixa e do estoque. Ao iniciar, o programa verifica se o arquivo existe. Se existir, ele lê os valores do caixa e dos produtos armazenados no estoque. Se o arquivo não existir, o usuário é solicitado a informar o tamanho do estoque e o valor inicial do caixa.
*/


#include <stdio.h> // biblioteca básica de input e output do C
#include <stdlib.h> //biblioteca para uso de locação dinâmica de memória
#include <string.h> //biblioteca para manipulação de string

/*Essa parte do código define uma estrutura chamada Produto usando a palavra-chave typedef. A estrutura Produto é usada para armazenar informações sobre um produto, incluindo o nome do produto, a quantidade em estoque e o preço do produto.
A estrutura possui três campos:
*nome: Um array de caracteres com tamanho máximo de 100. Ele armazena o nome do produto.
*quantidade: Um inteiro que representa a quantidade disponível desse produto em estoque.
*preco: Um valor (float) que armazena o preço do produto.
Essa estrutura é usada em várias partes do código para representar os produtos do estoque. Cada variavel tipo Produto contém os detalhes de um único produto, como seu nome, quantidade e preço.*/
typedef struct
{
    char nome[100];
    int quantidade;
    float preco;
} Produto;
Produto;

// Protótipos das funções
void linha();
void InserirProduto(Produto **estoque, int *tamanho, char *nome, int quantidade, float preco, int *max);
void aumentarEstoque(Produto *estoque, int tamanho, int codigo, int quantidade);
void modificarPreco(Produto *estoque, int tamanho, int codigo, float preco);
void Venda(Produto *estoque, int tamanho, float *caixa, int *codigoProdutos);
void consultarEstoque(Produto *estoque, int tamanho);
void consultarSaldo(float saldo);
void FinalizarExpediente(float caixa, Produto *estoque, int tam);

// Esta função linha() é responsável por imprimir uma linha de caracteres de separação. Ela utiliza um loop for para imprimir o caractere "-" 50 vezes e, em seguida, imprime uma quebra de linha para avançar para a próxima linha. Assim não será preciso colocar o traço cinquenta vezes o que facilita na vizualição e efetividade do código. 
void linha()
{
    for (int i = 0; i < 50; i++)
    {
        printf("-");
    }
    printf("\n");
}

/*Essa função InserirProduto() permite adicionar um novo produto ao estoque. Ela recebe um ponteiro para o ponteiro do estoque (estoque), um ponteiro para o tamanho atual do estoque (tamanho), uma string contendo o nome do produto (nome), um inteiro representando a quantidade do produto (quantidade), um valor de ponto flutuante representando o preço do produto (preco), e um ponteiro para o tamanho máximo do estoque (max).
A função cria uma nova estrutura Produto chamada novoProduto e preenche seus campos com os valores fornecidos. Em seguida, ela verifica se o tamanho atual do estoque é maior ou igual ao tamanho máximo permitido (aquele valor anterioarmente digitado pelo usuário). Se for, é feita uma realocação de memória para aumentar o tamanho do estoque em 1, garantindo espaço para o novo produto.
Após a realocação, o novo produto é adicionado ao final do estoque e o tamanho do estoque é incrementado.*/

void InserirProduto(Produto **estoque, int *tamanho, char *nome, int quantidade, float preco, int *max)
{
    Produto novoProduto;
    strcpy(novoProduto.nome, nome);
    novoProduto.quantidade = quantidade;
    novoProduto.preco = preco;

    if (*tamanho >= *max)
    {
        Produto *novoEstoque = (Produto *)realloc(*estoque, (*tamanho + 1) * sizeof(Produto));
        //Verifica se há memória para o alocamento
        if (novoEstoque == NULL)
        {
            printf("Erro ao alocar memória.\n");
            return;
        }
        *estoque = novoEstoque;
    }
    (*estoque)[*tamanho] = novoProduto;
    (*tamanho)++;
}
/*A função aumentarEstoque() permite aumentar a quantidade de um produto existente no estoque. Ela recebe o estoque (estoque), o tamanho do estoque (tamanho), o código do produto a ser aumentado (codigo) e a quantidade a ser adicionada (quantidade). A função verifica se o código está dentro dos limites válidos (entre 0 e tamanho -1) e, se estiver, incrementa a quantidade do produto correspondente.*/

void aumentarEstoque(Produto *estoque, int tamanho, int codigo, int quantidade)
{
    if (codigo >= 0 && codigo < tamanho)
    {
        estoque[codigo].quantidade += quantidade;
    }
}

/*A função modificarPreco() permite modificar o preço de um produto existente no estoque. Ela recebe o estoque (estoque), o tamanho do estoque (tamanho), o código do produto a ser modificado (codigo) e o novo preço (preco). A função verifica se o código está dentro dos limites válidos (entre 0 e tamanho -1) e, se estiver, atualiza o preço do produto correspondente.*/

void modificarPreco(Produto *estoque, int tamanho, int codigo, float preco)
{
    if (codigo >= 0 && codigo < tamanho)
    {
        estoque[codigo].preco = preco;
    }
}

/*A função Venda() permite realizar uma venda de produtos do estoque. Ela recebe o estoque (estoque), o tamanho do estoque (tamanho), um ponteiro para o saldo do caixa (caixa) e um ponteiro para o array de códigos dos produtos vendidos (codigoProdutos). A função percorre o array de códigos de produtos até encontrar o valor -1, indicando o final dos códigos. Para cada código válido, verifica se o código está dentro dos limites válidos do estoque e se a quantidade disponível é maior que zero. Se as condições forem atendidas, imprime o nome e o preço do produto vendido, atualiza o total da venda, decrementa a quantidade disponível do produto no estoque. No final, imprime o total da venda, atualiza o saldo do caixa e imprime uma linha de separação.*/

void Venda(Produto *estoque, int tamanho, float *caixa, int *codigoProdutos)
{
    float total = 0.0;
    int codigo;
    int i = 0;
    while (codigoProdutos[i] != -1)
    {
        codigo = codigoProdutos[i];
        if (codigo >= 0 && codigo < tamanho && estoque[codigo].quantidade > 0)
        {
            printf("%s %.2f\n", estoque[codigo].nome, estoque[codigo].preco);
            total += estoque[codigo].preco;
            estoque[codigo].quantidade--;
        }
        i++;
    }
    printf("Total: %.2f\n", total);
    (*caixa) += total;
    linha();
}
/*A função consultarEstoque() permite consultar o estoque atual. Ela recebe o estoque (estoque) e o tamanho do estoque (tamanho). A função percorre o estoque e imprime o índice do produto, o nome do produto e a quantidade disponível. Após imprimir todos os produtos, é chamada a função linha() para imprimir uma linha de separação.*/

void consultarEstoque(Produto *estoque, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        printf("%d %s %d\n", i, estoque[i].nome, estoque[i].quantidade);
    }
    linha();
}

/*A função consultarSaldo() permite consultar o saldo atual do caixa. Ela recebe apenas o saldo (saldo) e imprime o saldo formatado com duas casas decimais e, em seguida, chama a função linha() para imprimir uma linha de separação.*/
void consultarSaldo(float saldo)
{
    printf("Saldo: %.2f\n", saldo);
    linha();
}



/*A função FinalizarExpediente é responsável por finalizar o expediente, salvando os dados do caixa e do estoque em um arquivo. Ela recebe o saldo total no final do expediente (caixa), o estoque (estoque), o tamanho do estoque (tam). Após isso ela abre o arquivo no modo de escrita ("w") usando a função fopen e verifica se o arquivo foi aberto com sucesso. Se sim, escreve o valor do caixa e o tamanho do estoque no arquivo usando a função fprintf e em seguida, usando um loop for, escreve os dados de cada produto no estoque no arquivo. Após escrever todos os dados, fecha o arquivo usando a função fclose. Agora Se ocorrer algum erro ao abrir ou escrever no arquivo, exibe uma mensagem de erro usando printf. Essa função é essencial para garantir a persistência dos dados do caixa e do estoque entre diferentes execuções do programa, permitindo que os dados sejam recuperados posteriormente.*/
void FinalizarExpediente(float caixa, Produto *estoque, int tam)
{
    FILE *arquivo;
    arquivo = fopen("dados.txt", "w");
    
    if (arquivo != NULL)
    {
        // Escreve o valor do caixa e o tamanho do estoque no arquivo
        fprintf(arquivo, "%.2f %d\n", caixa, tam);
        
        // Escreve os dados de cada produto no arquivo
        for (int i = 0; i < tam; i++)
        {
            fprintf(arquivo, "%s %d %.2f\n", estoque[i].nome, estoque[i].quantidade, estoque[i].preco);
        }
        
        fclose(arquivo);
    }
    else
    {
        printf("Erro ao salvar os dados.\n");
    }
}


 //Função principal do programa. Realiza a execução do sistema de controle de estoque.
 
int main()
{
    int tamanhoEstoque = 0;          // Variável para armazenar o tamanho atual do estoque
    float caixa = 0;                // Variável para armazenar o valor total do caixa
    int espacoEstoque = 0;          // Variável para armazenar o tamanho máximo do estoque

    Produto *estoque = NULL;        // Ponteiro para o array de estruturas Produto que representa o estoque
    char comando[3];                // Variável para armazenar o comando digitado pelo usuário
    
    FILE *arquivo;                  // Ponteiro para o arquivo

    // Verifica se existe um arquivo de dados e tenta lê-lo
    arquivo = fopen("dados.txt", "r");
    if (arquivo != NULL)
    {
        // Lê o valor do caixa do arquivo e o tamanho do estoque
        fscanf(arquivo, "%f %d", &caixa, &espacoEstoque);

        estoque = (Produto *)malloc(espacoEstoque * sizeof(Produto));
        //Verifica se há memória para o alocamento
        if (estoque == NULL)
        {
            printf("Erro ao alocar memória.\n");
            return 1;
        }

        // Enquanto o arquivo não estiver vazio o programa lê os dados dos produtos do arquivo e insere no estoque. Esse caso é usado para quando há registros do dia anterior.
        while (1)
        {
            Produto novoProduto;
            int result = fscanf(arquivo, "%s %d %f", novoProduto.nome, &novoProduto.quantidade, &novoProduto.preco);
            if (result != 3)
            {
                break;
            }
            InserirProduto(&estoque, &tamanhoEstoque, novoProduto.nome, novoProduto.quantidade, novoProduto.preco, &espacoEstoque);
        }

        // Verifica se chegou ao final do arquivo
        if (feof(arquivo))
        {
            fclose(arquivo);
        }
        else 
        {
            printf("Erro ao ler os dados do arquivo.\n");
            return 1;
        }


    }
    else
    {
        
        // Caso o arquivo não exista ou esteja vazio, é solicitado ao usuário o tamanho do estoque e o valor inicial do caixa
        scanf("%d", &espacoEstoque);
        estoque = (Produto *)malloc(espacoEstoque * sizeof(Produto));
        //Verifica se há memória para o alocamento
        if (estoque == NULL)
        {
            printf("Erro ao alocar memória.\n");
            return 1;
        }
        scanf("%f", &caixa);
    }

    // Loop principal do programa. É um loop infinito em que só existe uma condição de parada nesse caso um break que só ocorre quando o usário digita FE, função que finaliza o expediente
    while (1)
    {
        // Lê o comando digitado pelo usuário
        scanf("%s", comando);

        // Verifica o comando digitado e executa a ação correspondente
        if (strcmp(comando, "IP") == 0) //Esse comando é para inserir um novo produto
        {
            
            char nome[100];
            int quantidade;
            float preco;

            scanf("%s %d %f", nome, &quantidade, &preco);
            //Ápos ler todas as informações do produto o programa é levado para a função de inserir produto. 
            InserirProduto(&estoque, &tamanhoEstoque, nome, quantidade, preco, &espacoEstoque);

        }
        else if (strcmp(comando, "AE") == 0)// Comando para aumentar a quantidade de um produto no estoque
        {
            
            int codigo, quantidade;
            scanf("%d %d", &codigo, &quantidade);
            aumentarEstoque(estoque, tamanhoEstoque, codigo, quantidade);
        }
        else if (strcmp(comando, "MP") == 0)// Comando para modificar o preço de um produto no estoque
        {
            
            int codigo; //inteiro para armazenar o código de um produto durante a leitura dos códigos dos produtos vendidos.
            float preco;
            scanf("%d %f", &codigo, &preco);
            modificarPreco(estoque, tamanhoEstoque, codigo, preco);
        }
        else if (strcmp(comando, "VE") == 0)// Comando para realizar uma venda
        {
            int codigo; // inteiro para armazenar o código de um produto durante a leitura dos códigos dos produtos vendidos.
            int i = 0;//contador utilizado para percorrer o array `codigoProdutos` e armazenar os códigos dos produtos.
            int *codigoProdutos = NULL; // ponteiro para um array de inteiros que armazenará os códigos dos produtos vendidos. É alocado dinamicamente com tamanho `tamanhoEstoque` para garantir que tenha espaço suficiente para armazenar todos os códigos.
            int *listatemp = NULL;

            /* - Dentro de um loop while infinito, é lido um código de produto usando a função scanf. Se o código lido for igual a -1, significa que não há mais produtos a serem vendidos, e o loop é interrompido com a instrução `break`. Caso contrário, o código é armazenado no array codigoProdutos na posição i, e o contador i é incrementado.*/
            while (1)
            {
                listatemp = (int *)realloc (codigoProdutos, (i+1) * sizeof(int));
                if (listatemp == NULL) {
                    printf("Erro ao alocar memória.\n");
                    free(listatemp);
                }

                scanf("%d", &codigo);
                if (codigo == -1)
                {
                    break;
                }
                codigoProdutos = listatemp;
                codigoProdutos[i] = codigo;
                i++;
            }
            /*Após o loop de leitura dos códigos, é atribuído o valor -1 à próxima posição do array codigoProdutos, indicando o fim da lista de códigos. O array codigoProdutos será passado como argumento para a função Venda.*/
            codigoProdutos[i] = -1;
            /*- A função Venda é chamada, passando o estoque de produtos (estoque), o tamanho do estoque (tamanhoEstoque), o valor do caixa (caixa) por referência e o array codigoProdutos. A função Venda realiza o processamento da venda dos produtos de acordo com os códigos fornecidos e atualiza o valor do caixa*/
            Venda(estoque, tamanhoEstoque, &caixa, codigoProdutos);

            free(listatemp);
        }
        else if (strcmp(comando, "CE") == 0)// Comando para consultar o estoque
        {
            
            consultarEstoque(estoque, tamanhoEstoque);
        }
        else if (strcmp(comando, "CS") == 0) // Comando para consultar o saldo do caixa
        {
           
            consultarSaldo(caixa);
        }
        else if (strcmp(comando, "FE") == 0)// Comando para finalizar o expediente e salvar os dados
        {
            
            FinalizarExpediente(caixa, estoque, tamanhoEstoque);
            break; //finalmente aqui há o fim do while infinito.
        }
    }

    // Libera a memória alocada para o estoque
    free(estoque);

    return 0;
}
