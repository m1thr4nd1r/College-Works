// Trabalho - Gerenciamento de um Sistema Bancário
// MATA57 - Laboratorio de Programação - UFBA 2011.1
// Heitor Farias Melo
// Victor Maciel Guimarães dos Santos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tam_nome 30 // Tamanho Maximo do Nome
#define tam_senha 10 // Tamanho Maximo da Senha


struct Pessoa{	//struct contendo dados comuns a todos os tipos de usuario do sistema
				char senha[tam_senha];
				char nome[tam_nome];
				unsigned int CPF;
				unsigned int RG;
			  };
			  
struct GerenteContas{	// struct contendo dados comuns aos Gerentes de Contas
					  struct Pessoa P;
					  struct GerenteContas *prox;
					  unsigned int matricula;
				    };
				    
struct GerenteContas *sentinela_GC;	// variavel do tipo GerenteContas vazia porem valida

struct Lista_GerenteContas{	// Lista dinamica encandeada dos Gerentes de Contas (nao inclui o Gerente Geral)
							struct GerenteContas* inicio;
							int qnt;
						  };

struct Correntista{	// struct contendo os dados comuns aos Correntistas
					struct Pessoa P;
					struct Correntista *prox;
					float renda;
					int agencia;
					int conta;
					int limite;
					float saldo;
					int gerente;
				  };

struct Correntista *sentinela_C;  // variavel do tipo Correntista vazia porem valida
				  
struct Lista_Correntista {	// Lista dinamica encandeada dos Correntistas
							struct Correntista *inicio;
							int qnt;
						 };
				  
int Login(struct GerenteContas GG,struct Lista_GerenteContas LGC,struct Lista_Correntista LC,struct Correntista **P_C,struct GerenteContas **P_GC,int * m) // Funçao que controla o login
// GG = Gerente Geral, LGC = Lista dos Gerente de Contas, LC = Lista dos Correntistas
// P_C = Ponteiro para o correntista que estiver fazendo o Login, P_GC = Ponteiro para o Gerente de Contas que estiver fazendo Login (Para uso posterior)
// m = Endereço da matricula de quem fez Login.
// Esta funçao cuida do Login do Usuario, e ira redireciona-lo para a Tela apropriada, ou dara erro caso o usuario nao exista
{	
	int matricula,j,i,k;
	char senha[tam_senha];
	struct GerenteContas *Aux_GC=LGC.inicio;
	struct Correntista* Aux_C=LC.inicio;
		
	printf("Digite sua matricula (ou CPF)(-1 para sair): ");
	scanf("%d",&matricula);
	if (matricula == -1) // Se matricula = -1 entao sai do programa.
		return -1;
	printf("Digite sua senha: ");
	scanf("%s",senha);
	
	j = strlen(senha);
	
	// O codigo a seguir limita a senha no tamanho definido no tam_senha
	
	if (j < tam_senha)
		senha[j] = '\0'; 
	else
		senha[tam_senha] = '\0';
		
	///////////////////////////////////////////////////////////////////////
	
	k = strcmp(senha,GG.P.senha); // Ira comparar as duas strings e retornar 0 se forem iguais.
	
	if ((matricula == GG.matricula) && (!k)) // Gerente Geral fez login
	{
		*m = matricula; // m recebe a matricula de quem logou
		return 1;
	}
	else
	{
		for(i=0;i<LGC.qnt;i++) // Varre a Lista de Gerentes Gerais
		{	
			k = strcmp(senha,Aux_GC->P.senha); // Ira comparar as duas strings e retornar 0 se forem iguais.
			if ((matricula == Aux_GC->matricula) && (!k)) // Gerente de Contas fez Login
			{
				*m = matricula; // m recebe a matricula de quem logou
				*P_GC = Aux_GC; //P_GC recebe o endereço do Gerente de Contas que logou
				return 2;
			}
			else
				Aux_GC = Aux_GC->prox; // Vai pro proximo elemento da Lista
		}
		
		for(i=0;i<LC.qnt;i++) // Varre a Lista de Correntistas
		{
			k = strcmp(senha,Aux_C->P.senha);	// Ira comparar as duas strings e retornar 0 se forem iguais.
			if ((matricula == Aux_C->P.CPF) && (!k)) // Gerente de Contas fez Login
			{
				*m = matricula; // m recebe a matricula de quem logou
				*P_C = Aux_C; //P_GC recebe o endereço do Gerente de Contas que logou
				return 3;
			}
			else
				Aux_C = Aux_C->prox; // Vai pro proximo elemento da Lista
		}
		return 0;	// Retorna zero se ao varrer todas as Listas o programa não encontrar usuario, ou seja, o usuario nâo existe
	}
}

int CadastrarGerenteConta(struct Lista_GerenteContas * LGC) // Funçao que cadastra Gerente de Conta
// LGC = Lista dos Gerentes de Conta
{
	struct GerenteContas *Aux=LGC->inicio,*Novo;
	
	int j;
	FILE *gerente; // Ponteiro para arquivo
	
	
	Novo = (struct GerenteContas *) malloc(sizeof(struct GerenteContas)); // Aloca espaço pra uma variavel do tipo GerenteContas
	
	if (Novo == NULL)
		{	
			printf("Nao ha espaco na memoria");
			return 0; // Nao foi possivel adicionar um Gerente de Contas
		}
	
	//Codigo para cadastro "automatico" do Gerente de Conta (para teste)
	
	Novo->matricula = 10 + LGC->qnt;
	Novo->P.CPF = 11111;
	Novo->P.RG = 1111;
	Novo->prox = NULL;
	
	strcpy(Novo->P.senha,"senha");
	
	printf("Digite o nome do Gerente de Contas(30 chars max): ");
	scanf("\n");
	gets(Novo->P.nome);
	
	///////////////////////////////////////////////////////////////////
	
	// Codigo para preenchimento manual do Cadastro
	/*
	 	
	printf("Digite o nome do Gerente de Contas(30 chars max): ");
	scanf("\n");	// Para limpar o buffer
	gets(Novo->P.nome);
		
	// O codigo a seguir limita o nome no tamanho definido no tam_nome
	
	j = strlen(Novo->P.nome);
	if (j < tam_nome)
		Novo->P.nome[j] = '\0';
	else
		Novo->P.nome[tam_nome] = '\0';
	
	///////////////////////////////////////////////////////////////////
	
	printf("Digite a matricula do Gerente de Contas: ");
	scanf("%d",&Novo->matricula);
	printf("Digite o CPF do Gerente de Contas(5 numeros): ");
	scanf("%d",&Novo->P.CPF);
	printf("Digite o RG do Gerente de Contas(4 numeros): ");
	scanf("%d",&Novo->P.RG);
	printf("Digite a senha do Gerente de Contas: ");
	scanf("\n");	// Para limpar o buffer
	gets(Novo->P.senha);
	
	// O codigo a seguir limita a senha no tamanho definido no tam_senha
		
	j = strlen(Novo->P.senha);
	if (j < tam_senha)
		Novo->P.senha[j] = '\0';
	else
		Novo->P.senha[tam_senha] = '\0';
	
	*/
	///////////////////////////////////////////////////////////////////
	
	// Codigo para alocação do novo elemento no inicio ou fim da Lista
	
	if (LGC->qnt == 0)
		LGC->inicio = Novo;
	else
	{
		while (Aux->prox != NULL)
			Aux = Aux->prox;
		
		Aux->prox = Novo;
	}
	
	////////////////////////////////////////////////////////////
	
	// Codigo para armazenar os gerentes de contas no arquivo
	
	gerente = fopen("gerentes_contas","ab");
	if (gerente != NULL)
		fwrite(Novo,sizeof(struct GerenteContas),1,gerente);
	fclose(gerente);
	
	//////////////////////////////////////////////////////////
			
	LGC->qnt++;
	
	return 1; // Cadastrou um Gerente de Contas
}


int CadastrarCorrentistas(struct Lista_Correntista *LC,int matricula) //Funçao para cadastrar correntistas
// LC = Lista dos correntistas, matricula = matricula de quem esta efetuando o cadastro
{
	char c[5]; // Variavel utilizada no preenchimento automatico do Cadastramento
	
	int j;
	
	struct Correntista *Aux=LC->inicio,*Novo;
	
	Novo = (struct Correntista *) malloc(sizeof(struct Correntista));
	
	if (Novo == NULL)
		{	
			printf("Nao ha espaco na memoria");
			return 0; // Nao foi possivel cadastrar o Correntista
		}
	
	//Codigo para cadastro "automatico" do Corentista (para teste)
	
	Novo->gerente = matricula;
	Novo->agencia = 1+1*(LC->qnt);
	Novo->conta = 1+1*(LC->qnt);
	Novo->limite = 1000 + 1*(LC->qnt);
	Novo->renda = 500 + 1*(LC->qnt);
	Novo->saldo = 10+1*(LC->qnt);
	Novo->P.CPF = 1+1*(LC->qnt);
	Novo->P.RG = 1+1*(LC->qnt);
	sprintf(c,"%d",LC->qnt);
	strcat(Novo->P.nome,c);
	strcpy(Novo->P.senha,"senha");
	Novo->prox = NULL;
	
	///////////////////////////////////////////////////////////////
	
	//Codigo para cadastro manual do Correntista
	/*
	
	printf("Digite o nome do Correntista(30 chars no max): "); //Adicionando Correntista
	scanf("\n");
	gets(Novo->P.nome);
	
	// O codigo a seguir limita o nome no tamanho definido no tam_nome
	
	j = strlen(Novo->P.nome);
	if (j < tam_nome)
		Novo->P.nome[j] = '\0';
	else
		Novo->P.nome[tam_nome] = '\0';
		
	
	////////////////////////////////////////////////////////////////////
		
	printf("Digite o CPF do Correntista(5 numeros): ");
	scanf("%d",&Novo->P.CPF);
	printf("Digite o RG do Correntista(4 numeros): ");
	scanf("%d",&Novo->P.RG);
	printf("Digite a senha do Correntista(10 chars no max): ");
	scanf("\n");
	gets(Novo->P.senha);
	
	// O codigo a seguir limita a senha no tamanho definido no tam_senha
	
	j = strlen(Novo->P.senha);
	if (j < tam_senha)
		Novo->P.senha[j] = '\0';
	else
		Novo->P.senha[tam_senha] = '\0';
	
	///////////////////////////////////////////////////////////////////
	
	printf("Digite a agencia do Correntista(5 numeros): ");
	scanf("%d",&Novo->agencia);
	printf("Digite a conta do Correntista(7 numeros): ");
	scanf("%d",&Novo->conta);
	printf("Digite o limite do Correntista: ");
	scanf("%d",&Novo->limite);
	printf("Digite a renda do Correntista: ");
	scanf("%f",&Novo->renda);
	
	while (Novo->renda <= 0)
	{
		printf("\nValor Invalido. Digite novamente: ");
		scanf("%f",&Novo->renda);
	} 
	
	printf("Digite o saldo do Correntista: ");
	scanf("%f",&Novo->saldo);
	*/
	
	/////////////////////////////////////////////////////////////
	
	// Codigo para alocação do novo elemento no inicio ou fim da Lista
	
	if (LC->qnt == 0)
		LC->inicio = Novo;
	else
	{
		while (Aux->prox != NULL)
			Aux = Aux->prox;
		
		Aux->prox = Novo;
	}
	
	LC->qnt++;
	
	///////////////////////////////////////////////////////////
	
	return 1; // Cadastrou Correntista
}

int Fazer_Saque(struct Correntista *C) // Funcao para realizar o saque
// C = Endereço do Correntista que fez Login
{
	float saque;
	printf("\nDigite o valor que quer sacar: ");
	scanf("%f",&saque);
	
	while (saque <= 0) // Verifica se o valor de saque eh valido
	{
		printf("\nValor invalido. Digite novamente: ");
		scanf("%f",&saque);
	}
	
	if (saque > (C->saldo + C->limite)) // Se saque for maior que o saldo + limite do usuario
	{
		printf("\nVoce nao tem saldo nem limite disponiveis\n");
		return 0; // Nao realiza saque
	}
	else if (saque > (C->saldo)) // Se saque for maior que o saldo
	{
		C->saldo -= saque; // Saldo fica negativo
		printf("\nSaque tirado do limite\n");
	}
	else // Se saque for menor que o saldo
	{
		C->saldo -= saque; // Saque é removido do saldo.
		printf("\nSaque tirado do saldo\n");
	}
	return 1; // Dinheiro sacado
}
	
void Fazer_Deposito(struct Correntista *C) // C = Endereço do Correntista que fez Login
{
	float deposito;
	printf("Digite quanto vc quer depositar: ");	
	scanf("%f",&deposito);
	
	while (deposito <= 0) // Verifica se o valor de deposito eh valido
	{
		printf("\nValor invalido. Digite novamente: ");
		scanf("%f",&deposito);
	}

	C->saldo += deposito; // Adiciona o deposito a conta do Correntista
	
	if (C->saldo <= 0) // Se saldo for negativo, o correntista ainda esta usando o limite
		printf("\nAinda sem saldo disponivel\n");
	else
		printf("\nSaldo disponivel\n");
}

void Visualizar_Dados(struct Correntista C,int authorization,int mode) // Funçao para visualizaçao dos dados de um correntista
// C = Endereço do Correntista que fez Login, authorization = autorizaçao do usuario que visualiza os dados, 0 para correntistas, 1 para gerentes 
{
	FILE *dados;
	if (authorization) // Se o usuario tiver autorizaçao entao imprime mais informaçoes
	{
		printf("\nNome = ");
		puts(C.P.nome);
		printf("\n");
		printf("\nCPF = %d\n",C.P.CPF);
		printf("\nRG = %d\n",C.P.RG);
		printf("\nSenha = ");
		puts(C.P.senha);
		printf("\n");
		printf("\nAgencia = %d\n",C.agencia);
		printf("\nConta = %d\n",C.conta);
		printf("\nRenda = %0.2f\n",C.renda);
		printf("\nGerente: %d\n",C.gerente);
	}	
	
	// Imprime o que todos os usuarios tem direito a visualizar
	
	// Se quiser ver na tela, imprime direto
	
	if (mode == 1)
	{
		printf("\nSaldo atual = %0.2f \n",C.saldo);
		if (C.saldo >= 0)
			printf("\nLimite = %d \n",C.limite);
		else
			printf("\nLimite = %0.2f \n",C.limite + C.saldo);
	}
	
	// Se quiser ver na tela, imprime no arquivo
	
	else if (mode == 2)
	{
		dados = fopen("dados_correntistas.txt","a"); // Abre o arquivo dados_correntistas.txt
		if (dados != NULL) // Verifica se o arquivo foi aberto com sucesso
		{
			fprintf(dados,"Limite: %d, Saldo: %0.2f, CPF: %d\n",C.limite,C.saldo,C.P.CPF); // Imprime os dados no arquivo
			/// Guarda o CPF no arquivo para possivel consulta no futuro.
			fclose(dados); // Fecha o arquivo dados_correntistas.txt
		}
	}
}

struct Correntista* Buscar_Correntista(struct Lista_Correntista LC,int conta,int matricula,int autorizacao) // Funcao para buscar o Correntista na Lista de Correntistas
// LC = Lista dos Correntistas, conta = conta a ser procurada, matricula = matricula de quem esta procurando o correntista, autorizacao = Autorizacao do usuario, se for Gerente Geral é 1, se Gerente de Contas é 0
{
	int i;
	struct Correntista *Aux=LC.inicio;
	for (i=0;i<LC.qnt;i++) // Procura o correntista (com a conta passada por parametro) na Lista de Correntistas
	{
		if (Aux->conta == conta) // Se a conta é igual a conta passada por matricula e...
		{
			if ((Aux->gerente == matricula) || (autorizacao == 1)) // Se o gerente da conta for igual a matricula do que esta fazendo a procura ou o Gerente for o gerente geral
			{
				printf("\nCorrentista Achado\n");
				return Aux; // Retorna o endereço do correntista (para uso posterior)
			}
			else
			{	
				printf("\nVc nao eh gerente deste correntista\n"); // O correntista existe mas o gerente nao é o mesmo que o esta procurando
				return NULL; // Retorna Nulo se o gerente nao for o gerente do correntista
			}
		}
		Aux = Aux->prox; // Varrendo a Lista
	}
	printf("\nCorrentista nao encontrado\n"); 
	return NULL;	// Retorna Nulo para correntista nao encontrado
}

void Display_GerenteGeral(struct Lista_GerenteContas *LGC, struct Lista_Correntista *LC,int matricula) // Organiza a tela do Gerente Geral
// LGC = Lista de Gerente de Contas, LC = Lista de Correntistas, matricula = matricula do Gerente que fez Login
{
	int choice,vis;
	do
	{
		int conta;
		struct Correntista * Aux;
		printf("\n1-Cadastrar Gerente de Contas");
		printf("\n2-Cadastrar Correntista");
		printf("\n3-Visualizar dados: ");
		printf("\nDigite a operaçao que deseja(0 para sair): ");
		scanf("%d",&choice);
	
		switch (choice)
		{
			case 0:
					choice = 0; // Faz logoff
					printf("\e[H\e[2J"); // Funçao de limpar tela
					break;
			case 1:
					if(CadastrarGerenteConta(LGC)) // Se conseguir cadastrar o gerente de contas retorna 1
						printf("\nGerente Cadastrado\n");
					break;
			case 2:
					if (CadastrarCorrentistas(LC,matricula)) // Se conseguir cadastrar o correntista retorna 1
						printf("\nCorrentista Cadastrado\n");
					break;
			case 3:
					printf("Digite a conta do correntista: ");
					scanf("%d",&conta);
					printf("\n1- Visualizar na tela");
					printf("\n2- Visualizar no arquivo");
					printf("\nEscolha sua opcao: ");
					scanf("%d",&vis);
					Aux = Buscar_Correntista(*LC,conta,matricula,1); // Busca o correntista dentro da lista com a conta informada
					if (Aux != NULL)
						Visualizar_Dados(*Aux,1,vis); //Aux é o endereço do correntista que eu quero acessar, 1 é a autorizaçao do usuario que faz a visualização
					break;
		}
	}while (choice != 0);
}

void Display_GerenteConta(struct Lista_Correntista *LC,int matricula) // Funçao que organiza a tela do gerente de contas
// LC = Lista dos Correntistas, matricula = matricula do gerente que esta logado
{
	int choice,vis;
	do
	{
		int conta;
		struct Correntista * Aux;
		
		printf("\n1-Cadastrar Correntista");
		printf("\n2-Visualizar dados: ");
		printf("\nDigite a operaçao que deseja(0 para sair): ");
		scanf("%d",&choice);
	
		switch (choice)
		{			
			case 0:
					choice = 0; // Faz logoff
					printf("\e[H\e[2J"); // Funçao de limpar tela
					break;
			case 1:
					if (CadastrarCorrentistas(LC,matricula)) // Se cadastrar o correntista retorna 1
						printf("\nCorrentista Cadastrado\n");
					break;
			case 2:
					printf("Digite a conta do correntista: ");
					scanf("%d",&conta);
					printf("\n1- Visualizar na tela");
					printf("\n2- Visualizar no arquivo");
					printf("\nEscolha sua opcao: ");
					scanf("%d",&vis);
					Aux = Buscar_Correntista(*LC,conta,matricula,0); // Busca o correntista dentro da lista com a conta informada
					if (Aux != NULL)
						Visualizar_Dados(*Aux,1,vis); //Aux é o endereço do correntista que eu quero acessar, 1 é a autorizaçao do usuario que faz a visualização
					break;
		}
	}while (choice != 0);
}

void Display_Correntista(struct Correntista *C) // Funçao que organiza a tela do Correntista
// C = O endereço do Correntista que fez o Login.
{
	int choice,vis;
	do
	{
		printf("\n1-Fazer saque");
		printf("\n2-Fazer deposito");
		printf("\n3-Visualizar dados (limite e saldo): ");
		printf("\nDigite a operaçao que deseja(0 para sair): ");
		scanf("%d",&choice);
	
		switch (choice)
		{
			case 0:
					choice = 0; // Faz logoff
					printf("\e[H\e[2J"); // Funçao de limpar tela
					break;
			case 1:
					Fazer_Saque(C); // Realiza saque
					break;
			case 2:
					Fazer_Deposito(C); // Realiza deposito
					break;
			case 3:
					printf("\n1- Visualizar na tela");
					printf("\n2- Visualizar no arquivo");
					printf("\nEscolha sua opcao: ");
					scanf("%d",&vis);
					Visualizar_Dados(*C,0,vis); // Visualiza Dados, onde C é o conteudo do Correntista que fez Login, e 0 é a autorizaçao que o correntista tem para visualizar dados
					break;
		}
	}while (choice != 0);
}

void init_ListaC(struct Lista_Correntista * LC) // Funçao para inicializar a Lista de Correntistas
// LC = Lista dos Correntistas
{
	LC->inicio = sentinela_C; // O inicio aponta para uma variavel do mesmo tipo porem vazia
	LC->qnt = 0; // Quantidade vai para zero para inicializar a lista
}

void init_ListaGC(struct Lista_GerenteContas * LGC) // Funçao para inicializar a Lista de Gerente de Contas
// LGC = Lista dos Gerentes de Contas
{
	LGC->inicio = sentinela_GC; // O inicio aponta para uma variavel do mesmo tipo porem vazia
	LGC->qnt = 0;  // Quantidade vai para zero para inicializar a lista
}

int gerar_relatorio(struct Lista_Correntista LC)
{
	FILE *relatorio;
	struct Correntista *aux = LC.inicio;
	
	printf("\nRelatorio sendo gerado...");
	
	relatorio = fopen("relatorio.txt","w"); // Abre o arquivo relatorio.txt
	if (relatorio == NULL) // Se nao conseguir retorna 0
		return 0;
	else
	{
		do
		{
			if (aux->saldo == -(aux->limite)) // Se o saldo em modulo do correntista for igual ao limite
				fprintf(relatorio,"Nome: %s, Agencia: %d, Conta: %d, Limite: %d, Saldo: %0.2f\n",aux->P.nome,aux->agencia,aux->conta,aux->limite,aux->saldo);
				// Guarda os dados do correntista no arquivo "relatorio.txt"
			aux = aux->prox; // Percorre a lista
		}while (aux != NULL); 
	
		fclose(relatorio); // Fecha o arquivo relatorio.txt
	}
	
	return 1;
}

int carregar_gerente_geral(struct GerenteContas *GG)
//	GG = A variavel que armazena os dados do Gerente Geral
{
	FILE* carregar;
	
	carregar = fopen("gerente_geral","rb"); // Abre o arquivo "gerente_geral"
	
	if (carregar != NULL) // Se conseguir abrir o arquivo
	{
		fread(GG,sizeof(struct GerenteContas),1,carregar); // Le os dados do gerente geral
		return 1; // Entao retorna 1 = Conseguiu ler
	}
	else
		return 0; // Senao, retorna 0 = Nao conseguiu ler
}

void carregar_gerente(struct Lista_GerenteContas *LGC)
//	LGC = Lista dos Gerentes de Conta
{
	FILE* carregar;
	struct GerenteContas *Novo, *Aux;
	
	Novo = (struct GerenteContas*) malloc (sizeof(struct GerenteContas)); // Aloca o espaco de um no novo
	
	carregar = fopen("gerentes_contas","rb"); // Tenta abrir o arquivo gerente_contas
	
	if (carregar != NULL) // Se conseguir abrir o arquivo gerente_contas
	{
		while (fread(Novo,sizeof(struct GerenteContas),1,carregar)) // Enquanto conseguir ler os gerentes de conta do arquivo
		{
			Aux = LGC->inicio; // Variavel para varrer a lista de gerentes de conta
			
			Novo->prox = NULL; // Seta o endereço do prox de Novo para NULL pois nao se pode confiar nos endereços que estavam no arquivo
			
			if (LGC->qnt == 0) // Se a quantidade de elementos na lista for 0
				LGC->inicio = Novo; // Aloca o novo nó no inicio
			else // Senao
			{
				while (Aux->prox != NULL) // Procura o ultimo elemento da lista
					Aux = Aux->prox;
				Aux->prox = Novo; // Aloca o novo no apos o ultimo elemento da lista
			}
		
			LGC->qnt++; // Incrementa o contador de elementos da lista
			
			Novo = (struct GerenteContas*) malloc (sizeof(struct GerenteContas)); 
			// Realoca o no Novo para que nao ocorra de mais de um elemento ter os mesmos valores
		}
		
		fclose(carregar); // Fecha o arquivo cujo ponteiro eh carregar

	}
}

void carregar_correntista(struct Lista_Correntista *LC)
{
	FILE* carregar;
	struct Correntista *Novo, *Aux;
	
	Novo = (struct Correntista*) malloc (sizeof(struct Correntista)); // Aloca o espaco de um no novo
	
	carregar = fopen("correntistas","rb"); // Tenta abrir o arquivo correntista
	
	if (carregar != NULL) // Se conseguir abrir o arquivo
	{
		while((fread(Novo,sizeof(struct Correntista),1,carregar) == 1)) // Enquanto conseguir ler os correntistas do arquivo
		{
			Aux = LC->inicio; // Variavel para percorrer a lista de correntistas
								
			Novo->prox = NULL; // Seta o prox do no Novo para NULL pois o endereço que esta no arquivo nao é atual
			
			if (LC->qnt == 0) // Se nao houver elementos na lista
				LC->inicio = Novo; // Adiciona o elemento no inicio
			else // Senao
			{
				while (Aux->prox != NULL) // Procura o ultimo elemento da lista
					Aux = Aux->prox;
				Aux->prox = Novo; // Adiciona o novo no como proximo do ultimo no da lista
			}
		
			LC->qnt++; // Incrementa a quantidade de nos na lista
			
			Novo = (struct Correntista*) malloc (sizeof(struct Correntista));
			// Realoca o no Novo para que nao ocorra de mais de um elemento ter os mesmos valores
		}
		
		fclose(carregar); // Fecha o arquivo "correntistas"
	}
}

int gerar_arquivo(struct Lista_Correntista LC)
// LC = Lista dos Correntistas
{
	struct Correntista	*Aux = LC.inicio; // Variavel para varrer a lista
	FILE * arquivo;
	
	printf("\nArquivo sendo gerado...");
	
	arquivo = fopen("correntistas","wb"); // Abre o arquivo "correntistas"
	if (arquivo != NULL) // Se conseguir abrir o arquivo
	{	
		while (Aux != NULL) // Enquanto a variavel nao for Nula
		{
			fwrite(Aux,sizeof(struct Correntista),1,arquivo); 
			// Imprime o elemento correspondente da lista no arquivo, apagando o que existia
			Aux = Aux->prox; // Varre a lista
		}
		
		fclose(arquivo); // Fecha o arquivo
	}
	else
		return 0; // Se nao conseguir abrir retorna 0 = False
	
	return 1; // Se conseguir, retorna 1 = True
}

int main()
{
	sentinela_C = (struct Correntista*) malloc(sizeof(struct Correntista)); // Aloca espaço para a sentinela dos correntistas
	sentinela_GC = (struct GerenteContas*) malloc(sizeof(struct GerenteContas)); // Aloca espaço para a sentinela dos gerentes de conta
	
	struct GerenteContas GG; // Gerente Geral;
	struct GerenteContas *Pos_GC=sentinela_GC;
	struct Correntista *Pos_C=sentinela_C;
	struct Lista_Correntista LC;
	struct Lista_GerenteContas LGC;
	int matricula=0,X=0,j;
	FILE *gerente_geral; // Ponteiro para arquivo
	
	init_ListaGC(&LGC); // Chamada da funçao para incializar a lista de gerentes de conta
	init_ListaC(&LC); // Chamada da funçao para inicializar a lista de correntistas
	
	// Funcao para carregar as listas dos arquivos
	
	carregar_gerente(&LGC);	// Carrega os Gerentes de Conta na lista correspondente
	
	carregar_correntista(&LC); // Carrega os Correntistas na lista correspondente
		
	if(!carregar_gerente_geral(&GG)) 
	// Se nao conseguir carregar o gerente geral (o arquivo estara vazio)
	// Se conseguir, o gerente geral ja estara com seus dados na variavel GG
	{
		
		// Codigo para cadastro "automatico" do gerente geral
		
		GG.matricula = 0;
		strcpy(GG.P.nome,"victor");
		GG.P.CPF = 00000;
		GG.P.RG = 0000;
		strcpy(GG.P.senha,"senha");
	
		/////////////////////////////////////////////////////
	
		// Codigo para cadastro manual do gerente geral
	
		/*
	
		printf("Digite a matricula do Gerente Geral(5 numeros, deve começar com zero): ");
		scanf("%d",&GG.matricula);		
		printf("Digite o nome do Gerente Geral(30 chars max): ");
		scanf("\n"); // Limpa o buffer
		gets(GG.P.nome);
	
		// O codigo a seguir limita o nome no tamanho definido no tam_nome
	
		j = strlen(GG.P.nome);
		if (j < tam_nome)
			GG.P.nome[j] = '\0';
		else
			GG.P.nome[tam_nome] = '\0';
	
		///////////////////////////////////////////////////////////////////
	
		printf("Digite o CPF do Gerente Geral(5 numeros): ");
		scanf("%d",&GG.P.CPF);
		printf("Digite o RG do Gerente Geral(4 numeros): ");
		scanf("%d",&GG.P.RG);
		printf("Digite a senha do Gerente Geral: ");
		scanf("\n"); // Limpa o buffer
		gets(GG.P.senha);
	
		// O codigo a seguir limita a senha no tamanho definido no tam_senha
	
		j = strlen(GG.P.senha);
		if (j < tam_senha)
			GG.P.senha[j] = '\0';
		else
			GG.P.senha[tam_senha] = '\0';
	
		///////////////////////////////////////////////////////////////////
	
		printf("\e[H\e[2J"); // Funçao de limpar tela
	
		*/
		
		// Codigo para gravar os dados do Gerente Geral no arquivo
		
		gerente_geral = fopen("gerente_geral","wb"); // Tenta abrir o arquivo "gerente_geral"
		if (gerente_geral != NULL) // Se conseguir abrir
			fwrite(&GG,sizeof(struct GerenteContas),1,gerente_geral); // Salva os dados do gerente geral no arquivo
		fclose(gerente_geral); // Fecha o arquivo
		
		////////////////////////////////////////////////////////////
	
	} 

	do
	{
		X = Login(GG,LGC,LC,&Pos_C,&Pos_GC,&matricula); // Chama a funçao de login
		switch (X)
		{
			case -1: // Sai do programa
					printf("\nSaindo do Programa");
					break;
			case 0: // Nao achou o usuario
					printf("\nUsuario ou senha invalidos\n");
					break;
			case 1: // O usuario é o gerente de geral
					Display_GerenteGeral(&LGC,&LC,GG.matricula);
					break;
			case 2: // O usuario é gerente de contas
					Display_GerenteConta(&LC,matricula);
					break;
			case 3: // O usuario é correntista
					Display_Correntista(Pos_C);
					break;
		}
	}while (X != -1); // Enquanto nao encontrar -1

	if (gerar_relatorio(LC)) 
	// Gera o relatorio dos clientes com o limite gasto
	// Se conseguir gerar, imprime a frase abaixo
		printf("\nRelatorio Gerado");
	
	if (gerar_arquivo(LC)) 
	// Gera o arquivo com os correntistas cadastrados ate o momento
	// Se conseguir gerar, imprime a frase abaixo
		printf("\nArquivo Gerado");
		
	return 0; // Programa finalizado corretamente
}
