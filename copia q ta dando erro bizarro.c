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
        scanf(" %d", &opcao);
        getchar();

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
        scanf(" %d", &opcao);
        getchar();

        switch (opcao){
            case 1:
            printf("Qual o novo valor do teto? ");
            scanf("%d", &inputBonus.teto);
            getchar();
            break;

            case 2:
            printf("Qual o valor de 1 bonus? ");
            scanf("%f", &inputBonus.uvalor);
            getchar();
            break;

            case 3:
            printf("Qual o novo valor para receber bonus? ");
            scanf("%f", &inputBonus.valorBonificado);
            getchar();
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
    fflush(stdin);
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = '\0'; // remove o '\n' do final da string

    if(strlen(cpf) != 11){ // verificação extra para caso cpf não possua 11 numeros
        printf("Erro: CPF deve possuir 11 digitos.\n");
        return;
    }
    for(int i = 0; i < *quantClientes; i++){ //verificar se o cpf já tá cadastrado
        if(strcmp(clientes[i].CPF, cpf) == 0){ // compara o cpf temporario com o cpf dos clientes
            printf("Erro: CPF ja cadastrado.\n");
            return;
        }
    }
    struct tCliente novoCliente; //cria var para novo cliente
    strcpy(novoCliente.CPF, cpf); //copia o cpf temporario para o cpf do novo cliente

    printf("Qual o nome? "); // pede o nome do novo cliente
    fgets(novoCliente.nome, sizeof(novoCliente.nome), stdin);
    novoCliente.nome[strcspn(novoCliente.nome, "\n")] = '\0'; 

    printf("Qual o telefone? "); // pede o telefone do novocliente
    fgets(novoCliente.telefone, sizeof(novoCliente.telefone), stdin);
    novoCliente.telefone[strcspn(novoCliente.telefone, "\n")] = '\0';

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
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = '\0'; 

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
        scanf(" %d", &opcao);
        getchar(); // limpar o '\n' do buffer

        if(opcao == 1){
            char novoCPF[12];
            int duploCpf = 0;

            printf("Qual o novo CPF? ");
            fgets(novoCPF, sizeof(novoCPF), stdin);
            novoCPF[strcspn(novoCPF, "\n")] = '\0';

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
            fgets(clientes[indice].nome, sizeof(clientes[indice].nome), stdin);
            clientes[indice].nome[strcspn(clientes[indice].nome, "\n")] = '\0';
            printf("Nome alterado.\n");
        }
        else if(opcao == 3){
            printf("Qual o novo telefone? ");
            fgets(clientes[indice].telefone, sizeof(clientes[indice].telefone), stdin);
            clientes[indice].telefone[strcspn(clientes[indice].telefone, "\n")] = '\0';
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

        printf("EFETIVAR COMPRA\n"); // para saber que entrou na opção de efetivar compra

        printf("Qual o CPF do cliente? ");
        fgets(cpf, sizeof(cpf), stdin);
        cpf[strcspn(cpf, "\n")] = '\0';

        int indice = -1; // flag q armazena o indice do cliente
        for(int i = 0; i < *quantClientes; i++){ // laço para verificar se o cpf já tá cadastrado
            if(strcmp(clientes[i].CPF, cpf) == 0){
                indice = i; // a var indice recebe i q é o cpf do cliente q quer efetivar a compra
                break;
            }
        }
        if(indice == -1){ // caso o cpf não seja encontrado
            printf("Erro: CPF nao cadastrado\n");
            return; // retorna para o menu principal
        }

        struct tCliente *cliente = &clientes[indice];
        int x = cliente -> bonus; // valor do bonus do que o cliente possui 
        float y = cliente -> bonus * inputBonus.uvalor; // valor correspondernte em reais (bonus * valor de 1 bonus)

        printf("Bonus = %d, VALOR CORRESPONDENTE = %.2f\n", x, y); // imprime o valor do bonus e o valor correspondente em reais

        float valorCompra; // valor da compra

        do{
            printf("Qual o valor da compra? R$ ");
            scanf("%f", &valorCompra);
            getchar();

            if(valorCompra <= 0.0){
                printf("“Erro: valor negativo. Digite novamente.\n");
            }
        } while(valorCompra <= 0.0); // obrigar o usuario a digitar um valor positivo

        float valorF = valorCompra;
        if(cliente -> bonus > 0){
            int usarBonus;
            do{
                printf("Deseja usar o bonus? [1- sim, 0- nao] ");
                scanf("%d", &usarBonus);
                getchar();

                if(usarBonus !=0 && usarBonus != 1){
                    printf("Erro: opcao invalida. Digite novamente.\n");
                }
            } while(usarBonus != 0 && usarBonus !=1); // obrigar o usuario a digitar 0 ou 1
            if(usarBonus == 1){
                float descontBonus = y;// descontro do bonus = bonus do cliente * valor de 1 bonus que é y

                if(descontBonus > valorCompra){ // se descontro do bonus for maior que o valor da compra
                    descontBonus = valorCompra; // o valor do desconto do bonus é igual ao valor da compra pq não pode ser maior 
                }
                x = cliente -> bonus;
                valorF -=descontBonus; // valor final = valor da compra - desconto do bonus
                printf("BONUS ATUAL = %d, VALOR da Compra utilizado = %.2f\n", x, valorF);
            }
        }

        float valorPago; // valor do pagamento
        do{
            printf("Qual o valor do pagamento? R$ ");
            scanf("%f", &valorPago);
            getchar();

            if(valorPago <= 0){
                printf("Erro: valor negativo. Digite novamente.\n");
            }
        } while(valorPago <= 0);

        while(valorPago < valorF){
            printf("Erro: Valor do pagamento inferior ao valor da compra. Deseja desisitir da compra?[1-sim <outro valor>-nao]: ");
            int desistir;
            scanf("%d", &desistir);
            getchar();

            if(desistir == 1){
                printf("COMPRA NÃO EFETIVADA. Valor devolvido ao cliente: R$ %.2f.\n", valorPago);
                return;
            }
            printf("Qual o valor do pagamento do cliente? R$ ");
            scanf("%f", &valorPago);
            getchar();
        }
        printf("TROCO = R$ %.2f", valorPago - valorF);

        // atualizar os dados do cliente
        cliente -> uCompra = valorCompra; // ultima compra do cliente
        cliente ->totCompras += valorCompra; // total de compras do cliente

        if(valorF == valorCompra){ // sem usar o bonus
            int novoBonus = (int) (valorCompra / inputBonus.valorBonificado); // novo bonus = valor da compra / valor para receber bonus
            cliente -> bonus += novoBonus; // bonus do cliente = bonus do cliente + novo bonus
            if(cliente -> bonus > inputBonus.teto){
                cliente -> bonus = inputBonus.teto; // se o bonus do cliente for maior que o teto, o bonus do cliente é igual ao teto
            }   
        }
        else{
            float usadoBonus = valorCompra - valorF;
            cliente -> bonus -= (int) (usadoBonus / inputBonus.uvalor);
        }
        printf("Compra realizada com sucesso!\n");
    }

// FUNÇÂO PRINCIPAL
int main(){
    int quantClientes = 0;
    const int maxClientes = 200;
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
        else if(opcao == 4){
            EfetivarCompra(clientes, &quantClientes); // chama a função de efetivar compra
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