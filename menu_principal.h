// Constantes
#define pr printf
#define sc scanf
#define sys system

// Prototipos de funciones
int menu_principal();
void gotoxy(int x,int y);
void setcolor(int value);

int menu_principal(){
	int tecla=0,x=18,y=3;
	while(tecla!=13){
		gotoxy(x,y-1);
		pr("    ");
		setcolor(244);
		gotoxy(x,y);
		pr("<<--");
		setcolor(240);
		gotoxy(x,y+1);
		pr("    ");
		
		gotoxy(3,1);
		pr("Menu principal:");
		gotoxy(3,3);
		pr("Administrador");
		gotoxy(3,4);
		pr("Docente");
		gotoxy(3,5);
		pr("Salir");
		
		tecla=getch();
		switch(tecla){
			case 72: // Arriba
				if(y>3){
					y--;
				}else{
					gotoxy(x,3);
					pr("    ");
					y=5;
				}
			break;
			case 80: // Abajo
				if(y<5){
					y++;
				}else{
					gotoxy(x,5);
					pr("    ");
					y=3;
				}
			break;
		}
		
		if(tecla == 13){
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
