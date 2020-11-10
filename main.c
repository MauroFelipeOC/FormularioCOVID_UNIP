#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "dados.h"

#define NUM_TENTATITVAS_LOGIN 3

REGISTRO cadastro()
{
    REGISTRO reg;
    
    int i;
    
    printf("Insira nome: ");
    fflush(stdin);
    fgets(reg.nome, 255, stdin);

    for (i = 0; reg.nome[i] != '\0'; i++)
    {
        if (reg.nome[i] >= 'a' && reg.nome[i] <= 'z')
        {
            reg.nome[i] = reg.nome[i] - 32;
        }
        if(reg.nome[i] == '\n') reg.nome[i] = '\0';
        if(reg.nome[i+1] == '\0') reg.nome[i] = NULL;
    }    

    printf("\nInsira cpf: ");
    fflush(stdin);
    scanf("%lld", &reg.cpf);
        
    printf("\nInsira telefone: ");
    fflush(stdin);
    scanf("%d", &reg.telefone);

    printf("\nInsira endereco: ");
    fflush(stdin);
    scanf("%s", &reg.endereco);

    printf("\nInsira numero: ");
    fflush(stdin);
    scanf("%d", &reg.numero);

    printf("\nInsira bairro: ");
    fflush(stdin);
    scanf("%s", &reg.bairro);

    printf("\nInsira cidade: ");
    fflush(stdin);
    scanf("%s", &reg.cidade);

    printf("\nInsira estado: ");
    fflush(stdin);
    scanf("%s", &reg.estado);

    printf("\nInsira cep: ");
    fflush(stdin);
    scanf("%s", &reg.cep);

    printf("\nInsira o dia de nascimento: ");
    fflush(stdin);
    scanf("%d", &reg.diaN);

    printf("\nInsira o mes de nascimento: ");
    fflush(stdin);
    scanf("%d", &reg.mesN);

    printf("\nInsira o ano de nascimento: ");
    fflush(stdin);
    scanf("%d", &reg.anoN);

    printf("\nInsira email: ");
    fflush(stdin);
    scanf("%s", &reg.email);

    printf("\nInsira data diagnostico: ");
    fflush(stdin);
    scanf("%s", &reg.diagnostico);

    printf("\nAlguma comorbidade? \t [S / N]");
    fflush(stdin);
    scanf("%c", &reg.comorbidade);

    if (toupper(reg.comorbidade) == 'S')
    {

        printf("\nDigite as comorbidades: ");
        fflush(stdin);
        scanf("%s", &reg.doencas);
    } else strcpy(reg.doencas, "");

    struct tm *data;
    time_t segundos;
        
    time(&segundos);
    data = localtime(&segundos);

    if(((data->tm_mon+1) <= reg.mesN) && (data->tm_mday < reg.diaN)){
        reg.idade = (data->tm_year + 1900) - reg.anoN -1;        
    }else{
            reg.idade = (data->tm_year + 1900) - reg.anoN;            
        }
    
    printf("\nIdade: %d\n", reg.idade);

    if (reg.idade >= 65 || toupper(reg.comorbidade) == 'S')
    {
        registrarGrupoRisco(reg);
        printf("Grupo de RISCO!!!\n");
        system("pause");
    }
    else
    {
        printf("Fora do grupo de Risco!\n");
        system("pause");
    }

    return reg;
}

void registrarGrupoRisco(REGISTRO reg)
{
    FILE *Ponteiro;
    Ponteiro = fopen("grupo_de_risco.txt", "a");
    fprintf(Ponteiro, "Cep: %s | Idade: %d | Nome: %s\n ------------------------------------\n", reg.cep, reg.idade, reg.nome);
    fclose(Ponteiro);
}

bool autenticar(char *loginCad, char *senhaCad, int tentativas)
{
    setlocale(LC_ALL, "Portuguese");

    char login[15];
    char senha[7];
    char c;
    int cont = 0;
    int i;
    int a;
    int verifica_senha = 0;

    do
    {
        i = 0;
        fflush(stdin);
        system("cls");

        printf("Digite o LOGIN\a: ");
        fflush(stdin);
        scanf("%s", login);

        printf("Digite a SENHA: ");

        while ((c = getch()) != 13)
        {
            senha[i] = c;

            putchar('*');
            i++;
        }
        senha[i] = '\0';

        if (strcmp(login, loginCad) == 0 && strcmp(senha, senhaCad) == 0)
        {
            printf("\nDADOS CORRETOS\n");
            system("color 0a");
            verifica_senha = 1;
            Beep(1500, 500);
            return true;
        }
        else
        {
            printf("\n FALHA \n");
            system("color 0c");
            Beep(1200, 200);
        }

        cont++;
    } while (verifica_senha == 0 && cont < tentativas);

    if (verifica_senha == 0)
    {
        printf("Você excedeu o número de tentativas!");
        return false;
    }
}

bool arquivarGeral(REGISTRO reg){
    FILE *Ponteiro;
    Ponteiro = fopen("arquivo_pacientes.txt", "a");
    fprintf(Ponteiro, "{\"nome\": \"%s\", \"cpf\": \"%011lld\", \"telefone\": \"%d\", \"endereco\": \"%s\", \"numero\": \"%d\", \"bairro\": \"%s\", \"cidade\": \"%s\", \"estado\": \"%s\", \"cep\": \"%d\", \"diaN\": \"%d\", \"mesN\": \"%d\", \"anoN\": \"%d\", \"email\":\"%s\", \"diagnostico\": \"%s\", \"comorbidade\": \"%c\", \"idade\": \"%d\", \"doencas\": \"%s\"},\n",  
        reg.nome,
        reg.cpf,
        reg.telefone,
        reg.endereco,
        reg.numero,
        reg.bairro,
        reg.cidade,
        reg.estado,
        reg.cep,
        reg.diaN,
        reg.mesN,
        reg.anoN,
        reg.email,
        reg.diagnostico,
        reg.comorbidade,
        reg.idade,
        reg.doencas);
    fclose(Ponteiro);
}


cadastrarUser(char *login, char *senha)
{
    int c = 0;
    int i = 0;

    printf("Digite o LOGIN\a: ");
    fflush(stdin);
    scanf("%s", login);

    printf("Digite a SENHA: ");

    while ((c = getch()) != 13)
    {

        senha[i] = c;

        putchar('*');
        i++;
    }
    senha[i] = '\0';
}

int menuPrincipal(void)
{
    int opcao = 1;
    char loginCad[15];
    char senhaCad[7];
    loginCad[0] = 0;

    LISTA pacientes;
    inicializarLista(&pacientes);

    if (!loginCad[0])
    { //Se ainda não houver login cadastrado
        printf("Cadastro de primeiro login\n");
        cadastrarUser(loginCad, senhaCad);
        system("cls"); //Limpa a tela
    }

    do
    {
        printf("\nInsira\n [1] Novo cadastro de paciente\n [2] Alterar credencial de login\n [3] Sair\n [4] Exibir cadastros de pacientes\n [0] Fechar: ");
        fflush(stdin);
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
        {
            REGISTRO reg = cadastro();
            arquivarGeral(reg);
            inserirElemento(&pacientes, reg);
            system("cls");
            break;
        }
        case 2:
        {
            cadastrarUser(loginCad, senhaCad);
            system("cls");
            break;
        }
        case 3:
        {
            if (!autenticar(loginCad, senhaCad, NUM_TENTATITVAS_LOGIN))
            {
                opcao = 0;
                break;
            }
            system("cls");
            break;
        }
        case 4:
        {
            exibirLista(&pacientes);
            system("pause");
            system("cls");
            break;
        }
        case 0:
            break;
        default:
        {
            system("cls");
            printf("Opcao invalida");
        }
        }
    } while (opcao);
}

int main(void)
{
    menuPrincipal();    
}