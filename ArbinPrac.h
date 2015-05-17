#ifndef _ARBINPRAC_H_
#define _ARBINPRAC_H_

#include "Exceptions.h"
#include "List.h" // Tipo devuelto por los recorridos
#include "Queue.h" // Tipo auxiliar para implementar el recorrido por niveles
#include "Arbin.h"

template <class T>
class ArbinPrac : public Arbin<T>{
public:

	ArbinPrac() : Arbin<T>(){}

	ArbinPrac(const T &elem) : Arbin<T>(elem){}

	ArbinPrac(const ArbinPrac &iz, const T &elem, const ArbinPrac &dr) : Arbin<T>(iz, elem, dr){}

	~ArbinPrac(){
		libera();
		_ra = NULL;
	}
	
	//esHoja: devuelve cierto si el ´arbol es una hoja (los hijos izquierdo y derecho son vac´ıos).
	bool esHoja(){
		return this->hijoIz().esVacio() && this->hijoDr().esVacio();
	}

	//frontera: devuelve una lista con todas las hojas del ´arbol, de izquierda a derecha.
	List<T> frontera(){
		List<T> lista;
		fronteraAux(lista, *this);
		return lista;
	}

	void fronteraAux(List<T> &lista,Arbin<T> &ab){
	if (ab.hijoIz().esVacio() && ab.hijoDr().esVacio()){
		lista.push_back(ab.raiz());
		return;
	}
	else{
		fronteraAux(lista, ab.hijoIz());
		fronteraAux(lista, ab.hijoDr());
		}
	}

	//espejo: devuelve un arbol nuevo que es la imagen especular del original.
	ArbinPrac<T> espejo(){
		if (this->esVacio())
			return ArbinPrac<T>();
		return ArbinPrac<T>(espejoAux(this->hijoDr()), this->raiz(), espejoAux(this->hijoIz()));
	}

	ArbinPrac<T> espejoAux(Arbin<T> &ab){
		if (ab.esVacio())
			return ArbinPrac<T>();
		return ArbinPrac<T>(espejoAux(ab.hijoDr()), ab.raiz(), espejoAux(ab.hijoIz()));
	}

	//minElem: devuelve el menor elemento del arbol.
	/*const E &minElem
	}*/

	T &minElem(){
		if (this->esVacio())
			throw InvalidAccessException();
		T minElem = this->raiz();
		T minElemIz;
		T minElemDr;
		if (!this->esHoja()){
				minElemIz = minElemExt(this->hijoIz());
				minElemDr = minElemExt(this->hijoDr());
			if (minElemIz < minElemDr){
			if (minElemIz < minElem)
				minElem = minElemIz;
				}
			else if (minElemDr <= minElemIz){
				if (minElemDr < minElem)
					minElem = minElemDr;
			}
		}
	return minElem;
	}

//private:
	/*List<E> fronteraAux(List<E> lista, ArbinPrac<E> ab){		
	}*/
};

#endif // __ARBIN_H