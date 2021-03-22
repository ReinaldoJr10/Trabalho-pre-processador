#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int procura_arquivo(char nome_arq[], char nome_procurado[]) {
  FILE * arq;
  char c1,c2,c3,c4,c5,c6,c7;
  int volta=sizeof(char);
  arq = fopen(nome_arq, "r");
  while (!feof(arq)) {
    c1=getc(arq);
    if (c1 == '#') {
      c2 = getc(arq);
      if (c2 == 'd') {
        c3 = getc(arq);
        if (c3 == 'e') {
          c4 = getc(arq);
          if (c4 == 'f') {
            c5 = getc(arq);
            if (c5 == 'i') {
              c6 = getc(arq);
              if (c6 == 'n') {
                c7 = getc(arq);
                if (c7 == 'e') {
                  return 1;
                } else fseek(arq, -(volta * 6), SEEK_CUR);
              } else fseek(arq, -(volta * 5), SEEK_CUR);
            } else fseek(arq, -(volta * 4), SEEK_CUR);
          } else fseek(arq, -(volta * 3), SEEK_CUR);
        } else fseek(arq, -(volta * 2), SEEK_CUR);
      } else fseek(arq, -(volta * 1), SEEK_CUR);
    }
  }
  fclose(arq);
  return 0;
}

int main() {
  setlocale(LC_ALL, "Portuguese");
  //Declaracao de variaveis usadas no programa
  FILE * arq1, * arq2, * arq3, * arq5, * arq6;
  char nome_arq[30], c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, biblioteca[25], caminho[50], palavra[25], caminho_final[50], nome_inicial[] = "etapa", ext[] = ".c", nome_final[30];
  char dados[10][10], chamada[10][10], nome_corpo[] = "corpo", nome_final_corpo[30], texto_define[200], nome_func[30], dados_func[30], corpo_func[150], corpo_func_mod[150], dados_chamada[30];
  float valor_define;
  int inscreve2 = 1, inscreve = 1, gh, tam_dados[10], volta = sizeof(char), sai = 1, sai2 = 1, sai3 = 1, sai4 = 1, cont = 0, cont2 = 0, cont3 = 0, cont4 = 0, cont5 = 0, cont6 = 0, cont7 = 0, ind, pula = 0, cont_arq = 0, posicao_antes, tipo = 0;
  int contCorpo = 0, tam_nome = 0, ind_x_chamada = 0, ind_y_chamada = 0, ind_y_muda;

  //Definindo o caminho para as bibliotecas estaticas nos diferentes sistemas operacionais
  #if _WIN32
  strcpy(caminho, "c:\\mingw\\include\\");
  #elif __linux__
  strcpy(caminho, "\\usr\\include\\");
  #elif __APPLE__
  strcpy(caminho, "\\usr\\include\\");
  #else
  printf("\n Sistema nao suportado");
  exit(1);
  #endif

  //Retirando o lixo das strings usadas para armazenar palavras
  for (int i = 0; i < 25; i++) {
    biblioteca[i] = '\0';
    palavra[i] = '\0';
  }
  for (int i = 0; i < 50; i++) {
    caminho_final[i] ='\0';
  }
  for (int x = 0; x < 10; x++) {
    for (int z = 0; z < 10; z++) {
      dados[x][z] = '\0';
      chamada[x][z] = '\0';
    }
  }
  for (int bu = 0; bu < 10; bu++) tam_dados[bu] = '\0';
  for (int i = 0; i < 200; i++) texto_define[i] = '\0';
  for (int i = 0; i < 150; i++) corpo_func[i] = '\0';
  for (int i = 0; i < 30; i++) {
    nome_func[i] = '\0';
    dados_func[i] = '\0';
    dados_chamada[i] = '\0';
  }

  //Pergunta ao usuario o nome para abertura do arquivo
  while (sai4) {
    printf("\n Qual é o nome do arquivo a ser processado?");
    gets(nome_arq);
    arq1 = fopen(nome_arq, "r");
    if (arq1 == NULL) {
      printf("\nNome inválido");
    } else sai4 = 0;
  }

  sprintf(nome_final, "%s%d%s", nome_inicial, cont_arq, ext);
  arq2 = fopen(nome_final, "w");

  //retira os comentarios do codigo fonte
  while (!feof(arq1)) {
    c1 = getc(arq1);
    if (c1 == '/') {
      c2 = getc(arq1);
      if (c2 == '/') {
        do {
          c3 = getc(arq1);
          if (c3 == '\n') {
            sai2 = 0;
          }
        } while (sai2);
        sai2 = 1;
      } else if (c2 == '*') {
        do {
          c1 = getc(arq1);
          if (c1 == '*') {
            c2 = getc(arq1);
            if (c2 == '/') {
              sai = 0;
            } else {
              fseek(arq1, -volta, SEEK_CUR);
            }
          }
        } while (sai);
      } else {
        fseek(arq1, -volta, SEEK_CUR);
        fputc(c1, arq2);
      }
    } else {
      if (c1 != 'ÿ')
        fputc(c1, arq2);
    }
  }

  fclose(arq1);
  fclose(arq2);

  //muda o nome do arquivo de leitura e escrita de acordo com a quantidade de vezes utilizada
  cont_arq++;
  arq1 = fopen(nome_final, "r");
  sprintf(nome_final, "%s%d%s", nome_inicial, cont_arq, ext);
  arq2 = fopen(nome_final, "w");

  //retira todos os espaços, tabulacoes e quebra de linhas desnecessarios
  while (!feof(arq1)) {
    c1 = getc(arq1);
    if (c1 == '>') {
      c2 = getc(arq1);
      fputc(c1, arq2);
      fputc(c2, arq2);
      sai3 = 0;
    }

    if (c1 == 'ÿ' || c1=='`') {
      sai3 = 0;
    }

    if (c1 == 'd') {
      c2 = getc(arq1);
      if (c2 == 'o') {
        c3 = getc(arq1);
        if (c3 == 'u') {
          c4 = getc(arq1);
          if (c4 == 'b') {
            c5 = getc(arq1);
            if (c5 == 'l') {
              c6 = getc(arq1);
              if (c6 == 'e') {
                c7 = getc(arq1);
                fputc(c1, arq2);
                fputc(c2, arq2);
                fputc(c3, arq2);
                fputc(c4, arq2);
                fputc(c5, arq2);
                fputc(c6, arq2);
                fputc(c7, arq2);
                sai3 = 0;
              } else fseek(arq1, -(volta * 5), SEEK_CUR);
            } else fseek(arq1, -(volta * 4), SEEK_CUR);
          } else fseek(arq1, -(volta * 3), SEEK_CUR);
        } else fseek(arq1, -(volta * 2), SEEK_CUR);
      } else fseek(arq1, -(volta * 1), SEEK_CUR);
    }

    if (c1 == 'f') {
      c2 = getc(arq1);
      if (c2 == 'l') {
        c3 = getc(arq1);
        if (c3 == 'o') {
          c4 = getc(arq1);
          if (c4 == 'a') {
            c5 = getc(arq1);
            if (c5 == 't') {
              c6 = getc(arq1);
              fputc(c1, arq2);
              fputc(c2, arq2);
              fputc(c3, arq2);
              fputc(c4, arq2);
              fputc(c5, arq2);
              fputc(c6, arq2);
              sai3 = 0;
            } else fseek(arq1, -(volta * 4), SEEK_CUR);
          } else fseek(arq1, -(volta * 3), SEEK_CUR);
        } else fseek(arq1, -(volta * 2), SEEK_CUR);
      } else fseek(arq1, -(volta * 1), SEEK_CUR);
    }

    if (c1 == 'F') {
      c2 = getc(arq1);
      if (c2 == 'I') {
        c3 = getc(arq1);
        if (c3 == 'L') {
          c4 = getc(arq1);
          if (c4 == 'E') {
            c5 = getc(arq1);
            fputc(c1, arq2);
            fputc(c2, arq2);
            fputc(c3, arq2);
            fputc(c4, arq2);
            fputc(c5, arq2);
            sai3 = 0;
          } else fseek(arq1, -(volta * 3), SEEK_CUR);
        } else fseek(arq1, -(volta * 2), SEEK_CUR);
      } else fseek(arq1, -(volta * 1), SEEK_CUR);
    }

    if (c1 == 'c') {
      c2 = getc(arq1);
      if (c2 == 'h') {
        c3 = getc(arq1);
        if (c3 == 'a') {
          c4 = getc(arq1);
          if (c4 == 'r') {
            c5 = getc(arq1);
            fputc(c1, arq2);
            fputc(c2, arq2);
            fputc(c3, arq2);
            fputc(c4, arq2);
            fputc(c5, arq2);
            sai3 = 0;
          } else fseek(arq1, -(volta * 3), SEEK_CUR);
        } else fseek(arq1, -(volta * 2), SEEK_CUR);
      } else fseek(arq1, -(volta * 1), SEEK_CUR);
    }

    if (c1 == 'l') {
      c2 = getc(arq1);
      if (c2 == 'o') {
        c3 = getc(arq1);
        if (c3 == 'n') {
          c4 = getc(arq1);
          if (c4 == 'g') {
            c5 = getc(arq1);
            fputc(c1, arq2);
            fputc(c2, arq2);
            fputc(c3, arq2);
            fputc(c4, arq2);
            fputc(c5, arq2);
            sai3 = 0;
          } else fseek(arq1, -(volta * 3), SEEK_CUR);
        } else fseek(arq1, -(volta * 2), SEEK_CUR);
      } else fseek(arq1, -(volta * 1), SEEK_CUR);
    }

    if (c1 == 'v') {
      c2 = getc(arq1);
      if (c2 == 'o') {
        c3 = getc(arq1);
        if (c3 == 'i') {
          c4 = getc(arq1);
          if (c4 == 'd') {
            c5 = getc(arq1);
            fputc(c1, arq2);
            fputc(c2, arq2);
            fputc(c3, arq2);
            fputc(c4, arq2);
            fputc(c5, arq2);
            sai3 = 0;
          } else fseek(arq1, -(volta * 3), SEEK_CUR);
        } else fseek(arq1, -(volta * 2), SEEK_CUR);
      } else fseek(arq1, -(volta * 1), SEEK_CUR);
    }

    if (c1 == 'e') {
      c2 = getc(arq1);
      if (c2 == 'l') {
        c3 = getc(arq1);
        if (c3 == 's') {
          c4 = getc(arq1);
          if (c4 == 'e') {
            c5 = getc(arq1);
            fputc(c1, arq2);
            fputc(c2, arq2);
            fputc(c3, arq2);
            fputc(c4, arq2);
            fputc(c5, arq2);
            sai3 = 0;
          } else fseek(arq1, -(volta * 3), SEEK_CUR);
        } else fseek(arq1, -(volta * 2), SEEK_CUR);
      } else fseek(arq1, -(volta * 1), SEEK_CUR);
    }

    if (c1 == 'c') {
      c2 = getc(arq1);
      if (c2 == 'a') {
        c3 = getc(arq1);
        if (c3 == 's') {
          c4 = getc(arq1);
          if (c4 == 'e') {
            c5 = getc(arq1);
            fputc(c1, arq2);
            fputc(c2, arq2);
            fputc(c3, arq2);
            fputc(c4, arq2);
            fputc(c5, arq2);
            sai3 = 0;
          } else fseek(arq1, -(volta * 3), SEEK_CUR);
        } else fseek(arq1, -(volta * 2), SEEK_CUR);
      } else fseek(arq1, -(volta * 1), SEEK_CUR);
    }

    if (c1 == 'r') {
      c2 = getc(arq1);
      if (c2 == 'e') {
        c3 = getc(arq1);
        if (c3 == 't') {
          c4 = getc(arq1);
          if (c4 == 'u') {
            c5 = getc(arq1);
            if (c5 == 'r') {
              c6 = getc(arq1);
              if (c6 == 'n') {
                c7 = getc(arq1);
                fputc(c1, arq2);
                fputc(c2, arq2);
                fputc(c3, arq2);
                fputc(c4, arq2);
                fputc(c5, arq2);
                fputc(c6, arq2);
                fputc(c7, arq2);
                sai3 = 0;
              } else fseek(arq1, -(volta * 5), SEEK_CUR);
            } else fseek(arq1, -(volta * 4), SEEK_CUR);
          } else fseek(arq1, -(volta * 3), SEEK_CUR);
        } else fseek(arq1, -(volta * 2), SEEK_CUR);
      } else fseek(arq1, -(volta * 1), SEEK_CUR);
    }

    if (c1 == 'i') {
      c2 = getc(arq1);
      if (c2 == 'n') {
        c3 = getc(arq1);
        if (c3 == 't') {
          c4 = getc(arq1);
          fputc(c1, arq2);
          fputc(c2, arq2);
          fputc(c3, arq2);
          fputc(c4, arq2);
          sai3 = 0;
        } else fseek(arq1, -(volta * 2), SEEK_CUR);
      } else fseek(arq1, -volta, SEEK_CUR);
    }

    if (c1 == 't') {
      c2 = getc(arq1);
      if (c2 == 'y') {
        c3 = getc(arq1);
        if (c3 == 'p') {
          c4 = getc(arq1);
          if (c4 == 'e') {
            c5 = getc(arq1);
            if (c5 == 'd') {
              c6 = getc(arq1);
              if (c6 == 'e') {
                c7 = getc(arq1);
                if (c7 == 'f') {
                  c8 = getc(arq1);
                  fputc(c1, arq2);
                  fputc(c2, arq2);
                  fputc(c3, arq2);
                  fputc(c4, arq2);
                  fputc(c5, arq2);
                  fputc(c6, arq2);
                  fputc(c7, arq2);
                  fputc(c8, arq2);
                  sai3 = 0;
                } else fseek(arq1, -(volta * 6), SEEK_CUR);
              } else fseek(arq1, -(volta * 5), SEEK_CUR);
            } else fseek(arq1, -(volta * 4), SEEK_CUR);
          } else fseek(arq1, -(volta * 3), SEEK_CUR);
        } else fseek(arq1, -(volta * 2), SEEK_CUR);
      } else fseek(arq1, -(volta * 1), SEEK_CUR);
    }

    if (c1 == '#') {
      fputc(c1, arq2);
      c9 = getc(arq1);
      while (c9 != '\n') {
        fputc(c9, arq2);
        c9 = getc(arq1);
      }
      fputc(c9, arq2);
      sai = 0;
    }

    if (c1 == 's') {
      c2 = getc(arq1);
      if (c2 == 't') {
        c3 = getc(arq1);
        if (c3 == 'r') {
          c4 = getc(arq1);
          if (c4 == 'u') {
            c5 = getc(arq1);
            if (c5 == 'c') {
              c6 = getc(arq1);
              if (c6 == 't') {
                c7 = getc(arq1);
                fputc(c1, arq2);
                fputc(c2, arq2);
                fputc(c3, arq2);
                fputc(c4, arq2);
                fputc(c5, arq2);
                fputc(c6, arq2);
                fputc(c7, arq2);
                sai3 = 0;
              } else fseek(arq1, -(volta * 5), SEEK_CUR);
            } else fseek(arq1, -(volta * 4), SEEK_CUR);
          } else fseek(arq1, -(volta * 3), SEEK_CUR);
        } else fseek(arq1, -(volta * 2), SEEK_CUR);
      } else fseek(arq1, -(volta * 1), SEEK_CUR);
    }

    if (c1 == '"') {
      fputc(c1, arq2);
      c2 = getc(arq1);
      fputc(c2, arq2);
      while (c2 != '"') {
        c2 = getc(arq1);
        fputc(c2, arq2);
      }
      sai3 = 0;
    }

    if (c1 != 'ÿ' && c1 != '\t' && c1 != ' ' && c1 != '\n' && c1 != '#') {
      if (sai3) fputc(c1, arq2);
      sai3 = 1;
    }
  }

  fclose(arq1);
  fclose(arq2);

  //expandi os define fixos com apenas um valor especificado
  while (procura_arquivo(nome_final, "#define") == 1) {
    cont_arq++;

    arq1 = fopen(nome_final, "r");
    sprintf(nome_final, "%s%d%s", nome_inicial, cont_arq, ext);
    arq2 = fopen(nome_final, "w");

    while (!feof(arq1)) {
      c1 = getc(arq1);
      if (c1 == '#') {
        c2 = getc(arq1);
        if (c2 == 'i') {
          c3 = getc(arq1);
          if (c3 == 'n') {
            c4 = getc(arq1);
            if (c4 == 'c') {
              c5 = getc(arq1);
              if (c5 == 'l') {
                c6 = getc(arq1);
                if (c6 == 'u') {
                  c7 = getc(arq1);
                  if (c7 == 'd') {
                    c8 = getc(arq1);
                    if (c8 == 'e') {
                      c9 = getc(arq1);
                      fputc(c1, arq2);
                      fputc(c2, arq2);
                      fputc(c3, arq2);
                      fputc(c4, arq2);
                      fputc(c5, arq2);
                      fputc(c6, arq2);
                      fputc(c7, arq2);
                      fputc(c8, arq2);
                      fputc(c9, arq2);
                      c10 = getc(arq1);
                      while (c10 != '\n') {
                        fputc(c10, arq2);
                        c10 = getc(arq1);
                      }
                      fputc(c10, arq2);
                    }
                  } else fseek(arq1, -(volta * 6), SEEK_CUR);
                } else fseek(arq1, -(volta * 5), SEEK_CUR);
              } else fseek(arq1, -(volta * 4), SEEK_CUR);
            } else fseek(arq1, -(volta * 3), SEEK_CUR);
          } else fseek(arq1, -(volta * 2), SEEK_CUR);
        } else fseek(arq1, -(volta * 1), SEEK_CUR);
      }
      if (c1 == '#') {
        c2 = getc(arq1);
        if (c2 == 'd') {
          c3 = getc(arq1);
          if (c3 == 'e') {
            c4 = getc(arq1);
            if (c4 == 'f') {
              c5 = getc(arq1);
              if (c5 == 'i') {
                c6 = getc(arq1);
                if (c6 == 'n') {
                  c7 = getc(arq1);
                  if (c7 == 'e') {
                    c8 = getc(arq1);
                    posicao_antes = ftell(arq1);
                    c9 = getc(arq1);
                    while (c9 != '\n') {
                      if (c9 == '(' || c9 == ')') tipo = 1;
                      c9 = getc(arq1);
                    }
                    fseek(arq1, posicao_antes, SEEK_SET);

                    if (tipo == 0) {
                      c9 = getc(arq1);
                      while (c9 != ' ') {
                        palavra[cont2] = c9;
                        cont2++;
                        c9 = getc(arq1);
                      }
                      fscanf(arq1, "%f \n", & valor_define);
                      //posicao = ftell(arq1);
                      while (!feof(arq1)) {
                        c12 = getc(arq1);
                        if (c12 != 'ÿ') fputc(c12, arq2);
                        if (c12 == '"') {
                          c12 = getc(arq1);
                          fputc(c12, arq2);
                          while (c12 != '"') {
                            c12 = getc(arq1);
                            fputc(c12, arq2);
                          }
                        }
                        if (c12 == palavra[0]) {
                          for (ind = 1; ind < cont2; ind++)
                            c12 = getc(arq1);
                          if (ind == cont2) {
                            fseek(arq2, -volta, SEEK_CUR);
                            fprintf(arq2, "%f", valor_define);
                          }
                        }
                      }
                      pula = 1;
                      cont2 = 0;
                    } else {
                      while ((c9 = getc(arq1)) != '\n') {
                        texto_define[cont5] = c9;
                        cont5++;
                      }
                      cont5 = 0;
                      while (texto_define[cont5] != '(') {
                        nome_func[cont5] = texto_define[cont5];
                        cont5++;
                        tam_nome++;
                      }
                      while (texto_define[cont5] != ')') {
                        dados_func[cont3] = texto_define[cont5];
                        cont5++;
                        cont3++;
                      }
                      dados_func[cont3] = texto_define[cont5];

                      for (int h = 1; h < cont3; h++) {
                        if (dados_func[h] != ',' && dados_func[h] != ' ') {
                          dados[ind_y_chamada][ind_x_chamada] = dados_func[h];
                          ind_x_chamada++;
                        } else if (dados_func[h] != ' ') {
                          tam_dados[ind_y_chamada] = ind_x_chamada;
                          ind_x_chamada = 0;
                          ind_y_chamada++;
                        }
                      }

                      tam_dados[ind_y_chamada] = ind_x_chamada;
                      ind_y_muda = ind_y_chamada;
                      ind_x_chamada = 0;
                      ind_y_chamada = 0;
                      cont3 = 0;
                      cont5++;
                      while (texto_define[cont5] != '}') {
                        corpo_func[cont4] = texto_define[cont5];
                        cont5++;
                        cont4++;
                      }
                      corpo_func[cont4] = texto_define[cont5];

                      while (!feof(arq1)) {
                        c12 = getc(arq1);
                        if (c12 == '"') {
                          fputc(c12, arq2);
                          c12 = getc(arq1);
                          fputc(c12, arq2);
                          while (c12 != '"') {
                            c12 = getc(arq1);
                            fputc(c12, arq2);
                          }
                          inscreve2 = 0;
                        }
                        if (c12 == nome_func[0]) {
                          for (ind = 1; ind < tam_nome; ind++) {
                            c12 = getc(arq1);
                            if (c12 != nome_func[ind]) {
                              fseek(arq1, -volta * (ind + 1), SEEK_CUR);
                              c12 = getc(arq1);
                              fputc(c12, arq2);
                              inscreve2 = 0;
                              break;
                            }
                          }
                          if (ind == tam_nome) {
                            if (c12 != ' ') {
                              dados_chamada[cont6] = c12;
                              cont6++;
                            }
                            while ((c12 = getc(arq1)) != ')') {
                              dados_chamada[cont6] = c12;
                              cont6++;
                              inscreve2 = 0;
                            }
                            dados_chamada[cont6] = c12;
                            for (int h = 1; h < cont6; h++) {
                              if (dados_chamada[h] != ',' && dados_chamada[h] != ' ' && dados_chamada[h] != '(') {
                                chamada[ind_y_chamada][ind_x_chamada] = dados_chamada[h];
                                ind_x_chamada++;
                              } else if (dados_chamada[h] != ' ' && dados_chamada[h] != '(') {
                                ind_x_chamada = 0;
                                ind_y_chamada++;
                              }
                            }
                            ind_x_chamada = 0;
                            ind_y_chamada = 0;

                            sprintf(nome_final_corpo, "%s%d.c", nome_corpo, contCorpo);
                            arq5 = fopen(nome_final_corpo, "w");
                            fprintf(arq5, "%s", corpo_func);
                            fclose(arq5);

                            for (int n = 0; n <= ind_y_muda; n++) {
                              contCorpo++;
                              arq5 = fopen(nome_final_corpo, "r");
                              sprintf(nome_final_corpo, "%s%d.c", nome_corpo, contCorpo);
                              arq6 = fopen(nome_final_corpo, "w");

                              while (!feof(arq5)) {
                                c13 = getc(arq5);
                                if (c13 == dados[n][0]) {
                                  for (gh = 1; gh < tam_dados[n]; gh++) {
                                    c13 = getc(arq5);
                                    if (c13 != dados[n][gh]) {
                                      fseek(arq5, -volta * (gh + 1), SEEK_CUR);
                                      c13 = getc(arq5);
                                      fputc(c13, arq6);
                                      inscreve = 0;
                                      break;
                                    }
                                  }
                                  if (gh == tam_dados[n]) {
                                    fprintf(arq6, "%s", chamada[n]);
                                    c13 = getc(arq5);

                                  }

                                }
                                if (c13 != 'ÿ' && inscreve == 1) fputc(c13, arq6);
                                inscreve = 1;

                              }
                              fclose(arq5);
                              fclose(arq6);

                              arq5 = fopen(nome_final_corpo, "r");

                              while (!feof(arq5)) {
                                c13 = getc(arq5);
                                if (c13 != 'ÿ') corpo_func_mod[cont7] = c13;
                                cont7++;
                              }

                              fclose(arq5);

                              for (int io = cont7; io < 150; io++) corpo_func_mod[io] = '\0';

                              for (int io = 1; io < 150; io++)
                                if (corpo_func_mod[io] == '}') cont7 = io + 1;

                              for (int io = cont7; io < 150; io++) corpo_func_mod[io] = '\0';
                              cont7 = 0;

                            }

                            contCorpo = 0;

                            fprintf(arq2, "%s", corpo_func_mod);
                            for (int x = 0; x < 10; x++) {
                              for (int z = 0; z < 10; z++) {
                                chamada[x][z] = '\0';
                              }
                            }
                          }
                        }
                        for (int y = 0; y < 30; y++)    dados_chamada[y] = '\0';
                        cont6 = 0;
                        ind = 0;
                        if (c12 != 'ÿ' && inscreve2 == 1) fputc(c12, arq2);
                        inscreve2 = 1;
                      }
                      cont5 = 0;
                    }
                  } else fseek(arq1, -(volta * 6), SEEK_CUR);
                } else fseek(arq1, -(volta * 5), SEEK_CUR);
              } else fseek(arq1, -(volta * 4), SEEK_CUR);
            } else fseek(arq1, -(volta * 3), SEEK_CUR);
          } else fseek(arq1, -(volta * 2), SEEK_CUR);
        } else fseek(arq1, -(volta * 1), SEEK_CUR);
      }
      if (pula) fputc(c1, arq2);
      pula = 0;

    }

    fclose(arq1);
    fclose(arq2);

  }

  //muda o nome do arquivo de leitura e escrita de acordo com a quantidade de vezes utilizada
  cont_arq++;
  arq1 = fopen(nome_final, "r");
  sprintf(nome_final, "%s%d%s", nome_inicial, cont_arq, ext);
  arq2 = fopen(nome_final, "w");

  //abre os include do codigo
  while (!feof(arq1)) {
    c1 = getc(arq1);
    if (c1 == '#') {
      c2 = getc(arq1);
      if (c2 == 'i') {
        c3 = getc(arq1);
        if (c3 == 'n') {
          c4 = getc(arq1);
          if (c4 == 'c') {
            c5 = getc(arq1);
            if (c5 == 'l') {
              c6 = getc(arq1);
              if (c6 == 'u') {
                c7 = getc(arq1);
                if (c7 == 'd') {
                  c8 = getc(arq1);
                  if (c8 == 'e') {
                    c9 = getc(arq1);
                    c10 = getc(arq1);
                    if (c10 == '<' || c10 == '"') {
                      while (c11 != '"' && c11 != '>') {
                        c11 = getc(arq1);
                        if (c11 != '"' && c11 != '>') {
                          biblioteca[cont] = c11;
                          cont++;
                        }
                      }
                      c11 = getc(arq1);
                      cont = 0;

                      strcat(caminho_final, caminho);
                      strcat(caminho_final, biblioteca);
                      arq3 = fopen(caminho_final, "r");
                      caminho_final[0] = '\0';
                      for (int y = 0; y < 25; y++) biblioteca[y] = '\0';
                      if (arq3 != NULL) {

                        while (!feof(arq3)) {
                          c12 = getc(arq3);
                          if (c12 != 'ÿ') fputc(c12, arq2);
                        }
                      } else printf("\n NULL");
                      fclose(arq3);
                    }
                  } else fseek(arq1, -(volta * 7), SEEK_CUR);
                } else fseek(arq1, -(volta * 6), SEEK_CUR);
              } else fseek(arq1, -(volta * 5), SEEK_CUR);
            } else fseek(arq1, -(volta * 4), SEEK_CUR);
          } else fseek(arq1, -(volta * 3), SEEK_CUR);
        } else fseek(arq1, -(volta * 2), SEEK_CUR);
      } else fseek(arq1, -(volta * 1), SEEK_CUR);
    }

    if (c1 == '#') {
      c2 = getc(arq1);
      if (c2 == 'd') {
        c3 = getc(arq1);
        if (c3 == 'e') {
          c4 = getc(arq1);
          if (c4 == 'f') {
            c5 = getc(arq1);
            if (c5 == 'i') {
              c6 = getc(arq1);
              if (c6 == 'n') {
                c7 = getc(arq1);
                if (c7 == 'e') {
                  c8 = getc(arq1);
                  fputc(c1, arq2);
                  fputc(c2, arq2);
                  fputc(c3, arq2);
                  fputc(c4, arq2);
                  fputc(c5, arq2);
                  fputc(c6, arq2);
                  fputc(c7, arq2);
                  fputc(c8, arq2);
                  c9 = getc(arq1);
                  while (c9 != '\n') {
                    fputc(c9, arq2);
                    c9 = getc(arq1);
                  }
                  fputc(c9, arq2);
                } else fseek(arq1, -(volta * 6), SEEK_CUR);
              } else fseek(arq1, -(volta * 5), SEEK_CUR);
            } else fseek(arq1, -(volta * 4), SEEK_CUR);
          } else fseek(arq1, -(volta * 3), SEEK_CUR);
        } else fseek(arq1, -(volta * 2), SEEK_CUR);
      } else fseek(arq1, -(volta * 1), SEEK_CUR);
    }

    if (c1 != 'ÿ' && c1 != '#')
      fputc(c1, arq2);
  }

  fclose(arq1);
  fclose(arq2);

  //cria o arquivo finalizado e copia o ultimo arquivo utilizado para ele
  arq1 = fopen(nome_final, "r");
  sprintf(nome_arq, "%s%s", "arq_processado", ext);
  arq2 = fopen(nome_arq, "w");

  while ((c13 = getc(arq1)) != EOF) {
    fputc(c13, arq2);
  }

  fclose(arq1);
  fclose(arq2);

  printf("\n Arquivo processado e salvo no mesmo diretotio com o nome '%s'", nome_arq);
  return 0;
}
