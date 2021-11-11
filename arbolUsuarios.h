// Constantes
#define pr printf
#define sc scanf
#define sys system

typedef struct{
	int matricula,asist;
	char degree[6],ap_p[20],ap_m[20],nom[25];
}datosUser_a;

typedef struct nodo_a{ // Estructura para el nodo_a
	int fe; // factor de equilibrio
	datosUser_a info;
	nodo_a *izq;
	nodo_a *der;	
}nodo_a;

// Prototipos de funciones
nodo_a* crea_nodo(datosUser_a info);
void inicializa_dato_a(nodo_a **raiz,datosUser_a info,bool *bo);
void inserta_dato(nodo_a **raiz,datosUser_a info,bool *bo);
void enorden(nodo_a *raiz,FILE *archavl);
void preorden(nodo_a *raiz);
void posorden(nodo_a *raiz);
void busqueda(nodo_a *raiz,datosUser_a info,int num);
void reestruc_izq(nodo_a **raiz,bool *bo);
void reestruc_der(nodo_a **raiz,bool *bo);
void ingresa_dat(nodo_a **raiz,datosUser_a info,bool *bo);
void elimina(nodo_a **raiz,bool *b,int dato);
void recorre_enorden(nodo_a *raiz);
void gotoxy(int x,int y);

nodo_a* crea_nodo(datosUser_a info){
	nodo_a *aux;
	aux=(nodo_a*)malloc(sizeof(nodo_a));
	aux->info=info;
	aux->der=NULL;
	aux->izq=NULL;	
	aux->fe=0; //pone en 0 el factor de equilibro
	return aux;
}

// Inicializa los datos
void inicializa_dato_a(nodo_a **raiz,datosUser_a info,bool *bo){
	FILE *arch;
	arch=fopen("alumnos01.txt","r");
	if(arch){
		while(!feof(arch)){
			fscanf(arch,"%d\t",&info.matricula);
			fscanf(arch,"%[^\t]\t",info.degree);
			fscanf(arch,"%[^\t]\t",info.ap_p);
			fscanf(arch,"%[^\t]\t",info.ap_m);
			fscanf(arch,"%[^\t]\t",info.nom);
			fscanf(arch,"%d\n",&info.asist);
			inserta_dato(raiz,info,bo);
		}
	}
	fclose(arch);
}

// Ingresa datos
void ingresa_dat(nodo_a **raiz,datosUser_a info,bool *bo){
	pr("\n\tIngreso de datos:\n");
	fflush(stdin);
	do{
		pr("\n\tMatricula: ");
		sc("%d",&info.matricula);
		if(info.matricula <= 99999 || info.matricula > 999999){
			pr("\n\tMatricula invalida\n");
		}
	}while(info.matricula <= 99999 || info.matricula > 999999);
	fflush(stdin);
	pr("\n\tApellido paterno: ");
	sc("%[^\n]",info.ap_p);
	fflush(stdin);
	pr("\n\tApellido materno: ");
	sc("%[\n]",info.ap_m);
	fflush(stdin);
	pr("\n\n\tNombre: ");
	sc("%[^\n]",info.nom);
	fflush(stdin);
	pr("\n\tCarrera (Siglas): ");
	sc("%[^\n]",info.degree);
	fflush(stdin);
	info.asist=0;
	inserta_dato(raiz,info,bo);
}

// Inserta en el arbol
void inserta_dato(nodo_a **raiz,datosUser_a info,bool *bo){
	nodo_a*otro,*nodo1=NULL,*nodo2=NULL;
	if(*raiz!=NULL){
		if(info.matricula < (*raiz)->info.matricula){
			inserta_dato(&(*raiz)->izq,info,bo);
			if(*bo==1){
				if((*raiz)->fe==1){
					(*raiz)->fe=0;
					*bo=false;
				}else if((*raiz)->fe==0){
					(*raiz)->fe=-1;
				}else if((*raiz)->fe==-1){
					nodo1=(*raiz)->izq;
				
					if(nodo1->fe<=0){ //rotacion II
						(*raiz)->izq=nodo1->der;
						nodo1->der=(*raiz);
						(*raiz)->fe=0;
						(*raiz)=nodo1;
					}else{
						nodo2=nodo1->der;
						(*raiz)->izq=nodo2->der; //Rotacion ID
						nodo2->der=(*raiz);
						nodo1->der=nodo2->izq;
						nodo2->izq=nodo1;
						if(nodo2->fe==-1){
							(*raiz)->fe=1;
						}else{
							(*raiz)->fe=0;
						}
						if(nodo2->fe==1){
							nodo1->fe=-1;
						}else{
							nodo1->fe=0;
						}
						(*raiz)=nodo2;
					}
					(*raiz)->fe=0;
					*bo=false;
				}
			}
		}else{
			if(info.matricula>(*raiz)->info.matricula){
				inserta_dato(&(*raiz)->der,info,bo);
				if(*bo){
					if((*raiz)->fe==-1){
						(*raiz)->fe=0;
						*bo=false;
					}else
					if((*raiz)->fe==0) (*raiz)->fe=1;
					else if((*raiz)->fe==1){
						nodo1=(*raiz)->der;
						if((nodo1->fe) >= 0){ //Rotacion DD
							(*raiz)->der=nodo1->izq;
							nodo1->izq=(*raiz);
							(*raiz)->fe=0;
							(*raiz)=nodo1;
						}else{
							nodo2=nodo1->izq; //Rotacion DI
							(*raiz)->der=nodo2->izq;
							nodo2->izq=(*raiz);
							nodo1->izq=nodo2->der;
							nodo2->der=nodo1;
							if(nodo2->fe==1){
								(*raiz)->fe=-1;
							}else{
								(*raiz)->fe=0;
							}
							if(nodo2->fe==-1){
								nodo1->fe=1;
							}else{
								nodo1->fe=0;
							}
							(*raiz)=nodo2;
						}
						(*raiz)->fe=0;
						*bo=false;
					}				
				}
			}else{
				printf("\n\tDato repetido\n");
				Sleep(700);
			}				
		}
	}else{
		*raiz=crea_nodo(info);
		*bo=true;
	}
}

// Genera la busqueda del nodo necesario
void busqueda(nodo_a *raiz,datosUser_a info,int num){
	if(raiz!=NULL)
	{
		if(num < raiz->info.matricula)
			busqueda(raiz->izq,info,num);	
		else{
			if(num > raiz->info.matricula){
				busqueda(raiz->der,info,num);
			}
			else{
				printf("\n\tMatricula: %d\n\tNombre: %s %s %s\n\tCarrera: %s\n\tAsistencias: %d",
				raiz->info.matricula,raiz->info.nom,raiz->info.ap_p,raiz->info.ap_m,raiz->info.degree,raiz->info.asist);
			}
		}
	}else{
		printf("\n\tEl dato no se encuentra en el arbol\n");
	}
}

// Recorre y muestra alumnos para tomar lista
void recorre_enorden(nodo_a *raiz){
	int aux;
	if(raiz!=NULL){
		recorre_enorden(raiz->izq);
		system("cls");
		pr("\n\tPara tomar asistencia 1 = asistencia, 0 = falta");
		pr("\n\n\t%d",raiz->info.matricula);
		pr(" %s",raiz->info.degree);
		pr(" %s",raiz->info.ap_p);
		pr(" %s",raiz->info.ap_m);
		pr(" %s",raiz->info.nom);
		pr(" %d",raiz->info.asist);
		do{
			pr("\n\t>> ");
			sc("%d",&aux);
			switch(aux){
				case 0:
					aux = 1;
				break;
				case 1:
					raiz->info.asist+=1;
				break;
				default:
					pr("\n\tDato invalido");
			}
		}while(aux != 1);
		recorre_enorden(raiz->der);
	}
}

// IRD guarda en archivo
void enorden(nodo_a *raiz, FILE *archavl){
	if(raiz!=NULL){
		enorden(raiz->izq,archavl);
		fprintf(archavl,"%d\t",raiz->info.matricula);
		fprintf(archavl,"%s\t",raiz->info.degree);
		fprintf(archavl,"%s\t",raiz->info.ap_p);
		fprintf(archavl,"%s\t",raiz->info.ap_m);
		fprintf(archavl,"%s\t",raiz->info.nom);
		fprintf(archavl,"%d\n",raiz->info.asist);
		enorden(raiz->der,archavl);
	}
}

// RID
void preorden(nodo_a *raiz){
	if(raiz!=NULL){
		//...
		preorden(raiz->izq);
		preorden(raiz->der);
	}
}

// Modificado para recorrer en orden 
void posorden(nodo_a *raiz){ // IRD -> En orden 
	if(raiz!=NULL){
		posorden(raiz->izq);
		pr("\n\tMatricula: %d",raiz->info.matricula);
		pr("\n\tCarrera: %s",raiz->info.degree);
		pr("\n\tNombre: %s",raiz->info.nom);
		pr("\n\tApellido p: %s",raiz->info.ap_p);
		pr("\n\tApellido m: %s",raiz->info.ap_m);
		pr("\n\tAsistencias registradas: %d\n",raiz->info.asist);
		posorden(raiz->der);
	}
}

//restructuracion izquirda
void reestruc_izq(nodo_a **raiz,bool *bo){
	if((*raiz)!=NULL){
	nodo_a *nodo1=NULL;	
   	nodo_a *nodo2=NULL;
	if(*bo==true){
	
			if((*raiz)->fe==-1){
				(*raiz)->fe=0;
			}else
			if((*raiz)->fe==0){
				(*raiz)->fe=1;
				*bo=false;
			}else
			if((*raiz)->fe==1){ //RDD
				nodo1=(*raiz)->der;
				if(nodo1->fe>=0){
					(*raiz)->der=nodo1->izq;
					nodo1->izq=(*raiz);
				
						if(nodo1->fe==0){
							(*raiz)->fe=1;
							nodo1->fe=-1;
							*bo=false; //0
						}else
						if(nodo1->fe==1){
							(*raiz)->fe=0;
							nodo1->fe=0;
						}
					
					(*raiz)=nodo1;//ACTUALIZO RAIZ
					//termina rotacion
				}else{ //RDI
					nodo2=nodo1->izq;
					(*raiz)->der=nodo2->izq;
					nodo2->izq=(*raiz);
					nodo1->izq=nodo2->der;
					nodo2->der=nodo1;
					if(nodo2->fe==1){
						(*raiz)->fe=-1;
					}else{
						(*raiz)->fe=0;
					}
					if(nodo2->fe==-1){ //factores de quilibrio
						nodo1->fe=1;
					}else{
						nodo1->fe=0;
					}
					(*raiz)=nodo2;//actualiza raiz
					nodo2->fe=0;
				}
			}
			
	}
}
}

//restructuracion derecha
void reestruc_der(nodo_a **raiz,bool *bo){
	if((*raiz)!=NULL){
	nodo_a *nodo1=NULL;	
   	nodo_a *nodo2=NULL;
	if(*bo==true){
			if((*raiz)->fe==1){
				(*raiz)->fe=0;
			}else
			if((*raiz)->fe==0){
				(*raiz)->fe=-1;
				*bo=false;
			}else
			if((*raiz)->fe==-1){
				nodo1=(*raiz)->izq;
				if(nodo1->fe<=0){
					(*raiz)->izq=nodo1->der;
					nodo1->der=(*raiz);
					
						if(nodo1->fe==0){
							(*raiz)->fe=-1;
							nodo1->fe=1;
							*bo=false;
						}else
						if(nodo1->fe==-1){
							(*raiz)->fe=0;
							nodo1->fe=0;
						}
					
					(*raiz)=nodo1;
				}else{
					nodo2=nodo1->der;
					(*raiz)->izq=nodo2->der;
					nodo2->der=(*raiz);
					nodo1->der=nodo2->izq;
					nodo2->izq=nodo1;
					if(nodo2->fe==-1){
						(*raiz)->fe=1;
					}else{
						(*raiz)->fe=0;
					}
					if(nodo2->fe==1){
						nodo1->fe=-1;
					}else{
						nodo1->fe=0;
					}
					(*raiz)=nodo2;//actualiza raiz
					nodo2->fe=0;
				}
			}
			
		
	}
	}
}

//eliminar
void elimina(nodo_a **raiz,bool *b,int dato)
{
	nodo_a *otro, *aux, *aux1;
	int bo=0; // encontro al mayor de los menores
	
	if(*raiz!=NULL)
	{
		if(dato<(*raiz)->info.matricula)
		{
				elimina(&(*raiz)->izq,&*b,dato);
				reestruc_izq(&(*raiz),&*b);		
		}
		else if(dato>(*raiz)->info.matricula){
				elimina(&(*raiz)->der,&*b,dato);
				reestruc_der(&(*raiz),&*b);
			}
			else // es el dato
			{ 
				otro=(*raiz);
				*b=1;
				// tiene hijos?	
				if(otro->der==NULL) (*raiz)=otro->izq;
				else if(otro->izq==NULL) (*raiz)=otro->der;
					else
					{// mayor de los menores
						aux=(*raiz)->izq;
						bo=0;
						while(aux->der!=NULL)
						{
							aux1=aux;
							aux=aux->der;
							bo=1;
						}
						(*raiz)->info.matricula=aux->info.matricula;
						otro=aux;
						if(bo==1)	aux1->der=aux->izq;
						else(*raiz)->izq=aux->izq;								
						if((*raiz)->izq!=NULL) reestruc_der(&(*raiz)->izq,&*b);
							else reestruc_izq(&(*raiz),&*b);
					}
				free(otro);		
			}
	}
	else{
		printf("\n\tNo existe la matricula\n");
	}
/*	nodo *aux=NULL;	
   	nodo *aux1=NULL;	
   	nodo *otro=NULL;
   	bool BOOL;
	if((*raiz)!=NULL){
		if(cve< (*raiz)->info.matricula){
			eliminacion(&(*raiz)->izq,bo,cve);
			reestruc_izq(&(*raiz),bo);
		}else{
			if(cve>(*raiz)->info.matricula){
				eliminacion(&(*raiz)->izq,bo,cve);
				reestruc_der(&(*raiz),bo);
			}else{
				otro=(*raiz);
				*bo=true;
				if(otro->der==NULL){
					(*raiz)=otro->izq;
				}else{
					if(otro->izq==NULL){
						(*raiz)=otro->der;
					}else{
						aux=(*raiz)->izq;
						BOOL=false;
						while(aux->der!=NULL){
							aux1=aux;
							aux=aux1->der;
							BOOL=true;
						}
						(*raiz)->info=aux->info;
						otro=aux;
						if(BOOL==true){
							aux1->der=aux->izq;
						}else{
							(*raiz)->izq=aux->izq;
						}
						if((*raiz)->izq!=NULL)//
						reestruc_der(&(*raiz)->izq,bo);
						else
						reestruc_izq(&(*raiz),bo);
					}
				}
				printf("\nDato eliminado: %d\n",cve);
				free(otro);
			}
		}	
	}else{
			printf("La informacion no se encuentra en el arbol");
	} */

}
