#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct pixel
{	int R, G, B;
} PIXEL;
void aumentarBrilho(PIXEL** original, int linhas, int colunas, int maxValor)
{	int l, c;
	for(l=0; l<linhas; l++)
	{	for(c=0; c<colunas; c++)
		{	original[l][c].R = (int)(original[l][c].R * 1.2);
			if(original[l][c].R > maxValor)
				original[l][c].R = maxValor;
			original[l][c].G = (int)(original[l][c].G * 1.2);
			if(original[l][c].G > maxValor)
				original[l][c].G = maxValor;
			original[l][c].B = (int)(original[l][c].B * 1.2);
			if(original[l][c].B > maxValor)
				original[l][c].B = maxValor;
		}
	}
}

PIXEL** bandeiraFranca(int *linhas, int *colunas, int *maxValor)
{   //criando a matriz
	PIXEL **mat;
	int i;
	*linhas=200;
	*colunas = 300;
	*maxValor = 255;
	mat = (PIXEL **) malloc(200 * sizeof(PIXEL *));
	for(i=0; i< 200; i++)
		mat[i] = (PIXEL *) malloc(300 * sizeof(PIXEL));
	int l, c;
	for(l=0; l<200; l++)
	{	for(c=0; c<100; c++)
	    {   mat[l][c].R = 0;
	        mat[l][c].G = 0;
	        mat[l][c].B = 255;
	    }
	    for(c=100; c<200; c++)
	    {   mat[l][c].R = 255;
	        mat[l][c].G = 255;
	        mat[l][c].B = 255;
	    }
	    for(c=200; c<300; c++)
	    {   mat[l][c].R = 255;
	        mat[l][c].G = 0;
	        mat[l][c].B = 0;
	    }
	}
	return mat;
}

PIXEL** lerImagem(char * nomeArquivo, int *pLinhas, int *pColunas, int *pMaxValor)
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
	if(strstr(buffer, "P3") == NULL) // o tipo de arquivo eh diferente de P3?
	{	printf( "\nErro no tipo do arquivo\n\n");
		exit(-2);
	}
	//leia comentario
	fgets (buffer, 1000, fp);
	
	//leia dados da imagem
	fscanf(fp, "%d%d%d", pColunas, pLinhas, pMaxValor);
	//criando a matriz
	PIXEL **mat;
	int i;
	mat = (PIXEL **) malloc(*pLinhas * sizeof(PIXEL *));
	for(i=0; i< *pLinhas; i++)
		mat[i] = (PIXEL *) malloc(*pColunas * sizeof(PIXEL));
	int l, c;
	for(l=0; l<*pLinhas; l++)
	{	for(c=0; c<*pColunas; c++)
		{	fscanf(fp, "%d", &mat[l][c].R);
			fscanf(fp, "%d", &mat[l][c].G);
			fscanf(fp, "%d", &mat[l][c].B);
		}
	}
	fclose(fp);
	return mat;
}
void escreverImagem(char * nomeArquivo, PIXEL ** mat, int linhas, int colunas, int maxValor)
{	FILE *fp;
	fp = fopen(nomeArquivo,"w");
	// Arquivo ASCII, para leitura
	if(!fp)
	{	printf( "\nErro na abertura do arquivo\n\n");
		exit(-1);
	}
	//escreva tipo do arquivo
	fprintf (fp, "P3\n");
	//escreva comentario
	fprintf (fp, "#Figura modificada...\n");
	//colunas, linhas
	fprintf(fp, "%d %d\n", colunas, linhas);
	//maxValor
	fprintf(fp, "%d\n", maxValor);
	int l, c;
	for(l=0; l<linhas; l++)
	{	for(c=0; c<colunas; c++)
			fprintf(fp, "%d\n%d\n%d\n", mat[l][c].R, mat[l][c].G, mat[l][c].B);
	}
	fclose(fp);
}
int main(int argc, char * argv[])
{	char opcao[10]="0";
	int linhas=0, colunas=0, maxValor=0;
	PIXEL **mat=NULL;
	int tamanhoBorrao = 8;
	char nomeArquivo[100]="";
	char nomeArquivoLeitura[100]="";
	char nomeArquivoEscrita[100]="";
	while(opcao[0] != '9')
	{	printf("\n\nMini-photoshop\n\n");
		printf("1) Ler imagem\n");	
		printf("2) Gravar imagem\n");	
		printf("3) Aumentar o brilho\n");	
		printf("4) Diminuir o brilho\n");	
		printf("5) Aumentar contraste\n");
		printf("6) Diminuir contraste\n");
		printf("7) Desfocar\n");
		printf("8) Bandeira da França\n");
		printf("9) Sair\n");
		printf("\nEntre a opcao desejada: ");	
		fgets(opcao, 10, stdin);
		switch(opcao[0])
		{	case '1':
				printf("\n\nEntre com o nome da imagem (sem extensao): ");
				fgets(nomeArquivo, 100, stdin);
				nomeArquivo[strlen(nomeArquivo)-1]='\0';
				strcpy (nomeArquivoLeitura, nomeArquivo);
				strcat (nomeArquivoLeitura, ".ppm");
				mat = lerImagem(nomeArquivoLeitura, &linhas, &colunas, &maxValor);
				break;
			case '2':
				strcpy (nomeArquivoEscrita, nomeArquivo);
				strcat (nomeArquivoEscrita, "_editada.ppm");
				printf("\n\nA imagem sera salva como %s\n", nomeArquivoEscrita);
				escreverImagem(nomeArquivoEscrita, mat, linhas, colunas, maxValor);
				break;
			case '3':
				aumentarBrilho(mat, linhas, colunas, maxValor);
				break;
			case '4':
				//mat =  diminuirBrilho(mat, linhas, colunas, maxValor);
				break;
			case '5':
				//mat =  aumentarContraste(mat, linhas, colunas, maxValor);
				break;
			case '6':
				//mat =  diminuirContraste(mat, linhas, colunas, maxValor);
				break;
			case '7':
				//mat =  borrar(mat, linhas, colunas, tamanhoBorrao);		
				break;
			case '8':
				mat =  bandeiraFranca(&linhas, &colunas, &maxValor);
				break;
		}
	}
	return 0;
}
