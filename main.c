#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

void aumentarBrilho(int** original, int linhas, int colunas, int maxValor)
{	int l, c;
	for(l=0; l<linhas; l++)
	{	for(c=0; c<colunas; c++)
		{	original[l][c] = (int)(original[l][c] * 1.2);
			if(original[l][c] > maxValor)
				original[l][c] = maxValor;
		}
	}
}

void aumentarContraste(int** original, int linhas, int colunas, int maxValor)
{	int l, c;
	for(l=0; l<linhas; l++)
	{	for(c=0; c<colunas; c++)
		{	
			original[l][c] = maxValor/ (1.0 + exp(-(10.0 * original[l][c]/(float)maxValor - 5.0)));
		        
		}
	}
	
}

int ** girar (int** original, int * plinhas, int * pcolunas)
{	int l, c;
	int **nova, i, L = *pcolunas, C = *plinhas;
	nova = (int **) malloc(L * sizeof(int *));
	for(i=0; i<L; i++)
		nova[i] = (int *) malloc(C * sizeof(int));
	
	for(l=0; l<L; l++)
		for(c=0; c<C; c++)
			nova[l][c] = original[c][l];
	
	espelhar (nova, L, C);
	*plinhas = L;
	*pcolunas = C;
	return nova;
}

void diminuirContraste(int** original, int linhas, int colunas, int maxValor)
{	int l, c;
	for(l=0; l<linhas; l++)
	{	for(c=0; c<colunas; c++)
		{	
			original[l][c] = maxValor/ (1.0 + exp(-(2.0 * original[l][c]/(float)maxValor - 1.0)));
		}
	}
	
}



void espelhar(int** original, int linhas, int colunas)
{	int l,c,aux;
	for(l=0; l < linhas; l++)
	{
        for(c=0; c < colunas / 2; c++)
		{	
		    aux = original[l][c];
		    original[l][c] = original[l][colunas - 1 - c];
			original[l][colunas - 1 - c] = aux;
		}
	}
}

void espelharV(int** original, int linhas, int colunas)
{	int l,c,aux;
	for(l=0; l<linhas/2; l++)
		for(c=0; c<colunas; c++)
		{	aux = original[l][c];
			original[l][c] = original[linhas - 1 - l][c];
			original[linhas - 1 - l][c] = aux;
		}
}

void diminuirBrilho(int** original, int linhas, int colunas)
{	int l, c;
	for(l=0; l<linhas; l++)
	{	for(c=0; c<colunas; c++)
		{	original[l][c] = (int)(original[l][c] / 1.2);
		}
	}
}

int** borrar(int** original, int linhas, int colunas, int tB)
{	int l, c;
	int **nova, i;
	nova = (int **) malloc(linhas * sizeof(int *));
	for(i=0; i<linhas; i++)
		nova[i] = (int *) malloc(colunas * sizeof(int));
	
	for(l=0; l<linhas; l++)
	{
		for(c=0; c<colunas; c++)
		{
		    int soma=original[l][c], cont=1;
		    int coordl, coordc;
		    //cima
		    coordc=c;
		    coordl=l-tB;
		    if(coordl>=0 && coordl<linhas && coordc>=0 && coordc<colunas)
		    {   soma = soma + original[coordl][coordc];
		        cont++;
		    }
		    //baixo
		    coordc=c;
		    coordl=l+tB;
		    if(coordl>=0 && coordl<linhas && coordc>=0 && coordc<colunas)
		    {   soma = soma + original[coordl][coordc];
		        cont++;
		    }
		    //esquerda
		    coordc=c-tB;
		    coordl=l;
		    if(coordl>=0 && coordl<linhas && coordc>=0 && coordc<colunas)
		    {   soma = soma + original[coordl][coordc];
		        cont++;
		    }
		    //direita
		    coordc=c+tB;
		    coordl=l;
		    if(coordl>=0 && coordl<linhas && coordc>=0 && coordc<colunas)
		    {   soma = soma + original[coordl][coordc];
		        cont++;
		    }
		    nova[l][c] = soma/cont;
		}
	}		
	return nova;
}


int** lerImagem(char * nomeArquivo, int *pLinhas, int *pColunas, int *pMaxValor)
{	FILE *fp;
	fp = fopen(nomeArquivo,"r");
	/* Arquivo ASCII, para leitura */
	if(!fp)
	{	printf( "\nErro na abertura do arquivo\n\n");
		exit(-1);
	}
	//leia tipo do arquivo
	char buffer[1001];
	fgets (buffer, 1000, fp); //Primeira linha
	if(strstr(buffer, "P2") == NULL) // o tipo de arquivo eh diferente de P2?
	{	printf( "\nErro no tipo do arquivo\n\n");
		exit(-2);
	}
	//leia comentario
	fgets (buffer, 1000, fp);
	
	//leia dados da imagem
	fscanf(fp, "%d%d%d", pColunas, pLinhas, pMaxValor);
	
	//criando a matriz
	int **mat, i;
	mat = (int **) malloc(*pLinhas * sizeof(int *));
	for(i=0; i< *pLinhas; i++)
		mat[i] = (int *) malloc(*pColunas * sizeof(int));
	int l, c;
	for(l=0; l<*pLinhas; l++)
	{	for(c=0; c<*pColunas; c++)
			fscanf(fp, "%d", &mat[l][c]);
	}
	fclose(fp);
	return mat;
}
void escreverImagem(char * nomeArquivo, int ** mat, int linhas, int colunas, int maxValor)
{	FILE *fp;
	fp = fopen(nomeArquivo,"w");
	// Arquivo ASCII, para leitura
	if(!fp)
	{	printf( "\nErro na abertura do arquivo\n\n");
		exit(-1);
	}
	//escreva tipo do arquivo
	fprintf (fp, "P2\n");
	//escreva comentario
	fprintf (fp, "#Figura modificada...\n");
	//colunas, linhas
	fprintf(fp, "%d %d\n", colunas, linhas);
	//maxValor
	fprintf(fp, "%d\n", maxValor);
	int l, c;
	for(l=0; l<linhas; l++)
	{	for(c=0; c<colunas; c++)
		{	fprintf(fp, "%d ", mat[l][c]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}
int main(int argc, char * argv[])
{	char opcao[10];
	int linhas=0, colunas=0, maxValor=0, **mat=NULL;
	int tamanhoBorrao = 8;
	char nomeArquivo[100]="";
	char nomeArquivoLeitura[100]="";
	char nomeArquivoEscrita[100]="";
	while(opcao[0] != 'l')
	{	printf("\n\nMini-photoshop\n\n");
		printf("a) Ler imagem\n");	
		printf("b) Gravar imagem\n");	
		printf("c) Aumentar o brilho\n");	
		printf("d) Diminuir o brilho\n");	
		printf("e) Aumentar contraste\n");
		printf("f) Diminuir contraste\n");
		printf("g) Desfocar\n");
		printf("h) Fazer moldura\n");
		printf("i) Espelhar imagem (horizontal)\n");
		printf("j) Espelhar imagem (vertical)\n");
		printf("k) Girar\n");
		printf("l) Sair\n");
		printf("\nEntre a opcao desejada: ");	
		fgets(opcao, 10, stdin);
		switch(opcao[0])
		{	case 'a':
				printf("\n\nEntre com o nome da imagem (sem extensao): ");
				fgets(nomeArquivo, 100, stdin);
				nomeArquivo[strlen(nomeArquivo)-1]='\0';
				strcpy (nomeArquivoLeitura, nomeArquivo);
				strcat (nomeArquivoLeitura, ".pgm");
				mat = lerImagem(nomeArquivoLeitura, &linhas, &colunas, &maxValor);
				break;
			case 'b':
				strcpy (nomeArquivoEscrita, nomeArquivo);	
				strcat (nomeArquivoEscrita, "_editada.pgm");
				printf("\n\nA imagem sera salva como %s\n", nomeArquivoEscrita);
				escreverImagem(nomeArquivoEscrita, mat, linhas, colunas, maxValor);
				break;
			case 'c':
				aumentarBrilho(mat, linhas, colunas, maxValor); // feito
				break;
			case 'd':
			    diminuirBrilho(mat, linhas, colunas); // feito
				//diminuirBrilho(mat, linhas, colunas, maxValor);
				break;
			case 'e':
			    aumentarContraste(mat, linhas, colunas, maxValor); // feito
				//aumentarContraste(mat, linhas, colunas, maxValor);
				break;
			case 'f':
				diminuirContraste(mat, linhas, colunas, maxValor); // feito
				break;
			case 'g':
				mat = borrar(mat, linhas, colunas, tamanhoBorrao);	
				break;
			case 'h':
				//moldura(mat, linhas, colunas, maxValor);
				break;
			case 'i':
			    espelhar(mat, linhas, colunas);
			    break;
			case 'j':
			    espelharV(mat, linhas, colunas);
			    break;
			case 'k':
				mat = girar(mat, &linhas, &colunas);
				break;
		}
	}
	return 0;
}


