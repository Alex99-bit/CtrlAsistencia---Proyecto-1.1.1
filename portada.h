// Constantes
#define pr printf
#define sc scanf
#define sys system
#define FILAS 22
#define COL 68

// Prototipos de funciones
void setcolor(int value);
void gotoxy(int x,int y);
void carga(char pal[15]);
void mostrar_imagen_1(int **fig);

void portada(){
	FILE *archivo;
	int i,j;
	int **fig=NULL;
	fig=(int**)malloc(FILAS*sizeof(int*));
	for(i=0;i<FILAS;i++){
		fig[i]=(int*)malloc(COL*sizeof(int));
	}
	archivo = fopen("portada.txt", "r");
	if (archivo==NULL)
		printf("FILE ERROR");
	else{
		for (i=0; i<FILAS;i++){
			for (j=0;j<COL; j++){
				fscanf(archivo, "%d	",&fig[i][j]);
			}
		}
		mostrar_imagen_1(fig);
	}
	fclose(archivo);
	setcolor(240);
	Sleep(500);
	pr("\n\t\t\t");
	sys("pause");
}

// Imprime las imagenes
void mostrar_imagen_1(int **fig){
	int i,j;
	for (i=0;i<FILAS; i++){
		gotoxy(10,i);
		for (j=0;j<COL; j++){
			setcolor(fig[i][j]);
			pr("%c",219);
		}
		pr("\n");
		Sleep(100);
	}
}

