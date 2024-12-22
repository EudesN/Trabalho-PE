# include <stdio.h>
# include <stdlib.h>
# include <string.h>

struct tCliente{
    char nome[100]; // 99 caracteres + '\0'
    char CPF[12]; // 11 digitos + '\0'
    char telefone[15]; // 14 digitos + '\0'
    int bonus;
    float totCompras;
    float uCompra; // ultima compra
};

struct tBonus{
    int teto;
    float uvalor; // valor de 1 bonus
    float valorBonificado;
};

struct tBonus inputBonus = {1000, 0.5, 100.0}; // 'inputBonus' é uma variável do tipo tBonus que dá inicio a estrutura tBonus com os valores padrões respectivos

struct tCompra{
    float vuCompra;
    int CompraCancel; // 0 = não cancelada, 1 = cancelada (iniciar com não cancelada)
    float vuBonus; // valor de 1 bonus quando essa compra foi realizada
};

int MenuPrincipal(){ // Menu Principal
    int opcao; // opção de escolha do menu principal
    do{
        printf("---------------------------------------------------\n");
        printf("MENU PRINCIPAL\n");
        printf("---------------------------------------------------\n");
        printf("1- Configurar Bonus\n");
        printf("2- Cadastrar Cliente\n");
        printf("3- Alterar dados do Cliente\n");
        printf("4- Efetivar Compra\n"); 
        printf("5- Cancelar Compra\n");
        printf("6- Consultar Bonus\n");
        printf("7- Listar dados de todos os clientes\n");
        printf("8- Listar bonus de todos cliente\n");
        printf("9- Listar clientes pelo valor total de compras\n");
        printf("0- Sair\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 9); // obriga o usuário a digitar uma opção de 0 a 9
    if(opcao == 0){
        printf("Saindo do programa...\n");
    }
    return opcao;
}

// Função para configurar o bonus
void ConfigurarBonus(){ 
    int opcao; // opção de escolha do menu de configuração de bonus
    do{
        printf("MENU CONFIGURAR BONUS\n");
        printf("1- Alterar teto\n");
        printf("2- Digite o valor do bonus\n");
        printf("3- Alterar valor para receber bonus\n");
        printf("0 - Sair\n");
        scanf("%d", &opcao);

        switch (opcao){
            case 1:
            printf("Qual o novo valor do teto? ");
            scanf("%d", &inputBonus.teto);
            break;

            case 2:
            printf("Qual o valor de 1 bonus? ");
            scanf("%f", &inputBonus.uvalor);
            break;

            case 3:
            printf("Qual o novo valor para receber bonus? ");
            scanf("%f", &inputBonus.valorBonificado);
            break;
            case 0:
            printf("Saindo do menu de configuracao de bonus...\n");
            break;

            default:
            printf("Erro: valor negativo.\n");
            break;
        }
    }while(opcao != 0);
}

// Função para cadastrar um cliente
void CadastrarCliente(struct tCliente clientes[], int *quantClientes){
    char cpf[12]; // var temporario q armazena cpf

    printf("Qual o CPF? "); // solicita o cpf temporario
    scanf(" %s", cpf);

    for(int i = 0; i < *quantClientes; i++){ //verificar se o cpf já tá cadastrado
        if(strcmp(clientes[i].CPF, cpf) == 0){ // compara o cpf temporario com o cpf dos clientes
            printf("Erro: CPF ja cadastrado.\n");
            printf("---------------------------------------------------\n");
            return;
        }
    }
    struct tCliente novoCliente; //cria var para novo cliente
    strcpy(novoCliente.CPF, cpf); //copia o cpf temporario para o cpf do novo cliente

    printf("Qual o nome?"); // pede o nome do novo cliente
    scanf(" %[^\n]s", novoCliente.nome); 

    printf("Qual o telefone?"); // pede o telefone do novocliente
    scanf("%s", novoCliente.telefone);

    novoCliente.bonus = 0;
    novoCliente.totCompras = 0.0;
    novoCliente.uCompra = 0.0;

    clientes[*quantClientes] = novoCliente;
    (*quantClientes)++;

    printf("Cliente cadastrado com sucesso\n");
    printf("---------------------------------------------------\n");
}

// função principal que executa as funções secundarias
int main(){
    int quantClientes = 0;
    const int maxClientes = 100;
    struct tCliente clientes[maxClientes];
    
    int opcao;

    do{
        opcao = MenuPrincipal(); // chama a função MenuPrincipal

        // etapa que verifica a opção escolhida no MenuPrincipal
        if(opcao == 1){
            ConfigurarBonus(); // chama a função ConfigurarBonus
        }
        else if(opcao == 2){
            CadastrarCliente(clientes, &quantClientes); // chama a função CadastrarCliente
        }
        else if(opcao == 0){
            printf("Fim do programa!\n");
            return 0;
        }
        else{
            printf("A opcao %d nao foi implementada\n", opcao);
        }
    }while(opcao != 0);

    return 0;
}