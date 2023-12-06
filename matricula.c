#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// menu de opcoes
void menu() {
  printf(" \n 1 - Cadastrar Aluno\n 2 - Remover Aluno\n 3 - Atualizar Dados De "
         "Um Aluno\n 4 - Listar Alunos Cadastrados Na Turma\n 5 - Listar "
         "Alunos Aprovados\n 6 - Listra Alunos Reprovados Por Media\n 7 - "
         "Listar alunos por turma\n 8 - "
         "Listar Alunos Reprovados Por Falta\n 9 -Ordenacao Dos Dados\n 0 - "
         "Para Sair\n");
}
void erro() { printf("\nNumero invalido!!\n"); }
typedef struct {
  int matricula;
  char nome[50];
  float notas[4];
  int turma;
  int faltas;
} aluno;

// "condicaonatricula" verifica se a matricula esta no  formato certo e se ja esta no sistema
int condicaomatricula(aluno *n, unsigned long int v) {
  int i;
  int valida = 0;

  if (n[v].matricula < 2021000 || n[v].matricula > 2021099) {
    return 1;
  }
  for (i = v; i >= 0; i--) {
    if (i != v) {
      if (n[v].matricula == n[i].matricula) {
        return 0;
      }
    }
  }
  return 2;
}
//"condicaonota" avalia se a nota esta entre 0 e 10
int condicaonota(float n) {
  if (n < 0 || n > 10) {
    return 0;
  }
  return 1;
}
// mensagem de matricula existente
void Matriculaexiste() { printf("Matricula Existente no Cadastro\n"); }
// mensagem do formato incorreto de matricula
void Formatomatricula() {
  printf("Formato da matricula invalido\nFormato correto:--20210XX--\n");
}
//"condicaoturma" verifica se a turma eh maior que 0
int condicaoturma(int n) {
  if (n <= 0) {
    return 0;
  }
  return 1;
}
//"condicaofalta" verifica a entrada de faltas se e maior ou igual 0 e se e
//menor ou igual 36
int condicaofalta(int n) {
  if (n < 0 || n > 36) {
    return 0;
  }
  return 1;
}

//"cadastrarmatricula" cadastrar matricula no vetor alunos
void cadastrarmatricula(aluno *estudante, unsigned long int h) {
  int vmatricula = 0;
  vmatricula = 0;
  while (vmatricula == 0 || vmatricula == 1) {
    printf("Digite a Matricula:\n");
    scanf("%d", &estudante[h].matricula);
    getchar();
    // utilizando a funcao "condicaomatricula" para verificar se ja existe
    // matricula no sistema se existir retorna 0 e se o formato é invalido
    // devolve 1 caso as duas condicoes nao forem satisfeitas retorna 2 e sai do
    // loop.
    vmatricula = condicaomatricula(estudante, h);

    if (vmatricula == 1) {
      Formatomatricula();
    }
    if (vmatricula == 0) {
      Matriculaexiste();
    }
  }
}
int condicaonome(aluno *estudante, unsigned long int h) {
  int i = 0;
  for(i=0;estudante[h].nome[i] != '\0';i++) {
   
    if (isalpha(estudante[h].nome[i])==0 &&  isspace(estudante[h].nome[i])==0) {
      return 0;
    }
   
  }
  return 1;
}
void cadastrarnome(aluno *estudante, unsigned long int h) {
  int vnome = 0;
  while (vnome == 0) {
    printf("Digite seu nome:\n");
    fgets(estudante[h].nome,50,stdin);
   
    estudante[h].nome[strcspn(estudante[h].nome, "\n")] = 0;
     
    //scanf("%s", estudante[h].nome);

    vnome = condicaonome(estudante, h);
    if (vnome == 0) {
      printf("nome invalido\n");
      break;
    }
  }
}
//"cadastranotas" cadastra o vetor notas
void cadastrarnotas(aluno *estudante, unsigned long int h) {
  int vnotas = 0, i;
  vnotas = 0;
  while (vnotas == 0) {
    printf("Digite as 4 notas do aluno abaixo:\n");
    for (i = 0; i < 4; i++) {
      printf("Nota %d:", i + 1);
      scanf("%f", &estudante[h].notas[i]);
      // verificando se a nota>=0 e nota<=10 se for false entra no loop ate
      // digitar certo as 4 notas
      vnotas = condicaonota(estudante[h].notas[i]);
      if (vnotas == 0) {
        printf("nota invalida\n");
        break;
      }
    }
  }
}
//"cadastrarfaltas" cadastra faltas no vetor faltas
void cadastrarfaltas(aluno *estudante, unsigned long int h) {
  int vfalta = 0;
  vfalta = 0;
  // loop ate que que digite um numero de faltas correto
  vfalta = 0;
  while (vfalta == 0) {
    printf("Digite quantas faltas o aluno tem :");
    scanf("%d", &estudante[h].faltas);
    //"vfalta"  se o valor eh valido eh 1 se  nao eh 0 e continua no loop
    vfalta = condicaofalta(estudante[h].faltas);
    if (vfalta == 0) {
      printf("Numero de faltas invalido\n");
    }
  }
}
//"cadastrarturmas" cadastra o vetor turmas
void cadastrarturmas(aluno *estudante, unsigned long int h) {
  int vturma = 0;
  vturma = 0;
  while (vturma == 0) {
    printf("Digite a turma:");
    scanf("%d", &estudante[h].turma);
    vturma = condicaoturma(estudante[h].turma);
    if (vturma == 0) {
      printf("Numero de Turma Invalido\n");
    }
  }
}
float media(aluno *estudante, unsigned long int h) {
  float media1 = 0;
  int j;

  for (j = 0; j < 4; j++) {
    media1 += estudante[h].notas[j];
  }
  media1 /= 4;
  return media1;
}

//"cadastro" cadastra um aluno
void cadastro(aluno *estudante, unsigned long int cont2, FILE *arquivo) {
  int i;
  // chamando funcoes para cadastrar o aluno

  cadastrarmatricula(estudante, cont2);
  cadastrarnome(estudante, cont2);
  cadastrarnotas(estudante, cont2);
  cadastrarfaltas(estudante, cont2);
  cadastrarturmas(estudante, cont2);

  printf("Aluno Cadastrado Com Sucesso!!\n");
}

int removernosistema(aluno *estudante, unsigned long int h, int m) {
  int i, j;
  int prov;
  for (i = 0; i < h; i++) {
    if (estudante[i].matricula == m) {
      estudante[i].matricula = -1;
      for (j = 0; j < 4; j++) {
        estudante[i].notas[j] = -1;
      }
      estudante[i].faltas = -1;
      estudante[i].turma = -1;
      return 1;
    }
  }
  return 0;
}
void atualizardados(aluno *estudante, unsigned long int h) {
  int i, matri, flag = 0;

  printf("Digite a matricula a ser atualziada:");
  scanf("%d", &matri);
  for (i = 0; i < h; i++) {
    if (matri == estudante[i].matricula) {
      cadastrarnotas(estudante, i);
      cadastrarfaltas(estudante, i);

      flag++;
    }
  }
  if (flag == 0) {
    printf("Matricula nao consta no sistema");
  }
}
void gravarnoarquivo(FILE *arquivo, aluno *estudante, unsigned long int cont2) {
  int i, j;
  arquivo = fopen("alunos.txt", "w");
  if (arquivo == NULL) {
    printf("nao abriu!");
  } else {
    for (i = 0; i < cont2; i++) {
      // printf("%d",cont2); //tirar duvida to tamanho
      if (estudante[i].matricula < 0) {
        continue;
      } else {

        fprintf(arquivo, "%d ", estudante[i].matricula);
        fprintf(arquivo, "%s ", estudante[i].nome);
        for (j = 0; j < 4; j++) {
          fprintf(arquivo, "%.2f ", estudante[i].notas[j]);
        }
        fprintf(arquivo, "%d ", estudante[i].faltas);
        fprintf(arquivo, "%d\n", estudante[i].turma);
      }
    }
    fclose(arquivo);
  }
}
void listaralunoscadastrados(aluno *estudante, unsigned long int h) {
  int turma, i, j, flag = 0;
  printf("Digite a turma a ser listada:");
  scanf("%d", &turma);
  for (i = 0; i < h; i++) {
    if (turma == estudante[i].turma) {
      printf("%d\n", estudante[i].matricula);
      for (j = 0; j < 4; j++) {
        printf("%.2f\n", estudante[i].notas[j]);
      }
      printf("%d", estudante[i].faltas);
      flag++;
    }
  }
  if (flag == 0) {
    printf("Nao existe alunos cadastrados na turma\n");
  }
}
int frequencia(int n) {
  int freque = 0;
  freque = 36 - n;

  return freque;
}
void listaralunosaprovados(aluno *estudante, unsigned long int cont2) {
  int turma, i, flag = 0, l;
  float h;
  printf("Digite a turma :");
  scanf("%d", &turma);

  for (i = 0; i < cont2; i++) {
    if (turma == estudante[i].turma) {
      h = media(estudante, i);
      l = frequencia(estudante[i].faltas);
      if (h >= 7 && l >= 21) {
        printf("\n%d\n", estudante[i].matricula);
        printf("%.2f\n", h);
        printf("%d\n", l);
        flag++;
      }
    }
  }
  if (flag == 0) {
    printf("Nao existe alunos aprovados nessa turma\n");
  }
}
void listaralunosreprovadospormedia(aluno *estudante, unsigned long int cont2) {
  int turma, i, flag = 0, l;
  float h;
  printf("Digite a turma :");
  scanf("%d", &turma);

  for (i = 0; i < cont2; i++) {
    if (turma == estudante[i].turma) {
      h = media(estudante, i);
      if (h < 7) {
        printf("\n%d\n", estudante[i].matricula);
        printf("%.2f\n", h);
        flag++;
      }
    }
  }
  if (flag == 0) {
    printf("Nao existe alunos reprovados nessa turma\n");
  }
}
void listaralunosreprovadosporfalta(aluno *estudante, unsigned long int cont2) {
  int turma, i, flag = 0, l;
  float h;
  printf("Digite a turma :");
  scanf("%d", &turma);

  for (i = 0; i < cont2; i++) {
    if (turma == estudante[i].turma) {
      l = frequencia(estudante[i].faltas);
      if (l < 21) {
        printf("\n%d\n", estudante[i].matricula);

        printf("%d\n", l);
        flag++;
      }
    }
  }
  if (flag == 0) {
    printf("Nao existe a alunos reprovados por faltas nessa turma\n");
  }
}
int verificar(aluno *estudante, int *n, unsigned long int k) {
  int i;
  for (i = 0; i <= k; i++) {
    if (estudante[k].turma == n[i]) {
      return -1;
    }
  }
  return 1;
}
void listaralunosporturma(aluno *estudante, unsigned long int h) {
  int i, j = 1, k, flag = 0;
  int *prov;
  prov = (int *)malloc(1 * sizeof(int));
  if (estudante[0].turma < 1) {
    printf("\n Nao existe alunos cadastrados\n");
  }
  for (i = 0; i < h; i++) {
    flag = 0;
    k = 0;
    for (j = 0; j < h; j++) {

      if (estudante[i].turma == estudante[j].turma &&
          verificar(estudante, prov, i) == 1 && estudante[j].matricula > 0) {
        if (flag == 0) {
          printf("\nAlunos da turma: %d\n", estudante[i].turma);
        }
        printf("\nMatricula: %d\n", estudante[j].matricula);
        printf("Media: %.2f\n", media(estudante, j));
        flag++;
      }
    }

    if (flag != 0) {
      prov[i] = estudante[i].turma;
      prov = (int *)realloc(prov, j + 1 * sizeof(int));
      j++;
    }
  }
}

void trocar(aluno tmp, aluno *a, unsigned long int j) {
  int l;

  tmp.matricula = a[j].matricula;
  strcpy(tmp.nome, a[j].nome);
  for (l = 0; l < 4; l++) {
    tmp.notas[l] = a[j].notas[l];
  }
  tmp.faltas = a[j].faltas;
  tmp.turma = a[j].turma;

  a[j].matricula = a[j + 1].matricula;
  strcpy(a[j].nome, a[j + 1].nome);
  for (l = 0; l < 4; l++) {
    a[j].notas[l] = a[j + 1].notas[l];
  }
  a[j].faltas = a[j + 1].faltas;
  a[j].turma = a[j + 1].turma;

  a[j + 1].matricula = tmp.matricula;
  strcpy(a[j + 1].nome, tmp.nome);
  for (l = 0; l < 4; l++) {
    a[j + 1].notas[l] = tmp.notas[l];
  }
  a[j + 1].faltas = tmp.faltas;
  a[j + 1].turma = tmp.turma;
}
void crescente(aluno *a, unsigned long int n, int h) {
  int i, j, l;
  float m1 = 0, m2 = 0;
  aluno tmp;
  for (i = 0; i < n; i++) {

    for (j = 0; j < n - i - 1; j++) {
      switch (h) {
      case 1:
        if (a[j].matricula > a[j + 1].matricula) {
          trocar(tmp, a, j);
        }
        break;
      case 2:
        if (strcmp(a[j].nome, a[j + 1].nome) > 0) {
          trocar(tmp, a, j);
        }
        break;
      case 3:
        m1 = media(a, j);
        m2 = media(a, j + 1);
        if (m1 > m2) {
          trocar(tmp, a, j);
        }
        break;
      case 4:
        if (a[j].faltas > a[j + 1].faltas) {
          trocar(tmp, a, j);
        }
        break;
      }
    }
  }
}
void decrescente(aluno *a, unsigned long int n, int h) {
  int i, j, l;
  float m1 = 0, m2 = 0;
  aluno tmp;
  for (i = 0; i < n; i++) {

    for (j = 0; j < n - i - 1; j++) {
      switch (h) {
      case 1:
        if (a[j].matricula < a[j + 1].matricula) {
          trocar(tmp, a, j);
        }
        break;
      case 2:
        if (strcmp(a[j].nome, a[j + 1].nome) < 0) {
          trocar(tmp, a, j);
        }
        break;
      case 3:
        m1 = media(a, j);
        m2 = media(a, j + 1);
        if (m1 < m2) {
          trocar(tmp, a, j);
        }
        break;
      case 4:
        if (a[j].faltas < a[j + 1].faltas) {
          trocar(tmp, a, j);
        }
        break;
      }
    }
  }
}
void menuord() {
  printf(" \nEscolha o modo da Orderncao:\n 1 - Matricula\n 2 - Nome\n 3 - "
         "Media\n 4 - Faltas\n");
}
void escolhaord() {
  printf(
      "\n escolha a forma da ordenacao:\n 1 - crescente\n 2 - Decrescente\n ");
}
void ordsuc() { printf("\nOrdenacao realizada com sucesso!!\n"); }
void ordmatricula(aluno *estudante, unsigned long int cont2) {
  int op;
  int h = 1;
  escolhaord();
  scanf("%d", &op);

  switch (op) {
  case 1:

    crescente(estudante, cont2, h);
    ordsuc();
    break;
  case 2:
    decrescente(estudante, cont2, h);
    ordsuc();
    break;
  default:
    erro();
    break;
  }
}
void ordmedia(aluno *estudante, unsigned long int cont2) {
  int op;
  int h = 3;
  escolhaord();
  scanf("%d", &op);

  switch (op) {
  case 1:
    crescente(estudante, cont2, h);
    ordsuc();
    break;
  case 2:
    decrescente(estudante, cont2, h);
    ordsuc();
    break;
  default:
    erro();
    break;
  }
}
void ordfaltas(aluno *estudante, unsigned long int cont2) {
  int op;
  int h = 4;
  escolhaord();
  scanf("%d", &op);

  switch (op) {
  case 1:
    crescente(estudante, cont2, h);
    ordsuc();
    break;
  case 2:
    decrescente(estudante, cont2, h);
    ordsuc();
    break;
  default:
    erro();
    break;
  }
}
void ordnome(aluno *estudante, unsigned long int cont2) {
  int op;
  int h = 2;
  escolhaord();
  scanf("%d", &op);

  switch (op) {
  case 1:
    crescente(estudante, cont2, h);
    ordsuc();
    break;
  case 2:
    decrescente(estudante, cont2, h);
    ordsuc();
    break;
  default:
    erro();
    break;
  }
}

void ordenacao(aluno *estudante, unsigned long int cont2) {
  int op;

  menuord();
  scanf("%d", &op);

  switch (op) {
  case 1:
    ordmatricula(estudante, cont2);
    break;
  case 2:
    ordnome(estudante, cont2);
    break;
  case 3:
    ordmedia(estudante, cont2);
    break;
  case 4:
    ordfaltas(estudante, cont2);
    break;
  default:
    erro();
    break;
  }
}
int main() {
  int op;
  int i, j;
  int removermatricula, condicaoremover;
  unsigned long int cont2 = 0;
  // lembrar muda as funcoes para unsigned long  int
  aluno *estudante;
  //(*aux[cont2]).matricula, aux[cont2] -> matricula , &(aux[cont2]-> matricula)

  estudante = (aluno *)malloc(1 * sizeof(aluno));

  FILE *arquivo;

  arquivo = fopen("alunos.txt", "a");
  fclose(arquivo);

  arquivo = fopen("alunos.txt", "r");

  if (arquivo == NULL) {
    printf("nao abriu!");
  } else {
    while (fscanf(arquivo, "%d %[^\n]s %f %f %f %f %d %d",
                  &estudante[cont2].matricula, estudante[cont2].nome,
                  &estudante[cont2].notas[0], &estudante[cont2].notas[1],
                  &estudante[cont2].notas[2], &estudante[cont2].notas[3],
                  &estudante[cont2].faltas, &estudante[cont2].turma) != EOF) {
      cont2++;
      
      estudante = (aluno *)realloc(estudante, (cont2+1) * sizeof(aluno));
    }
    fclose(arquivo);
  }

  do {
    menu();
    scanf("%d", &op);
    switch (op) {
    case 1:
      cont2++;
      estudante = (aluno *)realloc(estudante, (cont2+1) * sizeof(aluno));
      cadastro(estudante, cont2-1, arquivo);
      break;
    case 2:
      printf("Digite a matricula do aluno para removelo:");
      scanf("%d", &removermatricula);
      // chamando "removersitema" para remover a matricula e retornando se
      // romeveu ou nao
      condicaoremover = removernosistema(estudante, cont2, removermatricula);
      if (condicaoremover == 1) {
        printf("aluno removido\n");

      } else {
        printf("Matricula Nao Encontrada\n");
      }
      break;
    case 3:
      atualizardados(estudante, cont2);
      break;
    case 4:
      listaralunoscadastrados(estudante, cont2);
      break;
    case 5:
      listaralunosaprovados(estudante, cont2);
      break;
    case 6:
      listaralunosreprovadospormedia(estudante, cont2);
      break;
    case 7:
      listaralunosporturma(estudante, cont2);
      break;
    case 8:
      listaralunosreprovadosporfalta(estudante, cont2);
      break;
    case 9:
      ordenacao(estudante, cont2);
      break;
    case 0:
      gravarnoarquivo(arquivo, estudante, cont2);
      break;
    default:
      erro();
      break;
    }
  } while (op != 0);

  return 0;
}
