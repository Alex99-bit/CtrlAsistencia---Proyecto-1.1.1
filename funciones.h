// Constantes
#define pr printf
#define sys system

// Prototipos de funciones
int menu_usuario();
int menu_admi();
int menu_alumn();
int menu_docente();
void gotoxy(int x,int y);
void setcolor(int value);
void carga(char pal[15]);
void lapiz();
void libro(void);

// Funcion para generar un menu para admi
int menu_admi(){
	int tecla=0,x=23,y=3;
	libro();
	while(tecla!=13){
		gotoxy(x,y-1);
		pr("    ");
		setcolor(241);
		gotoxy(x,y);
		pr("<<--");
		setcolor(240);
		gotoxy(x,y+1);
		pr("    ");
		
		gotoxy(3,1);
		pr("Menu administradores:");
		gotoxy(3,3);
		pr("Modoficar docentes");
		gotoxy(3,4);
		pr("Modificar alumnos");
		gotoxy(3,5);
		pr("Cerrar sesion");
		
		tecla=getch();
		switch(tecla){
			case 72:
				if(y>3){
					y--;
				}else{
					gotoxy(x,3);
					pr("    ");
					y=5;
				}
			break;
			case 80:
				if(y<5){
					y++;
				}else{
					gotoxy(x,5);
					pr("    ");
					y=3;
				}
			break;
		}
		
		if(tecla==13){
			switch(y){
				case 3:
					return 1;
				break;
				case 4:
					return 2;
				break;
				case 5:
					return 3;
				break;
			}
		}
	}
}

// Funcion para generar un menu para docentes
int menu_docente(){
	int tecla=0,x=18,y=3;
	lapiz();
	while(tecla!=13){
		gotoxy(x,y-1);
		pr("   ");
		setcolor(250);
		gotoxy(x,y);
		pr("<<-");
		setcolor(240);
		gotoxy(x,y+1);
		pr("   ");
		
		gotoxy(3,1);
		pr("Menu docentes:");
		gotoxy(3,3);
		pr("Registro");
		gotoxy(3,4);
		pr("Consultas");
		gotoxy(3,5);
		pr("Cerrar sesion");
		
		tecla=getch();
		switch(tecla){
			case 72:
				if(y>3){
					y--;
				}else{
					gotoxy(x,3);
					pr("   ");
					y=5;
				}
			break;
			case 80:
				if(y<5){
					y++;
				}else{
					gotoxy(x,5);
					pr("   ");
					y=3;
				}
			break;
		}
		
		if(tecla==13){
			switch(y){
				case 3:
					return 1;
				break;
				case 4:
					return 2;
				break;
				case 5:
					return 3;
				break;
			}
		}
	}
}

// Funcion para generar un menu para alumnos
int menu_alumn(){
	int tecla=0,x=14,y=3;
	while(tecla!=13){
		gotoxy(x,y-1);
		pr("   ");
		setcolor(241);
		gotoxy(x,y);
		pr("<<-");
		setcolor(240);
		gotoxy(x,y+1);
		pr("   ");
		
		gotoxy(3,1);
		pr("Menu alumnos -> Admi:");
		gotoxy(3,3);
		pr("Altas");
		gotoxy(3,4);
		pr("Bajas");
		gotoxy(3,5);
		pr("Consultas");
		gotoxy(3,6);
		pr("Busqueda");
		gotoxy(3,7);
		pr("Regresar");
		
		tecla=getch();
		switch(tecla){
			case 72:
				if(y>3){
					y--;
				}else{
					gotoxy(x,3);
					pr("   ");
					y=7;
				}
			break;
			case 80:
				if(y<7){
					y++;
				}else{
					gotoxy(x,7);
					pr("   ");
					y=3;
				}
			break;
		}
		
		if(tecla==13){
			switch(y){
				case 3:
					return 1;
				break;
				case 4:
					return 2;
				break;
				case 5:
					return 3;
				break;
				case 6:
					return 4;
				break;
				case 7:
					return 5;
				break;
			}
		}
	}
}

// Funcion para generar un menu para usuarios/docentes en seccion de admi
int  menu_usuario(){ // Fincion menu, para menu con teclado
	int tecla=0,x=14,y=3;
	while(tecla!=13){
		gotoxy(x,y-1);
		pr("   ");
		setcolor(241);
		gotoxy(x,y);
		pr("<<-");
		setcolor(240);
		gotoxy(x,y+1);
		pr("   ");
		
		// Imprecion del menu
		gotoxy(3,1);
		pr("Menu de usuarios -> Admi:");
		gotoxy(3,3);
		pr("Alta");
		gotoxy(3,4);
		pr("Baja");
		gotoxy(3,5);
		pr("Consultas");
		gotoxy(3,6);
		pr("Regresar");
		
		tecla=getch();
		switch(tecla){
			case 72: // Arriba
				if(y>3){
					y--;
				}else{
					gotoxy(x,3);
					pr("   ");
					y=6;
				}
			break;
			case 80: // Abajo
				if(y<6){
					y++;
				}else{
					gotoxy(x,6);
					pr("   ");
					y=3;
				}
			break;
		}
		
		if(tecla==13){
			switch(y){ // Dependiendo la posición en y, regresa cierto valor para usarse en la funcion principal
				case 3:
					return 1;
				break;
				
				case 4:
					return 2;
				break;
				
				case 5:
					return 3;
				break;
				
				case 6:
					return 4;
				break;
			}
		}
	}
}
