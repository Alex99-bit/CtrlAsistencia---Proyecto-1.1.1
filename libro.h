#define pr printf
#define sc scanf
#define sys system
#define FILAS_Li 18
#define COL_Li 25

void mostrar_imagen_3(int **fig);
void libro(void);

void libro(void){
	FILE *archivo;
	int i,j;
	int **fig=NULL;
	fig=(int**)malloc(FILAS_Li*sizeof(int*));
	for(i=0;i<FILAS_Li;i++){
		fig[i]=(int*)malloc(COL_Li*sizeof(int));
	}
	archivo = fopen("libro.txt", "r");
	if (archivo==NULL)
		printf("FILE ERROR");
	else{
		for (i=0; i<FILAS_Li;i++){
			for (j=0;j<COL_Li; j++){
				fscanf(archivo, "%d	",&fig[i][j]);
			}
		}
		mostrar_imagen_3(fig);
	}
	fclose(archivo);
}

// Imprime las imagenes
void mostrar_imagen_3(int **fig){
	int i,j;
	for (i=0;i<FILAS_Li; i++){
		gotoxy(30,i);
		for (j=0;j<COL_Li; j++){
			setcolor(fig[i][j]);
			pr("%c",219);
		}
		pr("\n");
	}
}

