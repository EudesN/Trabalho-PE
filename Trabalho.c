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
        printf("---------------------------------------------------\n");
        printf("MENU CONFIGURAR BONUS\n");
        printf("1- Alterar teto\n");
        printf("2- Digite o valor do bonus\n");
        printf("3- Alterar valor para receber bonus\n");
        printf("0 - Sair\n");
        printf("---------------------------------------------------\n");

        printf("Digite a opcao desejada: ");
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
            return;
        }
    }
    struct tCliente novoCliente; //cria var para novo cliente
    strcpy(novoCliente.CPF, cpf); //copia o cpf temporario para o cpf do novo cliente

    printf("Qual o nome? "); // pede o nome do novo cliente
    scanf(" %[^\n]s", novoCliente.nome); 

    printf("Qual o telefone? "); // pede o telefone do novocliente
    scanf("%s", novoCliente.telefone);

    novoCliente.bonus = 0;
    novoCliente.totCompras = 0.0;
    novoCliente.uCompra = 0.0;

    clientes[*quantClientes] = novoCliente;
    (*quantClientes)++;

    printf("Cliente cadastrado com sucesso\n");
}

// função que altera o cadastro do cliente
void AlterarCadastro(struct tCliente clientes[], int *quantClientes){
    char cpf[12];

    printf("Qual o CPF do cliente?"); // pede o cpf que quer ser alterado
    scanf("%s", cpf);

    int indice = -1; // armazena o indice do cliente
    for(int i = 0; i < *quantClientes; i++){ 
        if (strcmp(clientes[i].CPF, cpf) == 0){
            indice = i;
            break;
        }
    }
    if(indice == -1){
        printf("CPF nao encontrado.\n");
        return;
    }

    int opcao = 0;
    do{
        printf("MENU ALTERAR CLIENTE\n");
        printf("1 - Alterar CPF\n");
        printf("2 - Alterar nome\n");
        printf("3 - Alterar telefone\n");
        printf("0 - Voltar ao menu principal\n");

        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);

        if(opcao == 1){
            char novoCPF[12];
            int duploCpf = 0;

            printf("Qual o novo CPF? ");
            scanf("%s", novoCPF);

            for(int i = 0; i < *quantClientes; i++){
                if(strcmp(clientes[i].CPF, novoCPF) == 0){
                    duploCpf = 1; // se o cpf já estiver cadastrado, altera o flag para 1
                    break;
                }
            }

            if(duploCpf){ // se o flag for 1, imprime a mensagem de cpf já cadastrado
                printf("CPF ja cadastrado.\n");
            }
            else{
                strcpy(clientes[indice].CPF, novoCPF);
                printf("CPF alterado.\n");
            }
        }
        else if(opcao == 2){
            printf("Qual o novo nome? ");
            scanf(" %[^\n]s", clientes[indice].nome);
            printf("Nome alterado.\n");
        }
        else if(opcao == 3){
            printf("Qual o novo telefone? ");
            scanf("%s", clientes[indice].telefone);
            
        }
        else if(opcao == 0){
            printf("Voltando ao menu principal...\n");
            printf("---------------------------------------------------\n");
        }
        else{
            printf("Opcao invalida.\n");
        }
    } while(opcao != 0);
}

    void EfetivarCompra(struct tCliente clientes[], int *quantClientes){
        char cpf[12];

        printf("1 - Qual o CPF do cliente? ");
        printf("2 - Qual o valor da compra?");
        printf("3 - Deseja utilizar o bonus? [1-sim <outro valor> - nao] ");
        printf("4 - Qual a valor de pagamento do cliente? R$");

        
    }

// FUNÇÂO PRINCIPAL
int main(){
    int quantClientes = 0;
    const int maxClientes = 100;
    struct tCliente clientes[maxClientes];
    int opcao;

    do{
        opcao = MenuPrincipal(); // chama a função  do Menu Principal

        // etapa que verifica a opção escolhida no MenuPrincipal
        if(opcao == 1){
            ConfigurarBonus(); // chama a função ConfigurarBonus
        }
        else if(opcao == 2){
            CadastrarCliente(clientes, &quantClientes); // chama a função de cadastrar cliente
        }
        else if(opcao == 3){
            AlterarCadastro(clientes, &quantClientes); //chama a função de alterar cadastro
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