#ifndef PIEZA_H
#define PIEZA_H

class pieza{
	public:
		bool blanca;
		bool vacia;
		bool isPeon;
		bool isTorre;
		bool isAlfil;
		bool isCaballo;
		bool isDama;
		bool isRey;
		
		pieza();
		pieza(bool , bool , bool , bool , bool , bool , bool , bool );
		
		void setBlanca(bool);
		void setVacia(bool);
		void setPeon(bool);
		void setTorre(bool);
		void setAlfil(bool);
		void setCaballo(bool);
		void setDama(bool);
		void setRey(bool);
};
#endif
