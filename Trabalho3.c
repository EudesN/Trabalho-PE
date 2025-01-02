/*
	AUTORES:
	- Francisco Eudes Andrade Nazario
	- Yuri da Silva Barbosa
*/

#include <stdio.h>
#include <string.h>
#include <locale.h>
#define maxClientes 200

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

/* PROTÓTIPOS DAS FUNÇÕES */
int validarCPF(char cpf[], struct tCliente clientes[], int quantClientes);
void configurarBonus();
void cadastrarCliente(struct tCliente clientes[], int *quantClientes);
void alterarCadastro(struct tCliente clientes[], int *quantClientes);
void efetivarCompra(struct tCliente clientes[], int *quantClientes);
void cancelarCompra(struct tCliente clientes[], int *quantClientes);
void consultarBonus(struct tCliente clientes[], int *quantClientes);
void listarClientes(struct tCliente clientes[], int *quantClientes);
void listarBonus(struct tCliente clientes[], int *quantClientes);
void listarClientesPorCompra(struct tCliente clientes[], int *quantClientes);

/* FUNÇÃO PRINCIPAL */
int main(){
	setlocale(LC_ALL, "portuguese");
	
	// struct tBonus inputBonus = {1000, 0.5, 100.0}; // 'inputBonus' é uma variável do tipo tBonus que dá inicio a estrutura tBonus com os valores padrões respectivos
	int quantClientes = 0;
    struct tCliente clientes[maxClientes];
	char opcao[3];
	
	do{
		printf("\nMENU PRINCIPAL\n");
		printf("01 - Configurar bônus\n");
		printf("02 - Cadastrar cliente\n");
		printf("03 - Alterar cadastro do cliente\n");
		printf("04 - Efetivar compra\n");
		printf("05 - Cancelar compra\n");
		printf("06 - Consultar bônus\n");
		printf("07 - Listar dados de todos os clientes\n");
		printf("08 - Listar bônus de todos os clientes\n");
		printf("09 - Listar clientes pelo valor total de compras\n");
		printf("00 - Sair\n\n");
		printf("Digite a opção desejada: ");
		scanf("%s", opcao);
		
		if(strcmp(opcao, "01") == 0 || strcmp(opcao, "1") == 0){
			configurarBonus();
		} else if(strcmp(opcao, "02") == 0 || strcmp(opcao, "2") == 0){
			cadastrarCliente(clientes, &quantClientes);
		} else if(strcmp(opcao, "03") == 0 || strcmp(opcao, "3") == 0){
			alterarCadastro(clientes, &quantClientes);
		} else if(strcmp(opcao, "04") == 0 || strcmp(opcao, "4") == 0){
			efetivarCompra(clientes, &quantClientes);
		} else if(strcmp(opcao, "05") == 0 || strcmp(opcao, "5") == 0){
			cancelarCompra(clientes, &quantClientes);
		} else if(strcmp(opcao, "06") == 0 || strcmp(opcao, "6") == 0){
			consultarBonus(clientes, &quantClientes);
		} else if(strcmp(opcao, "07") == 0 || strcmp(opcao, "7") == 0){
			listarClientes(clientes, &quantClientes);
		} else if(strcmp(opcao, "08") == 0 || strcmp(opcao, "8") == 0){
			listarBonus(clientes, &quantClientes);
		} else if(strcmp(opcao, "09") == 0 || strcmp(opcao, "9") == 0){
			listarClientesPorCompra(clientes, &quantClientes);
		} else if(strcmp(opcao, "00") == 0 || strcmp(opcao, "0") == 0){
			printf("Programa encerrado.\n");
			return 0;
		} else {
			printf("Opcao invalida!\n");
		}
	} while(strcmp(opcao, "00") != 0 || strcmp(opcao, "0") != 0);
	
	return 0;
}

/* 
	Objetivo: função para validar o CPF do cliente 
	Parametros: 
		- char cpf: o CPF que sera inserido pelo usuario
		- struct tCliente clientes[]: vetor do tipo tCliente para armazenar as 
									informações de cada cliente cadastrado
		- int quantClientes: quantidade de clientes cadastrados
	Retotno: retorna 0 caso alguma das condições seja atendida (CPF invalido) 
			 e, caso contrario, retorna 1 (CPF valido) 
*/
int validarCPF(char cpf[], struct tCliente clientes[], int quantClientes){
	if(strlen(cpf) != 11){
		printf("Erro: CPF deve possuir 11 caracteres.\n");
		return 0;
	}
	
	int i;
	for(i = 0; i < 11; i++){
		if(cpf[i] < '0' || cpf[i] > '9'){
			printf("Erro: digite somente numeros.\n");
			return 0;
		}
	}
	
	for(i = 0; i < quantClientes; i++){
		if(strcmp(clientes[i].CPF, cpf) == 0){
			printf("Erro: CPF ja cadastrado.\n");
			return 0;
		}
	}
	
	return 1;
}

/* 
	Objetivo: função para configurar o bonus 
	Parametros: não possui
	Retotno: sem retorno
*/
void configurarBonus(){ 
    int opcao; // opção de escolha do menu de configuração de bonus
    //struct tBonus inputBonus = {1000, 0.5, 100.0};
    
    do{
    //    printf("---------------------------------------------------\n");
        printf("\nMENU CONFIGURAR BONUS\n");
        printf("1- Alterar teto\n");
        printf("2- Digite o valor do bonus\n");
        printf("3- Alterar valor para receber bonus\n");
        printf("0 - Sair\n");
    //    printf("---------------------------------------------------\n");
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

/* 
	Objetivo: função para cadastrar um cliente 
	Parametros: 
		- struct tCliente clientes[]: vetor do tipo tCliente para armazenar as 
									informações de cada cliente cadastrado
		- int *quantClientes: ponteiro que aponta para a quantidade de clientes 
							  cadastrados
	Retotno: sem retorno
*/
void cadastrarCliente(struct tCliente clientes[], int *quantClientes){
    char cpf[12]; // var temporario q armazena cpf
	//int i;
	
    printf("Qual o CPF? "); // solicita o cpf temporario
    scanf(" %s", cpf);

    if(validarCPF(cpf, clientes, *quantClientes) == 0){
		return;
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

/* 
	Objetivo: função para alterar o cadastro de um cliente 
	Parametros: 
		- struct tCliente clientes[]: vetor do tipo tCliente para armazenar as 
									informações de cada cliente cadastrado
		- int *quantClientes: ponteiro que aponta para a quantidade de clientes 
							  cadastrados
	Retotno: sem retorno
*/
void alterarCadastro(struct tCliente clientes[], int *quantClientes){
    char cpf[12];
	int i;
	
    printf("Qual o CPF do cliente?"); // pede o cpf que quer ser alterado
    scanf("%s", cpf);

    int indice = -1; // armazena o indice do cliente
    for(i = 0; i < *quantClientes; i++){ 
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
            int duploCpf = 0, i;

            printf("Qual o novo CPF? ");
            scanf("%s", novoCPF);

            for(i = 0; i < *quantClientes; i++){
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

/* 
	Objetivo: função para efetivar a compra de um produto
	Parametros: 
		- struct tCliente clientes[]: vetor do tipo tCliente para armazenar as 
									informações de cada cliente cadastrado
		- int *quantClientes: ponteiro que aponta para a quantidade de clientes 
							  cadastrados
	Retotno: sem retorno
*/
void efetivarCompra(struct tCliente clientes[], int *quantClientes){
    char cpf[12];
    int /*opcao = 0,*/ i;

    printf("EFETIVAR COMPRA\n"); // para saber que entrou na opção de efetivar compra
    printf("Qual o CPF do cliente? ");
    scanf("%s", cpf);

    int indice = -1; // flag q armazena o indice do cliente
    for(i = 0; i < *quantClientes; i++){ // laço para verificar se o cpf já tá cadastrado
        if(strcmp(clientes[i].CPF, cpf) == 0){
            indice = i; // a var indice recebe i que é o cpf do cliente q quer efetivar a compra
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
        if(valorCompra < 0.0){
            printf("Erro: valor negativo. Digite novamente.\n");
        }
    } while(valorCompra <= 0.0); // obrigar o usuario a digitar um valor positivo

    float valorF = valorCompra;
    if(cliente -> bonus > 0){
        int usarBonus;
        do{
            printf("Deseja usar o bonus? [1- sim, 0- nao] ");
            scanf("%d", &usarBonus);
            if(usarBonus !=0 && usarBonus != 1){
                printf("Erro: opcao invalida. Digite novamente.\n");
            }
        } while(usarBonus != 0 && usarBonus !=1); // obrigar o usuario a digitar 0 ou 1
        if(usarBonus == 1){
            float descontBonus = y;// descontro do bonus = bonus do cliente * valor de 1 bonus que é y

            if(descontBonus > valorCompra){ // se descontro do bonus for maior que o valor da compra
                descontBonus = valorCompra; // o valor do desconto do bonus é igual ao valor da compra pq não pode ser maior 
            }
            
            valorF -=descontBonus; // valor final = valor da compra - desconto do bonus
            printf("BONUS ATUAL = %d. VALOR DA COMPRA ATUALIZADO = %.2f\n", x, valorF);
        }
    }

    float valorPago; // valor do pagamento
    do{
        printf("Qual o valor do pagamento? R$ ");
        scanf("%f", &valorPago);
        if(valorPago <= 0){
            printf("Erro: valor negativo. Digite novamente.\n");
        }
    } while(valorPago <= 0);

    while(valorPago < valorF){
        printf("Erro: Valor do pagamento inferior ao valor da compra. Deseja desisitir da compra? [1-sim, <outro valor>-nao]: ");
        int desistir;
        scanf("%d", &desistir);
        if(desistir == 1){
            printf("COMPRA NÃO EFETIVADA. Valor devolvido ao cliente: R$ %.2f.\n", valorPago);
            return;
        }
        printf("Qual o valor do pagamento do cliente? R$ ");
        scanf("%f", &valorPago);
    }
    printf("TROCO = R$ %.2f. ", valorPago - valorF);

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
    
/* 
	Objetivo: função para cancelar a compra de um produto
	Parametros: 
		- struct tCliente clientes[]: vetor do tipo tCliente para armazenar as 
									informações de cada cliente cadastrado
		- int *quantClientes: ponteiro que aponta para a quantidade de clientes 
							  cadastrados
	Retotno: sem retorno
*/
void cancelarCompra(struct tCliente clientes[], int *quantClientes) {
    char cpf[12];
    int i, indice = -1;

    printf("Qual o CPF do cliente? ");
    scanf(" %s", cpf);

    // Procurar cliente pelo CPF
    for (i = 0; i < *quantClientes; i++) {
        if (strcmp(clientes[i].CPF, cpf) == 0) {
            indice = i;
            break;
        }
    }

    // Caso o CPF não seja encontrado
    if (indice == -1) {
        int opcaoCPF;
        printf("Erro: CPF nao cadastrado. Deseja informar outro CPF [1-sim, <outro valor>-nao]? ");
        scanf("%d", &opcaoCPF);
        if (opcaoCPF == 1) {
            cancelarCompra(clientes, quantClientes); // Tentar novamente
        }
        return;
    }

    struct tCliente *cliente = &clientes[indice];
    int opcaoMenu;

    do {
        printf("\nMENU CANCELA COMPRA\n");
        printf("1 - Ultima compra\n");
        printf("2 - Outra compra\n");
        printf("3 - Exibir dados da ultima compra\n");
        printf("0 - Sair\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcaoMenu);

        switch (opcaoMenu) {
            case 1: {
                // Cancelar a ultima compra
                if (cliente->uCompra == 0.0) {
                    printf("ERRO: Nenhuma compra realizada para ser cancelada!\n");
                    break;
                }

                if (cliente->bonus < 0) {
                    printf("ERRO: Ultima compra já cancelada!\n");
                    break;
                }

                printf("Dados da última compra:\n");
                printf("Valor: R$ %.2f\n", cliente->uCompra);
                printf("Tem certeza que deseja cancelar a última compra? [1-sim, <outro valor>-nao]: ");
                int confirma;
                scanf("%d", &confirma);

                if (confirma == 1) {
                    cliente->totCompras -= cliente->uCompra;
                    cliente->uCompra = 0.0;
                    cliente->bonus -= (int)(cliente->uCompra / inputBonus.valorBonificado);
                    if (cliente->bonus < 0) cliente->bonus = 0;
                    printf("COMPRA CANCELADA!\n");
                } else {
                    printf("COMPRA NÃO CANCELADA!\n");
                }
                break;
            }
            case 2: {
                // Cancelar outra compra
                float valorCompra;
                printf("Qual o valor da compra a ser cancelada? R$ ");
                scanf("%f", &valorCompra);

                if (valorCompra <= 0) {
                    printf("Erro: valor negativo ou zero. Digite novamente.\n");
                    break;
                }

                int bonusDescontar = (int)(valorCompra / inputBonus.valorBonificado) * 2;
                printf("BONUS A SER DESCONTADO = %d. Tem certeza que deseja cancelar a compra? [1-sim, <outro valor>-nao]: ", bonusDescontar);
                int confirma;
                scanf("%d", &confirma);

                if (confirma == 1) {
                    cliente->totCompras -= valorCompra;
                    cliente->bonus -= bonusDescontar;
                    if (cliente->bonus < 0) cliente->bonus = 0;
                    printf("COMPRA CANCELADA!\n");
                } else {
                    printf("COMPRA NÃO CANCELADA!\n");
                }
                break;
            }
            case 3: {
                // Exibir dados da ultima compra
                printf("NOME DO CLIENTE: %s\n", cliente->nome);
                printf("CPF DO CLIENTE: %s\n", cliente->CPF);
                printf("VALOR DA COMPRA: R$ %.2f\n", cliente->uCompra);
                printf("BONUS UTILIZADOS: %d\n", cliente->bonus);
                printf("VALOR DE UM BONUS NA EPOCA DA COMPRA: R$ %.2f\n", inputBonus.uvalor);
                break;
            }
            case 0:
                // Sair do menu
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcaoMenu != 0);
}

/* 
	Objetivo: função para consultar o valor e a quantidade de bonus de um cliente
	Parametros: 
		- struct tCliente clientes[]: vetor do tipo tCliente para armazenar as 
									informações de cada cliente cadastrado
		- int *quantClientes: ponteiro que aponta para a quantidade de clientes 
							  cadastrados
	Retotno: sem retorno
*/
void consultarBonus(struct tCliente clientes[], int *quantClientes){
	char cpf[12];
    int i, indice = -1;

    printf("Qual o CPF do cliente? ");
    scanf(" %s", cpf);

    // Procurar cliente pelo CPF
    for (i = 0; i < *quantClientes; i++) {
        if (strcmp(clientes[i].CPF, cpf) == 0) {
            indice = i;
            break;
        }
    }

    // Caso o CPF não seja encontrado
    if (indice == -1) {
        int opcaoCPF;
        printf("Erro: CPF nao cadastrado. Deseja informar outro CPF [1-sim, <outro valor>-nao]? ");
        scanf("%d", &opcaoCPF);
        if (opcaoCPF == 1) {
            consultarBonus(clientes, quantClientes); // Tentar novamente
        }
        return;
    }
    
    struct tCliente *cliente = &clientes[indice];
    int x = cliente -> bonus; // valor do bonus do que o cliente possui 
    float y = cliente -> bonus * inputBonus.uvalor; // valor correspondernte em reais (bonus * valor de 1 bonus)

    printf("Bonus = %d. VALOR CORRESPONDENTE = %.2f\n", x, y); // imprime o valor do bonus e o valor correspondente em reais
}

/* 
	Objetivo: função para listar todos os clientes cadastrados e seus dados
	Parametros: 
		- struct tCliente clientes[]: vetor do tipo tCliente para armazenar as 
									informações de cada cliente cadastrado
		- int *quantClientes: ponteiro que aponta para a quantidade de clientes 
							  cadastrados
	Retotno: sem retorno
*/
void listarClientes(struct tCliente clientes[], int *quantClientes){
	int i;
	if(*quantClientes == 0){
		printf("\nErro: Não há clientes cadastrados.\n");
		return;
	}
	
	printf("\nRELATORIO DADOS DOS CLIENTES\n\n");
	for(i = 0; i < *quantClientes; i++){
		printf("Nome: %s\n", clientes[i].nome);
		printf("CPF: %s\n", clientes[i].CPF);
		printf("Telefone: %s\n", clientes[i].telefone);
		printf("Bonus: %d\n", clientes[i].bonus);
		printf("Total em compras: R$ %.2f\n", clientes[i].totCompras);
		printf("------------------------------------------------------------\n");
	}
}

void listarBonus(struct tCliente clientes[], int *quantClientes){
	int i;
	if(*quantClientes == 0){
		printf("\nErro: Não há clientes cadastrados.\n");
		return;
	}
	
   	printf("\nRELATORIO DADOS DOS CLIENTES\n\n");
    for(i = 0; i < *quantClientes; i++){
    	float y = clientes[i].bonus * inputBonus.uvalor; // valor correspondernte em reais (bonus * valor de 1 bonus)
		printf("Nome: %s\n", clientes[i].nome);
		printf("CPF: %s\n", clientes[i].CPF);
		printf("Bonus: %d\n", clientes[i].bonus);
		printf("Valor do Bonus: %.2f\n", y);
		printf("------------------------------------------------------------\n");
	}
}

/* 
	Objetivo: função para listar os clientes cadastrados e seus dados de acordo 
			  com uma faixa de valor pre-determinado pelo usuario, baseada no 
			  valor total de compras dos clientes
	Parametros: 
		- struct tCliente clientes[]: vetor do tipo tCliente para armazenar as 
									informações de cada cliente cadastrado
		- int *quantClientes: ponteiro que aponta para a quantidade de clientes 
							  cadastrados
	Retotno: sem retorno
*/
void listarClientesPorCompra(struct tCliente clientes[], int *quantClientes){
	int i, opcao, aux;
	float valor, valorInicial, valorFinal;
	if(*quantClientes == 0){
		printf("\nErro: Não há clientes cadastrados.\n");
		return;
	}
	
	do{
		printf("RELATORIO DE COMPRAS\n");
		printf("1 - Total de compras inferior a um valor\n");
		printf("2 - Total de compras superior a um valor\n");
		printf("3 - Total de compras igual a um valor\n");
		printf("4 - Total de compras em uma faixa\n");
		printf("0 - Sair\n\n");
		printf("Digite a opcao desejada: ");
		scanf(" %d", &opcao);
		
		switch(opcao){
			case 1: {			
				printf("Qual o valor? ");
				scanf("%f", &valor);
				if(valor < 0){
					do{
						printf("Erro: valor negativo. Digite novamente: ");
						scanf("%d", &opcao);
					} while(opcao < 0);
				}
				
				printf("\nRELATORIO DE COMPRAS\n\n");
				for(i = 0; i < *quantClientes; i++){
					if(clientes[i].totCompras < valor){
						printf("Nome: %s\n", clientes[i].nome);
						printf("CPF: %s\n", clientes[i].CPF);
						printf("Total em compras: R$ %.2f\n", clientes[i].totCompras);
						printf("------------------------------------------------------------\n");
					}
				}
			}
			break;
			
			case 2: {
				printf("Qual o valor? ");
				scanf("%f", &valor);
				if(valor < 0){
					do{
						printf("Erro: valor negativo. Digite novamente: ");
						scanf("%d", &opcao);
					} while(opcao < 0);
				}
				
				printf("\nRELATORIO DE COMPRAS\n\n");
				for(i = 0; i < *quantClientes; i++){
					if(clientes[i].totCompras > valor){
						printf("Nome: %s\n", clientes[i].nome);
						printf("CPF: %s\n", clientes[i].CPF);
						printf("Total em compras: R$ %.2f\n", clientes[i].totCompras);
						printf("------------------------------------------------------------\n");
					}
				}
				break;
			}
			
			case 3: {
				printf("Qual o valor? ");
				scanf("%f", &valor);
				if(valor < 0){
					do{
						printf("Erro: valor negativo. Digite novamente: ");
						scanf("%d", &opcao);
					} while(opcao < 0);
				}
				
				printf("\nRELATORIO DE COMPRAS\n\n");
				for(i = 0; i < *quantClientes; i++){
					if(clientes[i].totCompras == valor){
						printf("Nome: %s\n", clientes[i].nome);
						printf("CPF: %s\n", clientes[i].CPF);
						printf("Total em compras: R$ %.2f\n", clientes[i].totCompras);
						printf("------------------------------------------------------------\n");
					}
				}
				break;
			}
			
			case 4: {
				printf("Qual o inicial? ");
				scanf("%f", &valorInicial);
				if(valor < 0){
					do{
						printf("Erro: valor negativo. Digite novamente: ");
						scanf("%d", &opcao);
					} while(opcao < 0);
				}
				
				printf("Qual o valor final? ");
				scanf("%f", &valorFinal);
				if(valor < 0){
					do{
						printf("Erro: valor negativo. Digite novamente: ");
						scanf("%d", &opcao);
					} while(opcao < 0);
				}
				
				if(valorFinal < valorInicial){
					aux = valorFinal;
					valorFinal = valorInicial;
					valorInicial = aux;
				}
				printf("\nRELATORIO DE COMPRAS\n\n");
				for(i = 0; i < *quantClientes; i++){
					if(clientes[i].totCompras >= valorInicial && clientes[i].totCompras <= valorFinal){
						printf("Nome: %s\n", clientes[i].nome);
						printf("CPF: %s\n", clientes[i].CPF);
						printf("Total em compras: R$ %.2f\n", clientes[i].totCompras);
						printf("------------------------------------------------------------\n");
					}
				}
				break;
			}
			
			case 0: return;
			
			default: printf("Opcao invalida!\n");
		}
	} while(opcao != 0);	
}
