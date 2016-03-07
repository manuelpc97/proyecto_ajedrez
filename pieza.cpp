#include "pieza.h"

pieza :: pieza(){

}

pieza :: pieza(bool blanca, bool vacia, bool isPeon, bool isTorre, bool isAlfil, bool isCaballo, bool isDama, bool isRey){
	this->vacia = vacia;
	this->blanca = blanca;
	this->isPeon = isPeon;
	this->isTorre = isTorre;
	this->isAlfil = isAlfil;
	this->isCaballo = isCaballo;
	this->isDama = isDama;
	this->isRey = isRey;
}

void pieza :: setBlanca(bool m){
	this->blanca = m;
}
void pieza :: setVacia(bool m){
	this->vacia = m;
}

void pieza :: setPeon(bool m){
	this->isPeon=m;
}

void pieza :: setTorre(bool m){
	this->isTorre = m;
}

void pieza :: setAlfil(bool m){
	this->isAlfil = m;
}

void pieza :: setCaballo(bool m){
	this->isCaballo = m;
}

void pieza :: setDama(bool m){
	this->isDama = m;
}
		
void pieza :: setRey(bool m){
	this->isRey = m;
}
