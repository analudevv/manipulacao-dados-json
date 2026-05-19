#include <stdio.h>
#include <string.h>
#include <windows.h>

void criarEstrutura(){

    CreateDirectory("sistema", NULL);
    CreateDirectory("sistema\\backup", NULL);
    CreateDirectory("sistema\\config", NULL);
    CreateDirectory("sistema\\alunos", NULL);

    printf("\nEstrutura de pastas criada ou ja existente.\n");
}

void gerarConfig(){

    FILE *arquivo;

    arquivo = fopen("sistema\\config\\config.json", "w");

    if(arquivo == NULL){
        printf("Erro ao criar config.json.\n");
        return;
    }

    fprintf(arquivo, "{\n");
    fprintf(arquivo, "   \"sistema\":\"Sistema de Gerenciamento de Alunos\",\n");
    fprintf(arquivo, "   \"versao\":\"1.1\",\n");
    fprintf(arquivo, "   \"dev\":\"Ana Luiza\",\n");
    fprintf(arquivo, "   \"backup\":\"sistema\\\\backup\"\n");
    fprintf(arquivo, "}\n");

    fclose(arquivo);

    printf("Arquivo de configuracao criado com sucesso.\n");
}

void mostrarConfig(){

    FILE *arquivo;
    char linha[150];

    arquivo = fopen("sistema\\config\\config.json", "r");

    if(arquivo == NULL){
        printf("Arquivo config.json nao encontrado.\n");
        return;
    }

    while(fgets(linha, 150, arquivo) != NULL){
        printf("%s", linha);
    }

    fclose(arquivo);
}

void cadastrarAlunos(){

    FILE *arquivo;

    char nomeCompleto[100];
    char curso[50];
    char linha[200];
    char buscaMatricula[50];

    int semestre;
    int matricula;
    int existe;

    getchar();

    while(1){

        existe = 0;

        printf("Nome completo: ");
        fgets(nomeCompleto, 100, stdin);
        nomeCompleto[strcspn(nomeCompleto, "\n")] = 0;

        printf("Curso: ");
        fgets(curso, 50, stdin);
        curso[strcspn(curso, "\n")] = 0;

        printf("Semestre: ");
        scanf("%d", &semestre);

        printf("Matricula: ");
        scanf("%d", &matricula);

        arquivo = fopen("sistema\\alunos\\alunos.json", "r");

        if(arquivo != NULL){

            sprintf(buscaMatricula, "\"matricula\": %d", matricula);

            while(fgets(linha, 200, arquivo) != NULL){

                if(strstr(linha, buscaMatricula) != NULL){

                    existe = 1;

                    printf("Matricula ja cadastrada. Tente novamente.\n");
                }
            }

            fclose(arquivo);
        }

        if(existe == 0){
            break;
        }

        getchar();
    }

    arquivo = fopen("sistema\\alunos\\alunos.json", "a");

    if(arquivo == NULL){
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    fprintf(arquivo,
    "{\n"
    "   \"matricula\": %d,\n"
    "   \"nome-completo\": \"%s\",\n"
    "   \"curso\": \"%s\",\n"
    "   \"semestre\": %d\n"
    "}\n\n",
    matricula, nomeCompleto, curso, semestre);

    fclose(arquivo);

    printf("Aluno cadastrado com sucesso.\n");
}

void mostrarAlunos(){

    FILE *arquivo;
    char linha[150];

    arquivo = fopen("sistema\\alunos\\alunos.json", "r");

    if(arquivo == NULL){
        printf("Arquivo alunos.json nao encontrado.\n");
        return;
    }

    while(fgets(linha, 150, arquivo) != NULL){
        printf("%s", linha);
    }

    fclose(arquivo);
}

void verificarAluno(){

    FILE *arquivo;

    char linha[200];
    char buscaMatricula[50];

    int matricula;
    int encontrado = 0;

    printf("Digite a matricula do aluno: ");
    scanf("%d", &matricula);

    sprintf(buscaMatricula, "\"matricula\": %d", matricula);

    arquivo = fopen("sistema\\alunos\\alunos.json", "r");

    if(arquivo == NULL){
        printf("Arquivo nao encontrado.\n");
        return;
    }

    while(fgets(linha, 200, arquivo) != NULL){

        if(strstr(linha, buscaMatricula) != NULL){

            encontrado = 1;

            printf("\n=== ALUNO ENCONTRADO ===\n\n");

            printf("%s", linha);

            for(int i = 0; i < 3; i++){

                fgets(linha, 200, arquivo);

                printf("%s", linha);
            }
        }
    }

    fclose(arquivo);

    if(encontrado == 0){
        printf("Aluno nao encontrado.\n");
    }
}

void backupAlunos(){

    int resultado;

    resultado = CopyFile(
        "sistema\\alunos\\alunos.json",
        "sistema\\backup\\alunos_backup.json",
        FALSE
    );

    if(resultado != 0){
        printf("Backup criado com sucesso.\n");
    }else{
        printf("Erro ao criar backup.\n");
    }
}

int main(){

    int option;

    do{

        printf("\n===Sistema de Cadastro de Alunos em C e JSON===\n");
        printf("1 - Criar estrutura de pastas\n");
        printf("2 - Gerar arquivo de configuracao\n");
        printf("3 - Mostrar arquivo de configuracao\n");
        printf("4 - Cadastrar alunos\n");
        printf("5 - Mostrar alunos cadastrados\n");
        printf("6 - Verificar aluno\n");
        printf("7 - Fazer backup do arquivo de alunos\n");
        printf("0 - Sair\n");
        printf("Opcao: ");

        scanf("%d", &option);

        switch(option){

            case 1:
                criarEstrutura();
                break;

            case 2:
                gerarConfig();
                break;

            case 3:
                mostrarConfig();
                break;

            case 4:
                cadastrarAlunos();
                break;

            case 5:
                mostrarAlunos();
                break;

            case 6:
                verificarAluno();
                break;

            case 7:
                backupAlunos();
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    }while(option != 0);

    return 0;
}
