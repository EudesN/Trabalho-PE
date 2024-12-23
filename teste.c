#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tCliente {
    char nome[100];
    char CPF[12];
    char telefone[15];
    int bonus;
    float totCompras;
    float uCompra;
};

struct tBonus {
    int teto;
    float uvalor;
    float valorBonificado;
};

struct tBonus inputBonus = {1000, 0.5, 100.0};

struct tCompra {
    float vuCompra;
    int CompraCancel;
    float vuBonus;
};

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int MenuPrincipal() {
    int opcao;
    do {
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
        clearBuffer();
    } while (opcao < 0 || opcao > 9);
    if (opcao == 0) {
        printf("Saindo do programa...\n");
    }
    return opcao;
}

void ConfigurarBonus() {
    int opcao;
    do {
        printf("---------------------------------------------------\n");
        printf("MENU CONFIGURAR BONUS\n");
        printf("1- Alterar teto\n");
        printf("2- Digite o valor do bonus\n");
        printf("3- Alterar valor para receber bonus\n");
        printf("0 - Sair\n");
        printf("---------------------------------------------------\n");

        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        clearBuffer();

        switch (opcao) {
            case 1:
                printf("Qual o novo valor do teto? ");
                scanf("%d", &inputBonus.teto);
                clearBuffer();
                break;
            case 2:
                printf("Qual o valor de 1 bonus? ");
                scanf("%f", &inputBonus.uvalor);
                clearBuffer();
                break;
            case 3:
                printf("Qual o novo valor para receber bonus? ");
                scanf("%f", &inputBonus.valorBonificado);
                clearBuffer();
                break;
            case 0:
                printf("Saindo do menu de configuracao de bonus...\n");
                break;
            default:
                printf("Erro: valor invalido.\n");
                break;
        }
    } while (opcao != 0);
}

void CadastrarCliente(struct tCliente clientes[], int *quantClientes) {
    char cpf[12];

    printf("Qual o CPF? ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = '\0';

    for (int i = 0; i < *quantClientes; i++) {
        if (strcmp(clientes[i].CPF, cpf) == 0) {
            printf("Erro: CPF ja cadastrado.\n");
            return;
        }
    }

    struct tCliente novoCliente;
    strcpy(novoCliente.CPF, cpf);

    printf("Qual o nome? ");
    fgets(novoCliente.nome, sizeof(novoCliente.nome), stdin);
    novoCliente.nome[strcspn(novoCliente.nome, "\n")] = '\0';

    printf("Qual o telefone? ");
    fgets(novoCliente.telefone, sizeof(novoCliente.telefone), stdin);
    novoCliente.telefone[strcspn(novoCliente.telefone, "\n")] = '\0';

    novoCliente.bonus = 0;
    novoCliente.totCompras = 0.0;
    novoCliente.uCompra = 0.0;

    clientes[*quantClientes] = novoCliente;
    (*quantClientes)++;

    printf("Cliente cadastrado com sucesso\n");
}

void AlterarCadastro(struct tCliente clientes[], int *quantClientes) {
    char cpf[12];

    printf("Qual o CPF do cliente? ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = '\0';

    int indice = -1;
    for (int i = 0; i < *quantClientes; i++) {
        if (strcmp(clientes[i].CPF, cpf) == 0) {
            indice = i;
            break;
        }
    }
    if (indice == -1) {
        printf("CPF nao encontrado.\n");
        return;
    }

    int opcao = 0;
    do {
        printf("MENU ALTERAR CLIENTE\n");
        printf("1 - Alterar CPF\n");
        printf("2 - Alterar nome\n");
        printf("3 - Alterar telefone\n");
        printf("0 - Voltar ao menu principal\n");

        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        clearBuffer();

        if (opcao == 1) {
            char novoCPF[12];
            int duploCpf = 0;

            printf("Qual o novo CPF? ");
            fgets(novoCPF, sizeof(novoCPF), stdin);
            novoCPF[strcspn(novoCPF, "\n")] = '\0';

            for (int i = 0; i < *quantClientes; i++) {
                if (strcmp(clientes[i].CPF, novoCPF) == 0) {
                    duploCpf = 1;
                    break;
                }
            }

            if (duploCpf) {
                printf("CPF ja cadastrado.\n");
            } else {
                strcpy(clientes[indice].CPF, novoCPF);
                printf("CPF alterado.\n");
            }
        } else if (opcao == 2) {
            printf("Qual o novo nome? ");
            fgets(clientes[indice].nome, sizeof(clientes[indice].nome), stdin);
            clientes[indice].nome[strcspn(clientes[indice].nome, "\n")] = '\0';
            printf("Nome alterado.\n");
        } else if (opcao == 3) {
            printf("Qual o novo telefone? ");
            fgets(clientes[indice].telefone, sizeof(clientes[indice].telefone), stdin);
            clientes[indice].telefone[strcspn(clientes[indice].telefone, "\n")] = '\0';
            printf("Telefone alterado.\n");
        } else if (opcao == 0) {
            printf("Voltando ao menu principal...\n");
            printf("---------------------------------------------------\n");
        } else {
            printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

int main() {
    int quantClientes = 0;
    const int maxClientes = 200;
    struct tCliente clientes[maxClientes];
    int opcao;

    do {
        opcao = MenuPrincipal();

        if (opcao == 1) {
            ConfigurarBonus();
        } else if (opcao == 2) {
            CadastrarCliente(clientes, &quantClientes);
        } else if (opcao == 3) {
            AlterarCadastro(clientes, &quantClientes);
        } else if (opcao == 0) {
            printf("Fim do programa!\n");
            return 0;
        } else {
            printf("A opcao %d nao foi implementada\n", opcao);
        }
    } while (opcao != 0);

    return 0;
}
