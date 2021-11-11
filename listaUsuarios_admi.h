// Constantes
#define pr printf
#define sc scanf
#define sys system

// Estructura de datos "datosUser"
typedef struct{ 
	char nom[20];
	char apellidoP[30];
	char apellidoM[30];
	char userName[15];
	char pass[10];
}datosUser;

// nodo usuario
typedef struct nodoU{ 
	datosUser info;
	// lista doble
	nodoU *sig;
	nodoU *ant; 	
}nodoU;

// Prototipos de funciones
int recupera_usuarios_verif(nodoU **cab, char nom_arch[20]);
int valida(datosUser info,nodoU **cabUser);
void pedir_usuario(nodoU **cab,datosUser *info);
void inserta_inicio(nodoU **cab, datosUser info);
nodoU* inicializa_nodo(datosUser info);
void elimina_usuario(nodoU **cab);
void recupera_usuarios_verif(nodoU *cabUser);
void imprime_dato(datosUser info);
void vaciar_usuarios(nodoU *cabUser,char nom_arch[20]);
void insertar_arch_lista(datosUser info,char nom_arch[20]);
void recupera_arch_lista(nodoU **cab,char nom_arch[20]);

// Funcion para recuperar los datos que sean necesarios en el momento
void recupera_arch_lista(nodoU **cab,char nom_arch[20]){
	FILE *arch;
	datosUser info;
	arch=fopen(nom_arch,"r");
	if(arch){
		while(!feof(arch)){
			fscanf(arch,"%[^\t]\t",info.nom);
			fscanf(arch,"%[^\t]\t",info.apellidoP);
			fscanf(arch,"%[^\t]\t",info.apellidoM);
			fscanf(arch,"%[^\t]\t",info.userName);
			fscanf(arch,"%[^\n]\n",info.pass);
			inserta_inicio(&(*cab),info);	
		}
	}
	fclose(arch);
}

// Funcion que lee y guarda usuarios del archivo para verificar
int recupera_usuarios_verif(nodoU **cab,char nom_arch[20]){
	FILE *arch;
	datosUser info;
	int val=NULL;
	arch=fopen(nom_arch,"r");
	if(arch){
		while(!feof(arch)){
			fscanf(arch,"%[^\t]\t",info.nom);
			fscanf(arch,"%[^\t]\t",info.apellidoP);
			fscanf(arch,"%[^\t]\t",info.apellidoM);
			fscanf(arch,"%[^\t]\t",info.userName);
			fscanf(arch,"%[^\n]\n",info.pass);
			inserta_inicio(&(*cab),info);
		}
	}
	val=valida(info,cab);
	fclose(arch);
	return val;
}

// Ingresa usuarios nuevos
void pedir_usuario(nodoU **cab,datosUser info){
	fflush(stdin);
	pr("\n\tNombre: ");
	sc("%[^\n]",info.nom);
	
	fflush(stdin);
	pr("\n\tApellido P: ");
	sc("%[^\n]",info.apellidoP);
	
	fflush(stdin);
	pr("\n\tApellido M: ");
	sc("%[^\n]",info.apellidoM);
	
	fflush(stdin);
	pr("\n\tUsername: ");
	sc("%[^\n]",info.userName);
	
	fflush(stdin);
	pr("\n\tPassword: ");
	sc("%[^\n]",info.pass);
	
	inserta_inicio(cab,info);
}

// Incerta los usuarios de manera ordenada
void inserta_inicio(nodoU **cab,datosUser info){
	nodoU *nuevo=NULL;
	nuevo=inicializa_nodo(info);
	nuevo->sig=*cab;
	nuevo->ant=*cab;
	*cab=nuevo;
}

// Inicializa nodo usuarios
nodoU* inicializa_nodo(datosUser info){
	nodoU *nuevo;
	nuevo=(nodoU*)malloc(sizeof(nodoU));
	nuevo->info=info;
	nuevo->sig=NULL;
	nuevo->ant=NULL;
	return nuevo;
}

// Elimina usuarios especificos
void elimina_usuario(nodoU **cab){
	int  find=0,cve;
	nodoU *ultimo, *anterior, *aux;
	datosUser info;
	char nom[20];
	if(*cab==NULL){
	     printf("\n\tImposible eliminar, lista vacia");
	}else{           	
		printf("\n\tNombre: ");
		scanf("%s",nom);
		find=0;
	    anterior=*cab;
	    ultimo=*cab;
	    while(ultimo!= NULL && find==0){
            if(strcmp(nom,ultimo->info.nom)==0 && find==0){
				find=1;
			}else{
			    anterior=ultimo;
			    ultimo=ultimo->sig;
			}
		}
		if(find==1){            
	        if(ultimo==anterior) {	        
				*cab= (*cab)->sig;
			}else{
	        	anterior->sig=ultimo->sig;
	        }
		    free(ultimo);
		    printf("\n\t%d Eliminado\n",cve);
		}
	}
}

// Validación para mostrar el menu
int valida(datosUser info,nodoU **cabUser){
	char user_n[15],pass[10];
	int ban[2]={0},i,num;
		
	// Validación para perfil
	num=5;
	for(i=0;i<5;i++){
		// Se reinician los valores para poder validar las 5 veces
		nodoU *aux=NULL;
		aux=*cabUser; // pasado por valor
		sys("cls");
		strcpy(user_n,"");
		fflush(stdin);
		pr("\n\tNo. Intentos: ");
		setcolor(249);
		pr("%d",num);
		setcolor(240);
		pr("\n\tIngresa tu perfil: ");
		setcolor(244);
		sc("%[^\n]",user_n);
		setcolor(240);
		num--;
		while(aux!=NULL){
			if(strcmp(user_n,aux->info.userName) == 0){
				i=5;
				ban[0]=1;
			}
			aux=aux->sig;  
		}
	}
	
	if(ban[0]==1){
		// Se reinician los valores para poder validar las 5 veces
		num=5;
		for(i=0;i<5;i++){
			nodoU *aux2=NULL;
			aux2=*cabUser; // pasado por valor
			sys("cls");
			fflush(stdin);
			pr("\n\tNo. Intentos: ");
			setcolor(249);
			pr("%d",num);
			setcolor(240);
			pr("\n\tIngrese su password: ");
			setcolor(244);
			sc("%[^\n]",pass);
			setcolor(240);
			num--;
			while(aux2!=NULL){
				if(strcmp(pass,aux2->info.pass) == 0){
					i=5;
					ban[1]=1;
				}
				aux2=aux2->sig;
			}
		}
		if(ban[1]==1){
			return 1;
		}else{
			pr("\n\tPassword denegada");
			return 0;
		}
	}else{
		pr("\n\tUsuario denegado");
	}
}

// Funcion que recorre la lista para mostrar los usuarios
void recorre_usuario(nodoU *cabUser){
	nodoU *aux=NULL;
	aux=cabUser; // pasado por valor
	while(aux!=NULL){
		imprime_dato(aux->info);
		aux=aux->sig;
	}
}

// Funcion que en conjunto con recorre nodo, imprime los datos 
void imprime_dato(datosUser info){
	pr("\n\tNombre: %s %s %s",info.nom,info.apellidoP,info.apellidoM);
	pr("\n\tUsername: %s\n",info.userName);
}

// Vacia los datos en la funcion que inserta los datos al archivo
void vaciar_usuarios(nodoU *cabUser,char nom_arch[20]){
	nodoU *aux=NULL;
	FILE *arch;
	aux=cabUser; // pasado por valor
	arch=fopen(nom_arch,"w");
	while(aux!=NULL){
		fprintf(arch,"%s\t",aux->info.nom);
		fprintf(arch,"%s\t",aux->info.apellidoP);
		fprintf(arch,"%s\t",aux->info.apellidoM);
		fprintf(arch,"%s\t",aux->info.userName);
		fprintf(arch,"%s\n",aux->info.pass);
		aux=aux->sig;
	}
	fclose(arch);
}
