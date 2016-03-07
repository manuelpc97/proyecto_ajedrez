#include <ncurses.h>
#include <cmath>
#include <cstdlib>
#include <string>
#include <fstream>
#include "pieza.h"
#include <sstream>

using std::stringstream;
using std::string;
using std::abs;
using std::ofstream;
using std::ifstream;
	
pieza** crearPiezas();
void llenarTablero(pieza**);
void mostrarTablero(pieza**);
int lettersToNumbers(char);
int verifyNextSquare(int, int, pieza**,int);
bool verifyCurrentSquare(int, int, int, pieza**);
int conocerTipo(int,int,pieza**);
void destruirPiezas(pieza**);
bool movimientoPeon(pieza**, int, int, int, int, int,int&,int);
bool movimientoTorre(pieza**, int, int, int, int);
bool movimientoAlfil(pieza**, int, int, int, int);
bool movimientoCaballo(int, int, int, int);
bool movimientoDama(pieza**, int, int, int, int);
bool movimientoRey(pieza**,int, int, int, int, int);
void mover(int, int, int, int, int,int, pieza**);
void cambiarCasilla(pieza**, int, int, int, bool);
void comer(pieza**, int, int, int, int, int, int, int);
bool recorridoTorre(pieza**, int,int,int,int);
bool recorridoAlfil(pieza**, int, int, int, int);
int charToInt(char);
void findKing(pieza**, int, int*);
bool validacionPeon(pieza**, int, int, int);
void saveGame(string);
char* loadGame();
string piezaToChar(pieza**);
void charToPieza(char*, pieza**);
bool detectarIntercepcion(pieza**, int, int, int);
bool bloqueo(pieza**, int, int, int, int);
bool intercepcion(pieza**, int, int, int);
bool comerAmenaza(pieza**, int, int, int);
bool evaluarHacke(pieza**, int , int , int);
bool hackeMate(pieza**, int, int);

int main(int argc, char*argv[]){
 	bool continuar = true;
	pieza** piezas = crearPiezas();
	int coordenadas[4];
	bool jugar = true;
	char jugada[5];
	bool verificarMovimiento = false;
	int tipoPiezaContraria=0;
	int tipoPieza=0;
	int verificarCuadro =3;
	bool movimientoValido = false;
	int turno = 1;
	int tipoPiezaEnemiga=0;
	int* amenaza = new int[2];
    	int* king = new int[2];
    	int contadorJaque = 0;
    	char opcion[2];	
    	char decision[2];
    	int x, y;
    	char* word = new char[65];
    	string letras;
    


    	initscr();
    	start_color();
    		while(continuar){
        		while(opcion[0]!=49 && opcion[0]!=50 && opcion[0]!=51){
            		init_pair(2,COLOR_GREEN,COLOR_BLACK);
            		attron(COLOR_PAIR(2));
            		clear();
           		getmaxyx(stdscr,x,y);
           		move((x/2)-2,(y/2)-36);
            		printw("-------------------BIENVENIDO A SU JUEGO DE AJEDREZ-------------------------");
            		move((x/2)-1,(y/2)-11);
            		printw("1. Jugar nueva partida");
            		move((x/2),(y/2)-13);
            		printw("2. Cargar partida anterior");
            		move((x/2)+1,(y/2)-4);
            		printw("3. Salir");
            		move((x/2)+2,(y/2)-10);
            		printw("Ingrese una opcion: ");
            		getstr(opcion);
            		attroff(COLOR_PAIR(2));
        	}
        

        	if(opcion[0] == 49 || opcion[0] == 50){
            		if(opcion[0] == 49){
                		llenarTablero(piezas);
            		}else if(opcion[0] == 50){
                		word = loadGame();
                		charToPieza(word,piezas);
            		}

            		while(jugar){
				if(turno==1){
					contadorJaque = 0;
            				mostrarTablero(piezas);
            				printw("-----------------Jugador 1------------------\n");
            				printw("Elija una opcion: \n");
            				printw("1. Seguir\n");
            				printw("2. Guardar y salir\n");
            				printw("3. Solo salir\n");
            				getstr(decision);

            				if(decision[0] == 50){
                				letras = piezaToChar(piezas);
                				saveGame(letras);
                				clear();
                				endwin();
                				exit(1);
            				}else if(decision[0] == 51){
                				jugar = false;
                				endwin();
                				exit(1);
            				}else if(decision[0] == 49){
            					contadorJaque = 0;
            					mostrarTablero(piezas);
            					printw("-----------------Jugador 1------------------\n");
            					findKing(piezas, turno,king);
            
            					if(evaluarHacke(piezas,king[0], king[1],turno)){
                					if(hackeMate(piezas,king[0], king[1]) &&
					 			detectarIntercepcion(piezas, king[0], king[1], turno) == false){
                    						printw("HaqueMate-------------->Jugador1\n");
                    						printw("*********************HA GANADO EL JUGADOR 2*************************");
                    						getch();
                    						endwin();
                					}else{
                    						printw("Jugador 1, usted esta en jaque\n");
                    						contadorJaque++;
                					}
            					}		
	
            					while(verificarMovimiento == false){
                					while(movimientoValido == false){
                    						while(verificarCuadro == 3){
                        						printw("Ingrese la jugada segun el tablero: \n");
                        						getstr(jugada); 
                        						coordenadas[0] = charToInt(jugada[1]);
                        						coordenadas[1] = lettersToNumbers(jugada[0]);    
                        						coordenadas[2] = charToInt(jugada[3]);
                        						coordenadas[3] = lettersToNumbers(jugada[2]);
                        						verificarCuadro = verifyNextSquare(coordenadas[2],
                        						coordenadas[3], piezas, turno);

                        						if(verificarCuadro==3){
                            						   printw("En esta casilla hay una pieza propia,ingrese de nuevo\n");
                        						}                       
                    						}	
                   
						 		movimientoValido = verifyCurrentSquare(coordenadas[0],
						 		coordenadas[1],turno, piezas);

                    						if(movimientoValido==false){
                        					    printw("En esta casilla no existe una pieza propia ingrese de nuevo\n");
                        					    verificarCuadro=3;
                 						}
                					}	
                
                					tipoPiezaContraria = verifyNextSquare(coordenadas[2],coordenadas[3], piezas,turno);
                					tipoPieza = conocerTipo(coordenadas[0], coordenadas[1], piezas);
                					tipoPiezaEnemiga = conocerTipo(coordenadas[2], coordenadas[3], piezas);
                			
							if(tipoPieza==1){
                    						verificarMovimiento = movimientoPeon(piezas, coordenadas[0], 
                    						coordenadas[1], coordenadas[2], coordenadas[3], turno, 
								tipoPieza,tipoPiezaEnemiga);
                    					if(verificarMovimiento==false){
                        					printw("Movimiento de peon invalido, ingrese de nuevo\n");
                        					movimientoValido = false;
                        					verificarCuadro = 3;
                    					}
                				}else if(tipoPieza==2){
                    					verificarMovimiento = movimientoTorre(piezas, coordenadas[0],
                                        		coordenadas[1], coordenadas[2], coordenadas[3]);
                                        		if(verificarMovimiento==false){
                                                		printw("Movimiento de torre invalido, ingrese de nuevo\n");
                                                		movimientoValido = false;
                                                		verificarCuadro = 3;
                    					}
                				}else if(tipoPieza==3){
                    					verificarMovimiento = movimientoAlfil(piezas,coordenadas[0],
                                        		coordenadas[1], coordenadas[2], coordenadas[3]);
                                        		if(verificarMovimiento==false){
                                                		printw("Movimiento de alfil invalido, ingrese de nuevo\n"); 
                                                		movimientoValido = false;
                                                		verificarCuadro = 3;
                    					}
                				}else if(tipoPieza==4){
                    					verificarMovimiento = movimientoCaballo(coordenadas[0],
                                        		coordenadas[1], coordenadas[2], coordenadas[3]);
                                        		if(verificarMovimiento==false){
                                                		printw("Movimiento de caballo invalido, ingrese de nuevo\n");
                                                		movimientoValido = false;
                                                		verificarCuadro = 3;
                    					}
                				}else if(tipoPieza==5){
                    					verificarMovimiento = movimientoDama(piezas,coordenadas[0],
                                        		coordenadas[1], coordenadas[2], coordenadas[3]);
                                        		if(verificarMovimiento==false){
                                                		printw("Movimiento de dama invalido, ingrese de nuevo\n");
                                                		movimientoValido = false;
                                                		verificarCuadro = 3;
                    					}
                				}else if(tipoPieza==6){
                    					verificarMovimiento = movimientoRey(piezas,coordenadas[0],
                                        		coordenadas[1], coordenadas[2], coordenadas[3], turno);
                                        		if(verificarMovimiento==false){
                                                		printw("Movimiento de rey invalido, ingrese de nuevo\n");
                                                		movimientoValido = false;
                                                		verificarCuadro = 3;
                    					}
                				}			 
            				}

            				if(tipoPiezaContraria==1){
                				mover(coordenadas[0], coordenadas[1], coordenadas[2], coordenadas[3],tipoPieza, turno, piezas);
            				}else if(tipoPiezaContraria == 2){
                    				comer(piezas, coordenadas[0], coordenadas[1], coordenadas[2], coordenadas[3], 
                        			turno, tipoPieza, tipoPiezaEnemiga);
            				}
            				findKing(piezas, turno,king);

            				if(evaluarHacke(piezas, king[0], king[1], turno)){
                				contadorJaque++;
            				}

            				if(contadorJaque == 2){
                				printw("JAQUE MATE------------>Jugador1\n");
                				getch();
                				jugar = false;
            				}
            				turno=2;
            				verificarMovimiento=false;
            				verificarCuadro=3;
            				movimientoValido=false;
        			}
        		}else if(turno=2){
            			contadorJaque = 0;
            			mostrarTablero(piezas);
            			printw("-----------------JUgador 2------------------\n");
            			printw("Elija una opcion: \n");
            			printw("1. Seguir\n");
            			printw("2. Guardar y salir\n");
            			printw("3. Solo salir\n");
            			getstr(decision);

            			if(decision[0] == 50){
               				letras = piezaToChar(piezas);
                			saveGame(letras);
                			clear();
                			endwin();
                			exit(0);
            			}else if(decision[0] == 51){
                			jugar = false;
               				endwin();
            			}else if(decision[0] == 49){
                 			contadorJaque = 0;
            				mostrarTablero(piezas);
            				printw("-----------------JUgador 2------------------\n");
            				findKing(piezas, turno,king);
            				if(evaluarHacke(piezas, king[0], king[1], turno)){
                				if(hackeMate(piezas,king[0], king[1]) &&
				 			detectarIntercepcion(piezas, king[0], king[1], turno) == false){
                    					printw("HaqueMate-------------->Jugador2\n");
                    					printw("******************HA GANADO EL JUGADOR 1***************************");
                    					getch();
                    					endwin();
                				}else{
                    					printw("Jugador 2, usted esta en jaque\n");
                    					contadorJaque++;
                				}
            				}		
            				while(verificarMovimiento==false){
                                		while(movimientoValido==false){
                                        		while(verificarCuadro==3){
                                                		printw("Ingrese la jugada segun el tablero: \n");
                                                		getstr(jugada);
                                               
                                                		coordenadas[0] = charToInt(jugada[1]);
                                                		coordenadas[1] = lettersToNumbers(jugada[0]);    
                                                		coordenadas[2] = charToInt(jugada[3]);
                                                		coordenadas[3] = lettersToNumbers(jugada[2]);
                                                		verificarCuadro = verifyNextSquare(coordenadas[2],
                                                		coordenadas[3], piezas, turno);

                                                		if(verificarCuadro==3){
                                                        		printw("En esta casilla hay una pieza propia, ingrese de nuevo\n");
                                                        
                                                		}
                                        		}
                                        		movimientoValido = verifyCurrentSquare(coordenadas[0],
                                        		coordenadas[1],turno, piezas);

                                        		if(movimientoValido==false){
                                                		printw("En esta casilla no existe una pieza propia ingrese de nuevo\n");        
                                                		verificarCuadro=3;
                                        		}
                                		}
                                		tipoPiezaContraria = verifyNextSquare(coordenadas[2],coordenadas[3], piezas,turno);
                                		tipoPieza = conocerTipo(coordenadas[0], coordenadas[1], piezas);
                                		tipoPiezaEnemiga = conocerTipo(coordenadas[2], coordenadas[3], piezas);
                                		if(tipoPieza==1){
                                        		verificarMovimiento = movimientoPeon(piezas, coordenadas[0],
                                        		coordenadas[1], coordenadas[2], coordenadas[3], turno,tipoPieza, tipoPiezaEnemiga);
                                        		if(verificarMovimiento==false){
                                                	printw("Movimiento de peon invalido, ingrese de nuevo\n");               
                                                	movimientoValido = false;
                                                	verificarCuadro = 3;
                                        		}
                                		}else if(tipoPieza==2){
                                        		verificarMovimiento = movimientoTorre(piezas,coordenadas[0],
                                        		coordenadas[1], coordenadas[2], coordenadas[3]);
                                        		if(verificarMovimiento==false){
                                                		printw("Movimiento de torre invalido, ingrese de nuevo\n");
                                                
                                                		movimientoValido = false;
                                                		verificarCuadro = 3;
                                        		}
                                		}else if(tipoPieza==3){
                                        		verificarMovimiento = movimientoAlfil(piezas,coordenadas[0],
                                        		coordenadas[1], coordenadas[2], coordenadas[3]);
                                        		if(verificarMovimiento==false){
                                                		printw("Movimiento de alfil invalido, ingrese de nuevo\n");
                                                
                                                		movimientoValido = false;
                                                		verificarCuadro = 3;
                                        		}
                                		}else if(tipoPieza==4){
                                        		verificarMovimiento = movimientoCaballo(coordenadas[0],
                                        		coordenadas[1], coordenadas[2], coordenadas[3]);
                                        		if(verificarMovimiento==false){
                                                		printw("Movimiento de caballo invalido, ingrese de nuevo\n");
                                                
                                                		movimientoValido = false;
                                                		verificarCuadro = 3;
                                        		}
                                		}else if(tipoPieza==5){
                                        		verificarMovimiento = movimientoDama(piezas,coordenadas[0],
                                        		coordenadas[1], coordenadas[2], coordenadas[3]);
                                        		if(verificarMovimiento==false){
                                                		printw("Movimiento de dama invalido, ingrese de nuevo\n");
                                                
                                                		movimientoValido = false;
                                                		verificarCuadro = 3;
                                        		}
                                		}else if(tipoPieza==6){
                                        		verificarMovimiento = movimientoRey(piezas,coordenadas[0],
                                        		coordenadas[1], coordenadas[2], coordenadas[3], turno);
                                        		if(verificarMovimiento==false){
                                                		printw("Movimiento de rey invalido, ingrese de nuevo\n");
                                                		movimientoValido = false;
                                                		verificarCuadro = 3;            
                                         			verificarCuadro = 3;
                                        		}
                                		}
                        		}
                        
                        		if(tipoPiezaContraria==1){
                                		mover(coordenadas[0], coordenadas[1], coordenadas[2], coordenadas[3],tipoPieza, turno, piezas);
                        		}else if(tipoPiezaContraria == 2 ){
                    				comer(piezas, coordenadas[0], coordenadas[1], coordenadas[2], coordenadas[3], 
                        			turno, tipoPieza, tipoPiezaEnemiga);
            				}

            				findKing(piezas, turno,king);
            				if(evaluarHacke(piezas, king[0], king[1], turno)){
                				contadorJaque++;
            				}
            				if(contadorJaque == 2){
                				printw("JAQUE MATE------------>Jugador2\n");
                				getch();
                				jugar = false;
            				}
                        
                			turno=1;
                			verificarMovimiento=false;
                			verificarCuadro=3;
                			movimientoValido=false;
        			}                               
    			}
		}
        }else if(opcion[0] == 51){
            continuar = false;
        }

    }
    endwin();
    delete[] king;
	destruirPiezas(piezas);		
	return 0;
}

pieza** crearPiezas(){
	pieza** piezas = new pieza*[8];
	for(int i = 0; i<8; i++){
		piezas[i] = new pieza[8];
	}

	return piezas;
}

void destruirPiezas(pieza** tablero){
	for(int i = 0; i < 8; i++){
		delete[] tablero[i];
	}
	delete[] tablero;
}

void saveGame(string word){
    ofstream fsalida("game.txt");
    fsalida<<word;
    fsalida.close();
}

char* loadGame(){
    char* h = new char[65];
    ifstream fentrada("game.txt");
    for(int i = 0; i < 64; i++){
        h[i] = fentrada.get();
    }
    fentrada.close();
    return h;
}

string piezaToChar(pieza** tablero){
    stringstream ss;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if(tablero[i][j].vacia){
                ss<<"V";
            }else if(tablero[i][j].blanca && tablero[i][j].isPeon){
                ss<<"P";
            }else if(tablero[i][j].blanca && tablero[i][j].isAlfil){
                ss<<"A";
            }else if(tablero[i][j].blanca && tablero[i][j].isTorre){
                ss<<"T";
            }else if(tablero[i][j].blanca && tablero[i][j].isCaballo){
                ss<<"C";
            }else if(tablero[i][j].blanca && tablero[i][j].isDama){
                ss<<"D";
            }else if(tablero[i][j].blanca && tablero[i][j].isRey){
                ss<<"R";
            }else if(tablero[i][j].blanca == false && tablero[i][j].isPeon){
                ss<<"N";
            }else if(tablero[i][j].blanca==false && tablero[i][j].isAlfil){
                ss<<"L";
            }else if(tablero[i][j].blanca==false && tablero[i][j].isTorre){
                ss<<"E";
            }else if(tablero[i][j].blanca==false && tablero[i][j].isCaballo){
                ss<<"O";
            }else if(tablero[i][j].blanca==false && tablero[i][j].isDama){
                ss<<"Q";
            }else if(tablero[i][j].blanca==false && tablero[i][j].isRey){
                ss<<"K";
            }
        }
    }
    return ss.str();
}

void charToPieza(char* load, pieza** tab){
    int x = 0, y = 0;
    
    for(int i = 0; i < 64; i++){
            if(load[i] == 80){
                tab[x][y] = pieza(true,false,true,false,false,false,false,false);
            }else if(load[i] == 65){
                tab[x][y] = pieza(true,false,false,false,true,false,false,false);
            }else if(load[i] == 84){
                tab[x][y] = pieza(true,false,false,true,false,false,false,false);
            }else if(load[i] == 67){
                tab[x][y] = pieza(true,false,false,false,false,true,false,false);
            }else if(load[i] == 68){
                tab[x][y] = pieza(true,false,false,false,false,false,true,false);
            }else if(load[i] == 82){
                tab[x][y] = pieza(true,false,false,false,false,false,false,true);
            }else if(load[i] == 78){
                tab[x][y] = pieza(false,false,true,false,false,false,false,false);
            }else if(load[i] == 76){
                tab[x][y] = pieza(false,false,false,false,true,false,false,false);
            }else if(load[i] == 69){
                tab[x][y] = pieza(false,false,false,true,false,false,false,false);
            }else if(load[i] == 79){
                tab[x][y] = pieza(false,false,false,false,false,true,false,false);
            }else if(load[i] == 81){
                tab[x][y] = pieza(false,false,false,false,false,false,true,false);
            }else if(load[i] == 75){
                tab[x][y] = pieza(false,false,false,false,false,false,false,true);
            }else if(load[i] == 86){
                tab[x][y] = pieza(false,true,false,false,false,false,false,false);
            }
            y++; 
            if(y==8){
                y=0;
                x++;
            }
    }
    
}

void llenarTablero(pieza** piezas){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j <8; j++){
			if(i==1){
				piezas[i][j]=pieza(false,false,true,false,false,false,false,false);
			}else if(i==6){
				piezas[i][j]=pieza(true,false,true,false,false,false,false,false);
			}else if((i == 0 && j==0)||(i==0 && j==7)){
				piezas[i][j]=pieza(false,false,false,true,false,false,false,false);
			}else if((i==7 && j==0)||(i==7 && j==7)){
				piezas[i][j]=pieza(true,false,false,true,false,false,false,false);
			}else if((i == 0 && j == 1)||(i == 0 && j == 6)){
				piezas[i][j]=pieza(false,false,false,false,false,true,false,false);
			}else if((i == 7 && j == 1)||(i == 7 && j ==6)){
				piezas[i][j]=pieza(true,false,false,false,false,true,false,false);
			}else if((i == 0 && j == 2)||(i == 0 && j == 5)){
                                piezas[i][j]=pieza(false,false,false,false,true,false,false,false);
                        }else if((i == 7 && j == 2)||(i == 7 && j ==5)){
                                piezas[i][j]=pieza(true,false,false,false,true,false,false,false);
                        }else if((i == 0 && j == 3)){
                                piezas[i][j]=pieza(false,false,false,false,false,false,true,false);
                        }else if((i == 7 && j == 4)){
                                piezas[i][j]=pieza(true,false,false,false,false,false,true,false);
                        }else if((i == 0 && j == 4)){
                                piezas[i][j]=pieza(false,false,false,false,false,false,false,true);
                        }else if((i == 7 && j == 3)){
                                piezas[i][j]=pieza(true,false,false,false,false,false,false,true);
                        }else{
				 piezas[i][j]=pieza(false,true,false,false,false,false,false,false);
			}
		}
	}
}

void mostrarTablero(pieza** tablero){
    clear();
    init_pair(1, COLOR_RED, COLOR_WHITE);
    init_pair(2,COLOR_WHITE,COLOR_WHITE);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_RED, COLOR_GREEN);
    init_pair(5,COLOR_GREEN,COLOR_GREEN);
    init_pair(6, COLOR_BLACK, COLOR_GREEN);
    
    for(int i = 0; i<8; i++){
        for(int k = 0; k < 3; k++){
            if(k == 1){
                    printw(" %d ", 8-i);
                }else{
                    printw("   ");
                }
            for(int j = 0; j < 8; j++){
               if(i%2 == 0){
                    if(j%2 == 0){
                        if(k == 1){
                            if(tablero[i][j].blanca){
                                attron(COLOR_PAIR(1));
                                 if(tablero[i][j].isPeon){
                                    printw("  P  "); 
                                }else if(tablero[i][j].isAlfil){
                                    printw("  A  ");
                                }else if(tablero[i][j].isCaballo){
                                    printw("  C  ");
                                }else if(tablero[i][j].isTorre){
                                    printw("  T  ");
                                }else if(tablero[i][j].isDama){
                                    printw("  D  ");
                                }else if(tablero[i][j].isRey){
                                    printw("  R  ");
                                }else if(tablero[i][j].vacia){
                                    printw("     ");
                                }
                                attroff(COLOR_PAIR(1));
                            }else{
                                attron(COLOR_PAIR(3));
                                if(tablero[i][j].isPeon){
                                    printw("  P  "); 
                                }else if(tablero[i][j].isAlfil){
                                    printw("  A  ");
                                }else if(tablero[i][j].isCaballo){
                                    printw("  C  ");
                                }else if(tablero[i][j].isTorre){
                                    printw("  T  ");
                                }else if(tablero[i][j].isDama){
                                    printw("  D  ");
                                }else if(tablero[i][j].isRey){
                                    printw("  R  ");
                                }else if(tablero[i][j].vacia){
                                    printw("     ");
                                }
                                attroff(COLOR_PAIR(3));
                            }
                            
                        }else{
                            attron(COLOR_PAIR(2));
                            printw("     ");
                            attroff(COLOR_PAIR(2));
                        }
                    }else{
                        if(k == 1){
                            if(tablero[i][j].blanca){
                                attron(COLOR_PAIR(4));
                                if(tablero[i][j].isPeon){
                                    printw("  P  "); 
                                }else if(tablero[i][j].isAlfil){
                                    printw("  A  ");
                                }else if(tablero[i][j].isCaballo){
                                    printw("  C  ");
                                }else if(tablero[i][j].isTorre){
                                    printw("  T  ");
                                }else if(tablero[i][j].isDama){
                                    printw("  D  ");
                                }else if(tablero[i][j].isRey){
                                    printw("  R  ");
                                }else if(tablero[i][j].vacia){
                                    printw("     ");
                                }
                                attroff(COLOR_PAIR(4));
                            }else{
                                attron(COLOR_PAIR(6));
                                if(tablero[i][j].isPeon){
                                    printw("  P  "); 
                                }else if(tablero[i][j].isAlfil){
                                    printw("  A  ");
                                }else if(tablero[i][j].isCaballo){
                                    printw("  C  ");
                                }else if(tablero[i][j].isTorre){
                                    printw("  T  ");
                                }else if(tablero[i][j].isDama){
                                    printw("  D  ");
                                }else if(tablero[i][j].isRey){
                                    printw("  R  ");
                                }else if(tablero[i][j].vacia){
                                    printw("     ");
                                }
                                attroff(COLOR_PAIR(6));
                            }
                            
                        }else{
                            attron(COLOR_PAIR(5));
                            printw("     ");
                            attroff(COLOR_PAIR(5));
                        }
                    }
               }else{
                    if(j%2 == 0){
                        if(k == 1){
                            if(tablero[i][j].blanca){
                                attron(COLOR_PAIR(4));
                                if(tablero[i][j].isPeon){
                                    printw("  P  "); 
                                }else if(tablero[i][j].isAlfil){
                                    printw("  A  ");
                                }else if(tablero[i][j].isCaballo){
                                    printw("  C  ");
                                }else if(tablero[i][j].isTorre){
                                    printw("  T  ");
                                }else if(tablero[i][j].isDama){
                                    printw("  D  ");
                                }else if(tablero[i][j].isRey){
                                    printw("  R  ");
                                }else if(tablero[i][j].vacia){
                                    printw("     ");
                                }
                                attroff(COLOR_PAIR(4));
                            }else{
                                attron(COLOR_PAIR(6));
                                if(tablero[i][j].isPeon){
                                    printw("  P  "); 
                                }else if(tablero[i][j].isAlfil){
                                    printw("  A  ");
                                }else if(tablero[i][j].isCaballo){
                                    printw("  C  ");
                                }else if(tablero[i][j].isTorre){
                                    printw("  T  ");
                                }else if(tablero[i][j].isDama){
                                    printw("  D  ");
                                }else if(tablero[i][j].isRey){
                                    printw("  R  ");
                                }else if(tablero[i][j].vacia){
                                    printw("     ");
                                }
                                attroff(COLOR_PAIR(6));
                            }
                            
                        }else{
                            attron(COLOR_PAIR(5));
                            printw("     ");
                            attroff(COLOR_PAIR(5));
                        }
                    }else{
                        if(k == 1){
                            if(tablero[i][j].blanca){
                                attron(COLOR_PAIR(1));
                                if(tablero[i][j].isPeon){
                                    printw("  P  "); 
                                }else if(tablero[i][j].isAlfil){
                                    printw("  A  ");
                                }else if(tablero[i][j].isCaballo){
                                    printw("  C  ");
                                }else if(tablero[i][j].isTorre){
                                    printw("  T  ");
                                }else if(tablero[i][j].isDama){
                                    printw("  D  ");
                                }else if(tablero[i][j].isRey){
                                    printw("  R  ");
                                }else if(tablero[i][j].vacia){
                                    printw("     ");
                                }
                                attroff(COLOR_PAIR(1));
                            }else{
                                attron(COLOR_PAIR(3));
                                if(tablero[i][j].isPeon){
                                    printw("  P  "); 
                                }else if(tablero[i][j].isAlfil){
                                    printw("  A  ");
                                }else if(tablero[i][j].isCaballo){
                                    printw("  C  ");
                                }else if(tablero[i][j].isTorre){
                                    printw("  T  ");
                                }else if(tablero[i][j].isDama){
                                    printw("  D  ");
                                }else if(tablero[i][j].isRey){
                                    printw("  R  ");
                                }else if(tablero[i][j].vacia){
                                    printw("     ");
                                }
                                attroff(COLOR_PAIR(3));
                            }
                            
                        }else{
                            attron(COLOR_PAIR(2));
                            printw("     ");
                            attroff(COLOR_PAIR(2));
                        }
                    }
               }    
            }
            printw("\n");
        }
    }
    printw("     A    B    C    D    E    F    G     H");
    printw("\n");
}


int lettersToNumbers(char letra){
        int num=0;
        if(letra == 65){
                num = 0;
        }else if(letra == 66){
                num = 1;
        }else if(letra == 67){
                num = 2;
        }else if(letra == 68){
                num = 3;
        }else if(letra == 69){
                num = 4;
        }else if(letra == 70){
                num = 5;
        }else if(letra == 71){
                num = 6;
        }else if(letra == 72){
                num = 7;
        }
        return num;
}

int charToInt(char letra){
        if (letra == 48){
                return 100;
        }else if(letra == 49){
                return 7;
        }else if(letra == 50){
                return 6;
        }else if(letra == 51){
                return 5;
        }else if(letra == 52){
                return 4;
        }else if(letra == 53){
                return 3;
        }else if(letra == 54){
                return 2;
        }else if(letra == 55){
                return 1;
        }else if(letra == 56){
                return 0;
        }else if(letra == 57){
                return 1;
        }
}

int verifyNextSquare(int x, int y, pieza** tablero, int jugador){
	if(jugador==1){
		if(tablero[x][y].vacia){
			return 1;
		}else if(tablero[x][y].vacia==false && tablero[x][y].blanca==false){
			return 2;
		}else if(tablero[x][y].vacia==false && tablero[x][y].blanca){
			return 3;
		}
	}else if(jugador==2){
		if(tablero[x][y].vacia){
                        return 1;
                }else if(tablero[x][y].vacia==false && tablero[x][y].blanca){
                        return 2;
                }else if(tablero[x][y].vacia==false && tablero[x][y].blanca==false){
                        return 3;
                }

	}	
}

bool verifyCurrentSquare(int x, int y, int jugador, pieza** tablero){
	if(jugador==1){
		if(tablero[x][y].vacia){
			return false;
		}else if(tablero[x][y].blanca==false){		
			return false;
		}else{
			return true;
		}				
	}else if(jugador==2){
		if(tablero[x][y].vacia){               
                        return false;
                }else if(tablero[x][y].blanca){                
                        return false;
                }else{
                        return true;
                } 
	}
}

int conocerTipo(int x, int y, pieza** tablero){
	if(tablero[x][y].isPeon){
		return 1;
	}if(tablero[x][y].isTorre){
                return 2;
        }if(tablero[x][y].isAlfil){
                return 3;
        }if(tablero[x][y].isCaballo){
                return 4;
        }if(tablero[x][y].isDama){
                return 5;
        }if(tablero[x][y].isRey){
                return 6;
        }else if(tablero[x][y].vacia){
        	return 0;
        }
}

bool movimientoPeon(pieza** tablero ,int x1, int y1, int x2, int y2, int jugador, int& tipo1, int tipo2){
	bool retorno;
    	char opcion;

    if(x1<8&&x1>=0&&x2<8&&x2>=0&&y1<8&&y1>=0&&y2<8&&y2>=0){
		if(jugador == 1){ 
            		if(y1==y2){
                		if(x1 == 6){
                    			if(((x2 == x1-1) ||(x2 == x1-2 ))&& tipo2 == 0){
                        			retorno = true;
                    			}else{
                        			retorno = false;
                    			}
                		}else{
                    			if((x2 == x1-1) && tipo2 == 0){
                        			retorno = true;
                    			}else{
                        			retorno = false;
                    			}   
                		}
            		}else{
                		if(((x2 == x1-1) && (y2 == y1-1))||((x2 == x1-1) && (y2 == y1+1))){
                            		if(validacionPeon(tablero,x2,y2,jugador)){
                                		retorno = true;
                            		}else{
                                		retorno = false;
                            		}
                    		}else{
                    			retorno =  false;
                    		}
            		}

           		 if(retorno && x2 == 0){
                		printw("Desea convertir su peon a: \n");
                		printw("1. Torre\n");
                		printw("2. Alfil\n");
                		printw("3. Reina\n");
                		printw("Presiona otra si desea seguir con el peon\n");
                		printw("Ingrese una opcion: ");
                		opcion = getch();

                		if(opcion == 49){
                    			cambiarCasilla(tablero,x1,y1,0,true);
                    			cambiarCasilla(tablero,x1,y1,1,false);
                    			tipo1 = 2;
                		}else if(opcion == 50){
                    			cambiarCasilla(tablero,x1,y1,0,true);
                    			cambiarCasilla(tablero,x1,y1,1,false);
                    			tipo1 = 3;
                		}else if(opcion == 51){
                    			cambiarCasilla(tablero,x1,y1,0,true);
                    			cambiarCasilla(tablero,x1,y1,1,false);
                    			tipo1 = 5;
                		}
            		}        		
	}else if(jugador == 2){
           	if(y1 == y2){
                	if(x1 == 1){
                    		if(((x2 == x1+1) ||(x2 == x1+2 )) && tipo2 == 0){
                        		retorno =  true;
                    		}else{
                    			retorno =  false;
                    		}
                	}else{
                    		if((x2 == x1+1) && tipo2 == 0){
                        		retorno = true;
                    		}else{
                        		retorno =  false;
                    		}		   
                	}
            	}else{
            		if(((x2 == x1+1) && (y2 == y1-1))||((x2 == x1+1) && (y2 == y1+1))){
                        	if(validacionPeon(tablero,x2,y2,jugador)){
                                	retorno =  true;
                            	}else{
                                	retorno =  false;
                            	}
                    	}else{
                        	retorno =  false;
                    	}
            	}

            	if(retorno && x2 == 7){
                	printw("Desea convertir su peon a: \n");
               		printw("1. Torre\n");
                	printw("2. Alfil\n");
                	printw("3. Reina\n");
                	printw("Presiona otra si desea seguir con el peon\n");
                	printw("Ingrese una opcion: ");
                	opcion = getch();

                	if(opcion == 49){
                    		cambiarCasilla(tablero,x1,y1,0,true);
                    		cambiarCasilla(tablero,x1,y1,1,false);
                    		tipo1 = 2;
                	}else if(opcion == 50){
                    		cambiarCasilla(tablero,x1,y1,0,true);
                    		cambiarCasilla(tablero,x1,y1,1,false);
                    		tipo1 = 3;
                	}else if(opcion == 51){
                    		cambiarCasilla(tablero,x1,y1,0,true);
                    		cambiarCasilla(tablero,x1,y1,1,false);
                    		tipo1 = 5;
                	}
            	}
        }		               
    }
    return retorno;    
}

bool validacionPeon(pieza** tablero, int x, int y, int turno){
    if(turno == 1){
        if(x >= 0 && x < 8 && y >= 0 && y<8){
            if(tablero[x][y].vacia == false && tablero[x][y].blanca == false){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }else if(turno == 2){
        if(x >= 0 && x < 8 && y >= 0 && y<8){
            if(tablero[x][y].vacia == false && tablero[x][y].blanca){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
}

bool movimientoTorre(pieza** tablero, int x1, int y1, int x2, int y2){
	if(x1<8&&x1>=0&&x2<8&&x2>=0&&y1<8&&y1>=0&&y2<8&&y2>=0){
		if(recorridoTorre(tablero, x1, y1, x2, y2)){
			if(x1==x2){
				return true;
			}else if(y1==y2){
				return true;
			}else{
				return false;
			}
		}else{
			return false;
		}

	}else{
		return false;
	}
}

bool movimientoAlfil(pieza** tablero, int x1, int y1, int x2, int y2){
	if(x1<8&&x1>=0&&x2<8&&x2>=0&&y1<8&&y1>=0&&y2<8&&y2>=0){
		if(recorridoAlfil(tablero,x1,y1,x2,y2)){
			if((x1+y1)==(x2+y2)){
				return true;
			}else if(abs(x1-y1)==abs(x2-y2)){
				return true;
			}else{
				return false;
			}
		}else{
			return false;
		}
	 }else{
                return false;
         }	
}

bool movimientoCaballo(int x1, int y1, int x2, int y2){
	if(x1<8&&x1>=0&&x2<8&&x2>=0&&y1<8&&y1>=0&&y2<8&&y2>=0){
		if((x2 == x1-2) && (y2 == y1 +1)){
			return true;
		}else if((x2 == x1-2) && (y2 == y1 -1)){
			return true;
		}else if((x2 == x1-1) && (y2 == y1 - 2)){
			return true;
		}else if((x2 == x1-1) && (y2 == y1 +2)){
			return true;
		}else if((x2 == x1+1) && (y2 == y1 -2)){
			return true;
		}else if((x2 == x1+1) && (y2 == y1 +2)){
			return true;
		}else if((x2 == x1+2) && (y2 == y1 -1)){
			return true;
		}else if((x2 == x1+2) && (y2 == y1 +1)){
			return true;
		}else{
			return false;
		}		
	}else{
                return false;
        }	
}

bool movimientoDama(pieza** tablero,int x1, int y1, int x2, int y2){
	if(x1<8&&x1>=0&&x2<8&&x2>=0&&y1<8&&y1>=0&&y2<8&&y2>=0){
		if(movimientoTorre(tablero,x1,y1,x2,y2)){
                	return true;   
          	}else if(movimientoAlfil(tablero,x1,y1,x2,y2)){
                	return true;
          	}else{
            		return false;
          	}
        }else{
                return false;
        }

}

bool movimientoRey(pieza** tab, int x1, int y1, int x2, int y2, int turno){
	bool retorno = true; 
	
	if(x1<8&&x1>=0&&x2<8&&x2>=0&&y1<8&&y1>=0&&y2<8&&y2>=0){
        	if(verifyNextSquare(x2,y2,tab,turno)!=3){
		        if((x2 == x1-1) && (y2 == y1 -1)){
                        retorno = true;
                }else if((x2 == x1-1) && (y2 == y1)){
                        retorno = true;
                }else if((x2 == x1-1) && (y2 == y1 + 1)){
                        retorno = true;
                }else if((x2 == x1+1) && (y2 == y1 +1)){
                        retorno = true;
                }else if((x2 == x1) && (y2 == y1 -1)){
                        retorno = true;
                }else if((x2 == x1) && (y2 == y1 +1)){
                        retorno = true;
                }else if((x2 == x1+1) && (y2 == y1 -1)){
                        retorno = true;
                }else if((x2 == x1+1) && (y2 == y1)){
                        retorno = true;
                }else{
                        retorno =  false;
                }

                
                if(retorno == true){
                	if(evaluarHacke(tab, x2,y2,turno)){
						retorno = false;
					}else{
						retorno = true;
					}
				}
            }else if(verifyNextSquare(x2,y2,tab,turno)==3){
                return false;
            }
        }else{
                retorno = false;
        }
       
        return retorno;

}


void mover(int x1, int y1, int x2, int y2, int tipo1, int jugador, pieza** tablero){

	if(jugador==1){

		if(tipo1==1){
            		tablero[x2][y2].setPeon(true); 
            		tablero[x2][y2].setBlanca(true);
			tablero[x2][y2].setVacia(false);
             		tablero[x1][y1].setBlanca(false);
			tablero[x1][y1].setPeon(false);
			tablero[x1][y1].setVacia(true);
                }else if(tipo1==2){
            		tablero[x2][y2].setTorre(true);
            		tablero[x2][y2].setBlanca(true);
			tablero[x2][y2].setVacia(false);
            		tablero[x1][y1].setBlanca(false);
			tablero[x1][y1].setTorre(false);
            		tablero[x1][y1].setVacia(true);
                }else if(tipo1==3){
            		tablero[x2][y2].setAlfil(true);
            		tablero[x2][y2].setBlanca(true);
			tablero[x2][y2].setVacia(false);
            		tablero[x1][y1].setBlanca(false);
			tablero[x1][y1].setAlfil(false);
            		tablero[x1][y1].setVacia(true);
                }else if(tipo1==4){
            		tablero[x2][y2].setCaballo(true);
            		tablero[x2][y2].setBlanca(true);
			tablero[x2][y2].setVacia(false);
            		tablero[x1][y1].setBlanca(false);
			tablero[x1][y1].setCaballo(false);
            		tablero[x1][y1].setVacia(true);
                }else if(tipo1==5){
            		tablero[x2][y2].setDama(true);
            		tablero[x2][y2].setBlanca(true);
			tablero[x2][y2].setVacia(false);
            		tablero[x1][y1].setBlanca(false);
			tablero[x1][y1].setDama(false);
            		tablero[x1][y1].setVacia(true);
                }else if(tipo1==6){
            		tablero[x2][y2].setRey(true);
            		tablero[x1][y1].setBlanca(false);
            		tablero[x2][y2].setBlanca(true);
			tablero[x2][y2].setVacia(false);
			tablero[x1][y1].setRey(false);
            		tablero[x1][y1].setVacia(true);
                }

	}else if(jugador==2){
		if(tipo1==1){
                        tablero[x2][y2].setPeon(true);
                        tablero[x2][y2].setBlanca(false);
			tablero[x2][y2].setVacia(false);
                        tablero[x1][y1].setBlanca(true);
                        tablero[x1][y1].setPeon(false);
                        tablero[x1][y1].setVacia(true);
                }else if(tipo1==2){
                        tablero[x2][y2].setTorre(true);
                        tablero[x2][y2].setBlanca(false);
			tablero[x2][y2].setVacia(false);
                        tablero[x1][y1].setBlanca(true);
                        tablero[x1][y1].setTorre(false);
                        tablero[x1][y1].setVacia(true);
                }else if(tipo1==3){
                        tablero[x2][y2].setAlfil(true);
                        tablero[x2][y2].setBlanca(false);
                        tablero[x1][y1].setBlanca(true);
			tablero[x2][y2].setVacia(false);
                        tablero[x1][y1].setAlfil(false);
                        tablero[x1][y1].setVacia(true);
                }else if(tipo1==4){
                        tablero[x2][y2].setCaballo(true);
                        tablero[x2][y2].setBlanca(false);
                        tablero[x1][y1].setBlanca(true);
			tablero[x2][y2].setVacia(false);
                        tablero[x1][y1].setCaballo(false);
                        tablero[x1][y1].setVacia(true);
                }else if(tipo1==5){
                        tablero[x2][y2].setDama(true);
                        tablero[x2][y2].setBlanca(false);
                        tablero[x1][y1].setBlanca(true);
			tablero[x2][y2].setVacia(false);
                        tablero[x1][y1].setDama(false);
                        tablero[x1][y1].setVacia(true);
                }else if(tipo1==6){
                        tablero[x2][y2].setRey(true);
                        tablero[x2][y2].setBlanca(false);
                        tablero[x1][y1].setBlanca(true);
			tablero[x2][y2].setVacia(false);
                        tablero[x1][y1].setRey(false);
                        tablero[x1][y1].setVacia(true);
                }

	}
}

void cambiarCasilla(pieza** tablero, int x, int y, int tipo, bool estado){
	if(tipo == 0){
		tablero[x][y].setVacia(estado);
	}else if(tipo == 1){
		tablero[x][y].setPeon(estado);
	}else if(tipo == 2){
		tablero[x][y].setTorre(estado);
	}else if(tipo == 3){
		tablero[x][y].setAlfil(estado);
	}else if(tipo == 4){
		tablero[x][y].setCaballo(estado);
	}else if(tipo == 5){
		tablero[x][y].setDama(estado);
	}else if(tipo==6){
		tablero[x][y].setRey(estado);
	}else if(tipo == 7){
		tablero[x][y].setBlanca(estado);
	}


}

void comer(pieza** tablero, int x1, int y1, int x2, int y2, int jugador, int tipo1, int tipo2){
	if(jugador == 1){
		cambiarCasilla(tablero, x1, y1, tipo1, false);
		cambiarCasilla(tablero,x1,y1,0,true);
        	cambiarCasilla(tablero,x1,y1,7,false);
        	cambiarCasilla(tablero, x2,y2,0,false);
		cambiarCasilla(tablero,x2,y2,tipo2,false);
		cambiarCasilla(tablero,x2,y2,tipo1,true);
		cambiarCasilla(tablero,x2,y2,7,true);
	}else if(jugador == 2){
		cambiarCasilla(tablero, x1, y1, tipo1, false);
		cambiarCasilla(tablero,x1,y1,0,true);
        	cambiarCasilla(tablero,x1,y1,7,true);
        	cambiarCasilla(tablero,x2,y2,0,false);
		cambiarCasilla(tablero,x2,y2,tipo2,false);
		cambiarCasilla(tablero,x2,y2,tipo1,true);
		cambiarCasilla(tablero,x2,y2,7,false);
	}

}

bool recorridoTorre(pieza** pieza, int x1, int y1, int x2, int y2){
	bool retorno = true;
	if(x1 == x2){
		if(y1 < y2){
			for(int i = y1+1; i < y2; i++){
				if(pieza[x1][i].vacia == false){
					retorno = false;
				}
			}
		}else if(y2 < y1){
			for(int i = y2 + 1; i < y1; i++){
				if(pieza[x1][i].vacia == false){
					retorno = false;
				}
			}
		}
	}else if(y1 == y2){
		if(x1 < x2){
			for(int i = x1+1; i < x2; i++){
				if(pieza[i][y1].vacia == false){
					retorno = false;
				}
			}
		}else if(x2 < x1){
			for(int i = x2 + 1; i < x1; i++){
				if(pieza[i][y1].vacia == false){
					retorno = false;
				}
			}
		}	
	}	
	return retorno;
}

bool recorridoAlfil(pieza** tablero, int x1, int y1, int x2, int y2){
	bool retorno = true;
	if((x1+y1) == (x2+y2)){
		if(x1 < x2){
			for (int i = x1+1; i < x2 ; i++){
                		y1--;
				if(tablero[i][y1].vacia == false){
					retorno = false;
				}
				
			}
		}else if(x1 > x2){
			for (int i = x1-1; i > x2; i--){
                		y1++;
				if(tablero[i][y1].vacia == false){
					retorno = false;
				}
				
			}
		}	
	}else if((abs(x1-y1)) == (abs(x2-y2))){
		if(x1 < x2){
			for (int i = x1+1; i < x2 ; i++){
                		y1++;
				if(tablero[i][y1].vacia == false){
					retorno = false;
				}
			
			}
		}else if(x1 > x2){
			for (int i = x1-1; i > x2; i--){
                		y1--;
				if(tablero[i][y1].vacia == false){
					retorno = false;
				}
				
			}
		}
	}
	return retorno;
}

void findKing(pieza** tablero, int turno, int* pos){

    for(int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if(turno == 1){
                if(tablero[i][j].isRey && tablero[i][j].blanca){
                    pos[0] = i;
                    pos[1] = j;
                }
            }else if(turno == 2){
                if(tablero[i][j].isRey && tablero[i][j].blanca==false){
                    pos[0] = i;
                    pos[1] = j;
                }
            }
        }
    }
}

bool evaluarHacke(pieza** tab, int x, int y, int turno){
    bool retorno = false;
    int ref;
    if(turno == 1){
        for(int i = 0; i < 8; i++){
            for(int k = 0; k < 8; k++){
                if(!(i==x && y==k)){
                	if(tab[i][k].blanca==false && tab[i][k].isPeon){ 
                        	ref = 1;
                        	if(movimientoPeon(tab,i,k,x,y,turno,ref,6)){
                            		retorno = true;
                        	}
                	}else if(tab[i][k].blanca==false && tab[i][k].isTorre){
                        	if(movimientoTorre(tab,i,k,x,y)){
                            		retorno = true;
                        	}
                    	}else if(tab[i][k].blanca==false && tab[i][k].isAlfil){
                        	if(movimientoAlfil(tab,i,k,x,y)){
                            		retorno = true;
                        	}
                    }else if(tab[i][k].blanca==false && tab[i][k].isCaballo){
                        	if(movimientoCaballo(i,k,x,y)){
                            		retorno = true;
                        	}
                    }else if(tab[i][k].blanca==false && tab[i][k].isDama){
                        	if(movimientoDama(tab,i,k,x,y)){
                            		retorno = true;
                        	}
                    	}
                }
            }
        }
    }else if(turno ==2){
        for(int i = 0; i < 8; i++){
            for(int k = 0; k < 8; k++){
                if(!(i==x && y==k)){
                	if(tab[i][k].blanca && tab[i][k].isPeon){
                    		ref = 1;
                    	if(movimientoPeon(tab,i,k,x,y,turno,ref,6)){
                            retorno = true;
                        }
                    }else if(tab[i][k].blanca && tab[i][k].isTorre){
                        if(movimientoTorre(tab,i,k,x,y)){
                            retorno = true;
                        }
                    }else if(tab[i][k].blanca && tab[i][k].isAlfil){
                        if(movimientoAlfil(tab,i,k,x,y)){
                            retorno = true;
                        }
                    }else if(tab[i][k].blanca && tab[i][k].isCaballo){
                        if(movimientoCaballo(i,k,x,y)){
                            retorno = true;
                        }
                    }else if(tab[i][k].blanca && tab[i][k].isDama){
                        if(movimientoDama(tab,i,k,x,y)){
                            retorno = true;
                        }
                    }
                }
            }
        }
    }
    return retorno;
}

bool hackeMate(pieza** tab, int x, int y){
    bool retorno = true;
    int turno;

    if(tab[x][y].blanca){
        turno = 1;
    }else{
        turno = 2;
    }

    for(int i = 0; i<8; i++){
        for(int k = 0; k < 8; k++){
            if(movimientoRey(tab,x,y,i,k,turno)){
                retorno = false;
            }
        }
    }
    return retorno;
}

bool detectarIntercepcion(pieza** tab, int x, int y, int turno){
    bool retorno = false;

    if(turno == 1){
        for(int i = 0; i < 8; i++){
            for(int k = 0; k < 8; k++){
                
                if(tab[i][k].blanca==false && tab[i][k].isTorre){
                    if(movimientoTorre(tab,i,k,x,y)){
                        if(bloqueo(tab,x,y,i,k) || comerAmenaza(tab, i, k, turno)){
                            retorno = true;
                        }
                    }
                }else if(tab[i][k].blanca==false && tab[i][k].isAlfil){
                    if(movimientoAlfil(tab,i,k,x,y)){
                        if(bloqueo(tab,x,y,i,k) || comerAmenaza(tab, i, k, turno)){
                            retorno = true;
                        }
                    }
                }else if(tab[i][k].blanca==false && tab[i][k].isDama){
                    if(movimientoDama(tab,i,k,x,y)){
                        if(bloqueo(tab,x,y,i,k)|| comerAmenaza(tab, i, k, turno)){
                            retorno = true;
                        }
                    }
                }else if(tab[i][k].blanca==false && tab[i][k].isCaballo){
                    if(movimientoCaballo(i,k,x,y)){
                        if(comerAmenaza(tab, i, k, turno)){
                            retorno = true;
                        }
                    }
                }
            }
        }  
    }else if(turno ==2){
        for(int i = 0; i < 8; i++){
            for(int k = 0; k < 8; k++){
                    if(tab[i][k].blanca && tab[i][k].isTorre){
                    if(movimientoTorre(tab,i,k,x,y)){
                       if(bloqueo(tab,x,y,i,k) || comerAmenaza(tab, i, k, turno)){
                            retorno = true;
                        }
                    }
                }else if(tab[i][k].blanca && tab[i][k].isAlfil){
                    if(movimientoAlfil(tab,i,k,x,y)){
                        if(bloqueo(tab,x,y,i,k) || comerAmenaza(tab, i, k, turno)){
                            retorno = true;
                        }
                    }
                }else if(tab[i][k].blanca && tab[i][k].isDama){
                    if(movimientoDama(tab,i,k,x,y)){
                        if(bloqueo(tab,x,y,i,k)|| comerAmenaza(tab, i, k, turno)){
                            retorno = true;
                        }
                    }
                }else if(tab[i][k].blanca && tab[i][k].isCaballo){
                    if(movimientoCaballo(i,k,x,y)){
                        if(comerAmenaza(tab, i, k, turno)){
                            retorno = true;
                        }
                    }
                }
            }
        }
    }
    return retorno;  
}

bool bloqueo (pieza** tab, int reyx, int reyy, int amenazax, int amenazay){
    bool retorno = false;
    int turno;

    if(tab[reyx][reyy].blanca){
        turno = 1;
    }else{
        turno = 2;
    }

    for(int i = 0; i < 8; i++){
        for(int k = 0; k < 8; k++){
             if(reyx == i || reyy == k || (i+k) == (reyx +reyy) || abs(i-k) == abs(reyx-reyy)){
                if(movimientoDama(tab,amenazax,amenazay, i, k) && tab[i][k].vacia){   
                    if(movimientoDama(tab,reyx,reyy,i,k)){
                        if(intercepcion(tab,i,k,turno)){
                            retorno = true;
                        }
                    }
                }
            }
        }
    }
    return retorno;
}

bool intercepcion(pieza** tab, int x, int y, int turno){
    bool retorno = false;

    if(turno == 1){
        for(int i = 0; i < 8; i++){
            for(int k = 0; k < 8; k++){
                if(tab[i][k].blanca){
                    if(tab[i][k].isAlfil && movimientoAlfil(tab, i,k,x,y)){
                        retorno = true;
                    }else if(tab[i][k].isTorre && movimientoTorre(tab,i,k,x,y))
                    	retorno = true;
                    }else if(tab[i][k].isDama && movimientoDama(tab,i,k,x,y)){
                        retorno = true;
                    }else if(tab[i][k].isCaballo && movimientoCaballo(i,k,x,y)){
                        retorno = true;
                }
           }
       }
    }else if(turno == 2){
        for(int i = 0; i < 8; i++){
            for(int k = 0; k < 8; k++){
                if(tab[i][k].blanca == false){
                    if(tab[i][k].isAlfil && movimientoAlfil(tab, i,k,x,y)){
                        retorno = true;
                    }else if(tab[i][k].isTorre && movimientoTorre(tab,i,k,x,y))
                    retorno = true;
                }else if(tab[i][k].isDama && movimientoDama(tab,i,k,x,y)){
                    retorno = true;
                }else if(tab[i][k].isCaballo && movimientoCaballo(i,k,x,y)){
                    retorno = true;
                }
            }
        }   
    }
    return retorno;
}

bool comerAmenaza(pieza** tab, int x, int y, int turno){
    bool retorno = false;
    int ref = 1;

    if(turno == 1){
        for(int i = 0; i < 8; i++){
            for(int k = 0; k < 8; k++){
                if(tab[i][k].blanca){
                    if(tab[i][k].isPeon){
                    if(movimientoPeon(tab,i,k,x,y,turno,ref,6)){
                            retorno = true;
                        }
                    }else if(tab[i][k].isTorre){
                        if(movimientoTorre(tab,i,k,x,y)){
                            retorno = true;
                        }
                    }else if(tab[i][k].isAlfil){
                        if(movimientoAlfil(tab,i,k,x,y)){
                            retorno = true;
                        }
                    }else if(tab[i][k].isCaballo){
                        if(movimientoCaballo(i,k,x,y)){
                            retorno = true;
                        }
                    }else if(tab[i][k].isDama){
                        if(movimientoDama(tab,i,k,x,y)){
                            retorno = true;
                        }
                    }
                }
            }
        }
    }else if(turno == 2){
        for(int i = 0; i < 8; i++){
            for(int k = 0; k < 8; k++){
                if(tab[i][k].blanca == false){
                    if(tab[i][k].isPeon){
                    if(movimientoPeon(tab,i,k,x,y,turno,ref,6)){
                            retorno = true;
                        }
                    }else if(tab[i][k].isTorre){
                        if(movimientoTorre(tab,i,k,x,y)){
                            retorno = true;
                        }
                    }else if(tab[i][k].isAlfil){
                        if(movimientoAlfil(tab,i,k,x,y)){
                            retorno = true;
                        }
                    }else if(tab[i][k].isCaballo){
                        if(movimientoCaballo(i,k,x,y)){
                            retorno = true;
                        }
                    }else if(tab[i][k].isDama){
                        if(movimientoDama(tab,i,k,x,y)){
                            retorno = true;
                        }
                    }
                }
            }
        }
    }
    return retorno;
}
