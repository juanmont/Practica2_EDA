/*-ArbolVacio:->Arbin.Generadora implementada en el
constructor sin par�metros.
- Cons : Arbin, Elem, Arbin->Arbin.Generadora implementada
en un constructor con tres par�metros.
- hijoIz, hijoDr : Arbin - ->Arbin.Observadoras que
devuelven el hijo izquiero o derecho de un �rbol.
- esVacio : Arbin->Bool.Observadora que devuelve si
un �rbol binario es vac�o.

@author Marco Antonio G�mez Mart�n
*/
#ifndef _ARBIN_H_
#define _ARBIN_H_

#include "List.h"
#include "Exceptions.h"
#include "Queue.h"

template <class T>
class Arbin {
public:

	/** Constructor; operacion ArbolVacio */
	Arbin() : _ra(NULL) {
	}

	/** Constructor; operacion Cons */
	Arbin(const Arbin &iz, const T &elem, const Arbin &dr) :
		_ra(new Nodo(iz._ra, elem, dr._ra)) {
		_ra->addRef();
	}

	Arbin(const T &elem) :
		_ra(new Nodo(NULL, elem, NULL)) {
		_ra->addRef();
	}

	/** Destructor; elimina la estructura jer�rquica de nodos. */
	~Arbin() {
		libera();
		_ra = NULL;
	}

	/**
	Devuelve el elemento almacenado en la raiz

	raiz(Cons(iz, elem, dr)) = elem
	error raiz(ArbolVacio)
	@return Elemento en la ra�z.
	*/
	const T &raiz() const {
		if (esVacio())
			throw exception();
		return _ra->_elem;
	}

	/**
	Devuelve un �rbol copia del �rbol izquierdo.
	Es una operaci�n parcial (falla con el �rbol vac�o).

	hijoIz(Cons(iz, elem, dr)) = iz
	error hijoIz(ArbolVacio)
	*/
	Arbin hijoIz() const {
		if (esVacio())
			throw exception();

		return Arbin(_ra->_iz);
	}

	/**
	Devuelve un �rbol copia del �rbol derecho.
	Es una operaci�n parcial (falla con el �rbol vac�o).

	hijoDr(Cons(iz, elem, dr)) = dr
	error hijoDr(ArbolVacio)
	*/
	Arbin hijoDr() const {
		if (esVacio())
			throw exception();
		return Arbin(_ra->_dr);
	}


	/**
	Operaci�n observadora que devuelve si el �rbol
	es vac�o (no contiene elementos) o no.

	esVacio(ArbolVacio) = true
	esVacio(Cons(iz, elem, dr)) = false
	*/
	bool esVacio() const {
		return _ra == NULL;
	}

	// //
	// RECORRIDOS SOBRE EL �RBOL
	// //

	List<T> preorden() const {
		List<T> ret;
		preordenAcu(_ra, ret);
		return ret;
	}

	List<T> inorden() const {
		List<T> ret;
		inordenAcu(_ra, ret);
		return ret;
	}

	List<T> postorden() const {
		List<T> ret;
		postordenAcu(_ra, ret);
		return ret;
	}

	List<T> niveles() const {

		if (esVacio())
			return List<T>();

		List<T> ret;
		Queue<Nodo*> porProcesar;
		porProcesar.push_back(_ra);

		while (!porProcesar.empty()) {
			Nodo *visita = porProcesar.front();
			porProcesar.pop_front();
			ret.push_back(visita->_elem);
			if (visita->_iz != NULL)
				porProcesar.push_back(visita->_iz);
			if (visita->_dr != NULL)
				porProcesar.push_back(visita->_dr);
		}

		return ret;
	}

	// //
	// OTRAS OPERACIONES OBSERVADORAS
	// //

	/**
	Devuelve el n�mero de nodos de un �rbol.
	*/
	unsigned int numNodos() const {
		return numNodosAux(_ra);
	}

	/**
	Devuelve la talla del �rbol.
	*/
	unsigned int talla() const {
		return tallaAux(_ra);
	}

	/**
	Devuelve el n�mero de hojas de un �rbol.
	*/
	unsigned int numHojas() const {
		return numHojasAux(_ra);
	}

	// //
	// M�TODOS DE "FONTANER�A" DE C++ QUE HACEN VERS�TIL
	// A LA CLASE
	// //

	/** Constructor copia */
	Arbin(const Arbin<T> &other) : _ra(NULL) {
		copia(other);
	}

	/** Operador de asignaci�n */
	Arbin<T> &operator=(const Arbin<T> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparaci�n. */
	bool operator==(const Arbin<T> &rhs) const {
		return comparaAux(_ra, rhs._ra);
	}

	bool operator!=(const Arbin<T> &rhs) const {
		return !(*this == rhs);
	}



protected:

	/**
	Clase nodo que almacena internamente el elemento (de tipo T),
	y los punteros al hijo izquierdo y al hijo derecho, as�
	como el n�mero de referencias que hay.
	*/
	class Nodo {
	public:
		Nodo() : _iz(NULL), _dr(NULL), _numRefs(0) {}
		Nodo(Nodo *iz, const T &elem, Nodo *dr) :
			_elem(elem), _iz(iz), _dr(dr), _numRefs(0) {
			if (_iz != NULL)
				_iz->addRef();
			if (_dr != NULL)
				_dr->addRef();
		}

		void addRef() { assert(_numRefs >= 0); _numRefs++; }
		void remRef() { assert(_numRefs > 0); _numRefs--; }

		T _elem;
		Nodo *_iz;
		Nodo *_dr;

		int _numRefs;
	};

	/**
	Constructor protegido que crea un �rbol
	a partir de una estructura jer�rquica existente.
	Esa estructura jer�rquica SE COMPARTE, por lo que
	se a�ade la referencia.
	Se utiliza en hijoIz e hijoDr.
	*/
	Arbin(Nodo *raiz) : _ra(raiz) {
		if (_ra != NULL)
			_ra->addRef();
	}

	void libera() {
		libera(_ra);
	}

	void copia(const Arbin &other) {
		assert(this != &other);
		_ra = other._ra;
		if (_ra != NULL)
			_ra->addRef();
	}

	// //
	// M�TODOS AUXILIARES PARA LOS RECORRIDOS
	// //

	static void preordenAcu(Nodo *ra, List<T> &acu) {
		if (ra == NULL)
			return;

		acu.push_back(ra->_elem);
		preordenAcu(ra->_iz, acu);
		preordenAcu(ra->_dr, acu);
	}

	static void inordenAcu(Nodo *ra, List<T> &acu) {
		if (ra == NULL)
			return;

		inordenAcu(ra->_iz, acu);
		acu.push_back(ra->_elem);
		inordenAcu(ra->_dr, acu);
	}

	static void postordenAcu(Nodo *ra, List<T> &acu) {
		if (ra == NULL)
			return;

		postordenAcu(ra->_iz, acu);
		postordenAcu(ra->_dr, acu);
		acu.push_back(ra->_elem);
	}

	// //
	// M�TODOS AUXILIARES (RECURSIVOS) DE OTRAS OPERACIONES
	// OBSERVADORAS
	// //

	static unsigned int numNodosAux(Nodo *ra) {
		if (ra == NULL)
			return 0;
		return 1 + numNodosAux(ra->_iz) + numNodosAux(ra->_dr);
	}

	static unsigned int tallaAux(Nodo *ra) {
		if (ra == NULL)
			return 0;

		int tallaiz = tallaAux(ra->_iz);
		int talladr = tallaAux(ra->_dr);
		if (tallaiz > talladr)
			return 1 + tallaiz;
		else
			return 1 + talladr;
	}

	static unsigned int numHojasAux(Nodo *ra) {
		if (ra == NULL)
			return 0;

		if ((ra->_iz == NULL) && (ra->_dr == NULL))
			return 1;

		return numHojasAux(ra->_iz) + numHojasAux(ra->_dr);
	}

private:

	/**
	Elimina todos los nodos de una estructura arb�rea
	que comienza con el puntero ra.
	Se admite que el nodo sea NULL (no habr� nada que
	liberar).
	*/
	static void libera(Nodo *ra) {
		if (ra != NULL) {
			ra->remRef();
			if (ra->_numRefs == 0) {
				libera(ra->_iz);
				libera(ra->_dr);
				delete ra;
			}
		}
	}

	/**
	Compara dos estructuras jer�rquicas de nodos,
	dadas sus raices (que pueden ser NULL).
	*/
	static bool comparaAux(Nodo *r1, Nodo *r2) {
		if (r1 == r2)
			return true;
		else if ((r1 == NULL) || (r2 == NULL))
			// En el if anterior nos aseguramos de
			// que r1 != r2. Si uno es NULL, el
			// otro entonces no lo ser�, luego
			// son distintos.
			return false;
		else {
			return (r1->_elem == r2->_elem) &&
				comparaAux(r1->_iz, r2->_iz) &&
				comparaAux(r1->_dr, r2->_dr);
		}
	}

protected:
	/**
	Puntero a la ra�z de la estructura jer�rquica
	de nodos.
	*/
	Nodo *_ra;
};

#endif // __ARBIN_H