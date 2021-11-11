#define pr printf
#define sc scanf
#define sys system
#define FILAS_La 31
#define COL_La 31

void mostrar_imagen_2(int **fig);
void lapiz();

void lapiz(){
	FILE *archivo;
	int i,j;
	int **fig=NULL;
	fig=(int**)malloc(FILAS_La*sizeof(int*));
	for(i=0;i<FILAS_La;i++){
		fig[i]=(int*)malloc(COL_La*sizeof(int));
	}
	archivo = fopen("lapiz.txt", "r");
	if (archivo==NULL)
		printf("FILE ERROR");
	else{
		for (i=0; i<FILAS_La;i++){
			for (j=0;j<COL_La; j++){
				fscanf(archivo, "%d	",&fig[i][j]);
			}
		}
		mostrar_imagen_2(fig);
	}
	fclose(archivo);
}

// Imprime las imagenes
void mostrar_imagen_2(int **fig){
	int i,j;
	for (i=0;i<FILAS_La; i++){
		gotoxy(30,i);
		for (j=0;j<COL_La; j++){
			setcolor(fig[i][j]);
			pr("%c",219);
		}
		pr("\n");
	}
}

