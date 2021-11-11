// Coronado Obregón Carlos Alejandro - 170038
// Rodriguez Bravo Cesar Eduardo - 170050

// Librerias
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include <time.h>
// Headers
#include "funciones.h"
#include "listaUsuarios_admi.h"
#include "menu_principal.h"
#include "arbolUsuarios.h"
#include "portada.h"
#include "libro.h"
#include "lapiz.h"
// Constantes
#define pr printf
#define sc scanf
#define sys system

// Prototipos de funciones
bool AjustarVentana(int Ancho, int Alto);
void setcolor(int value);
void gotoxy(int x,int y);
void carga(char pal[15]);

/*	Indicaciones para desarrollar el proyecto: Se hará uso de la misma lista y nodoU 
	para los docentes y administradores, sin embargo se les daran las opciones correspondientes
	quiere decir que ciertas funciones podrian cambiar para cada uno de los usuarios	*/
	
// Encontrar y resolver bug que cicla el programa al tratar de ingresar un usuario nuevo al sistema

// Funcion principal
int main(){ 
	int op,op1,op2,val,num;
	FILE *archavl;
	nodo_a *raiz=NULL;
	datosUser info_u; // Nodo para la lista
	datosUser_a info_a; // Nodo para el árbol
	bool bo;
	sys("color f0");
	AjustarVentana(170,58);
	portada();
	do{
		nodoU *cabUser=NULL;
		sys("cls");
		op1=0;
		val=NULL;
		op1=menu_principal(); 
		sys("cls");
		switch(op1){
			
			case 1: // Administradores
				// recuperar datos del archivo de usuarios
				val=recupera_usuarios_verif(&cabUser,"admin.txt");
				if(val==1){
					nodoU *cabUser=NULL;
					recupera_arch_lista(&cabUser,"docentes.txt"); // <-- Recupera los datos del documento docentes.txt
					inicializa_dato_a(&raiz,info_a,&bo); // <-- Inicializa los datos para los alumnos (arbol)
					do{ // Genera el menu para administradores
						op2=0;
						sys("cls");
						op2=menu_admi();
						sys("cls");
						switch(op2){
							case 1: // Menu usuarios/docentes
								do{ // Se genera el menu
									sys("cls");
									op=0;
									op=menu_usuario(); 
									sys("cls");
									switch(op){
										case 1: // Altas
											pedir_usuario(&cabUser,info_u);
										break;
										case 2: // Bajas
											elimina_usuario(&cabUser);
										break;
										case 3: 
											recorre_usuario(cabUser);
										break;;
										case 4: 
											vaciar_usuarios(cabUser,"docentes.txt");
											carga("Menu admin");
										break;	
									}
									if(op!=4){
										pr("\n\n\t");
										sys("pause");
									}
								}while(op!=4);
							break;
							
							case 2: // Menu alumnos
								do{
									// Alumnos en el arbol :v
									op=0;
									sys("cls");
									op=menu_alumn();
									sys("cls");
									switch(op){
										case 1: // Altas
											ingresa_dat(&raiz,info_a,&bo);
										break; 
										
										case 2: // Bajas
											do{
												num=NULL;
												pr("\n\tIngresa la matricula del estudiante a dar de baja (0 para cancelar):\n\n\t>> ");
												sc("%d",&num);
												if(num == 0){
													num=100000;
												}else if(num >= 100000 || num <= 999999){
													elimina(&raiz,&bo,num);
												}
											}while(num <= 99999 || num > 999999);
										break;
										
										case 3: // Consultas
											// Hacer un recorrido del arbol
											posorden(raiz);
										break;
										
										case 4: 
											pr("\n\tIngresa la matricula que deseas buscar: ");
											sc("%d",&num);
											busqueda(raiz,info_a,num);
											// Recorre_usuario(cabUser);
										break;
										
										case 5: // Salir
											// Vaciar los datos
											archavl=fopen("alumnos01.txt","w");
											enorden(raiz,archavl);
											fclose(archavl);
											carga("Menu admi");
										break;
									}
									if(op!=5){
										pr("\n\n\t");
										sys("pause");
									}
								}while(op!=5);
							break;
							
							case 3: // Menu principal
								carga("Menu inicial");
							break;
						}
						if(op2!=3){
							pr("\n\n\t");
							sys("pause");
						}
					}while(op2!=3);
				}
			break;
			
			case 2: // Docentes
				val=recupera_usuarios_verif(&cabUser,"docentes.txt"); // Cambiar los nodos, actualmente se guarda todo en una misma lista
				if(val==1){
					inicializa_dato_a(&raiz,info_a,&bo);
					do{
						op2=0;
						sys("cls");
						op2=menu_docente();
						sys("cls");
						switch(op2){
							case 1: // Registro
								recorre_enorden(raiz);
							break;
							case 2: // Consultas
								posorden(raiz);
							break;
							case 3: // Regresar al menu principal
								archavl=fopen("alumnos01.txt","w");
								enorden(raiz,archavl); // aun no vacia bien los datos
								fclose(archavl);
								carga("Menu inicial");
							break;
						}
						if(op2!=3){
							pr("\n\n\t");
							sys("pause");
						}
					}while(op2!=3);
				}
			break;
			
			case 3:
				carga("Finalizando");
				pr("\a");
				Sleep(800);
			break;
		}
		if(op1!=3){
			pr("\n\n\t");
			sys("pause");
		}
	}while(op1!=3);
	return 0;
}

// Función para dar una posición en consola
void gotoxy(int x,int y){   
	HANDLE hcon;  
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
	COORD dwPos;  
	dwPos.X = x;  
	dwPos.Y= y;  
	SetConsoleCursorPosition(hcon,dwPos);  
}

// Cambia el color de un caracter o fondo
void setcolor(int value){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  value);
}

// Animacion de carga
void carga(char pal[15]){
	int i,j;
	for(i=0;i<2;i++){
		sys("cls");
		pr("\n\t%s",pal);
		for(j=0;j<3;j++){
			Sleep(100);
			pr(". ");
			Sleep(30);
		}
	}
}

// Funcion para definir el tamaño de consola
bool AjustarVentana(int Ancho, int Alto){ 
	_COORD Coordenada;
	Coordenada.X = Ancho;
	Coordenada.Y = Alto;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Right = Ancho - 1;
	Rect.Bottom = Alto - 1;

	// Obtener el handle de la consola
	HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);

	// Ajustar el buffer al nuevo tamaño
	SetConsoleScreenBufferSize(hConsola, Coordenada);

	// Cambiar tamaño de consola a lo especificado en el buffer
	SetConsoleWindowInfo(hConsola, TRUE, &Rect);
	return TRUE;
}
