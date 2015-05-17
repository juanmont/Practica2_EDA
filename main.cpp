
#include <iostream>
#include <stdio.h>
#include "arbin.h"
#include "ArbinPrac.h"
#include "List.h"
#include "Queue.h"
#include <time.h>

using namespace std;
template <class T>
bool esHojaExt(const Arbin<T> &ab);

void printArbolAux(const Arbin<int> &arbol, int cont){
	if (cont > 0){
		for (int i = 0; i < cont; i++)
			cout << "...";
	}
	if (arbol.esVacio())
		cout << "<VACIO>" << endl;
	else if (esHojaExt(arbol))
		cout << arbol.raiz() << endl;
	else{
		cout << arbol.raiz() << endl;
		cont++;
		if (!arbol.hijoIz().esVacio())
		printArbolAux(arbol.hijoIz(), cont);
		if (!arbol.hijoDr().esVacio())
		printArbolAux(arbol.hijoDr(), cont);
	}
}


void printArbol(const Arbin<int> &arbol){
	if (!arbol.esVacio())
		printArbolAux(arbol, 0);
}


template <class E>
Arbin<E> creaArbolDegenerado(){
	Arbin<int> arbol7 = Arbin<int>(Arbin<E>(), 7, Arbin<E>());
	Arbin<int> arbol2 = Arbin<int>(Arbin<E>(), 2, Arbin<E>());
	Arbin<int> arbol10 = Arbin<int>(Arbin<E>(), 10, Arbin<E>());
	Arbin<int> arbol9 = Arbin<int>(Arbin<E>(), 9, Arbin<E>());
	Arbin<int> arbol3 = Arbin<int>(arbol7, 3, arbol2);
	Arbin<int> arbol5 = Arbin<int>(Arbin<E>(), 5, arbol10);
	Arbin<int> arbolraiz = Arbin<int>(Arbin<E>(), 2, arbol5);
	return arbolraiz;
}

template <class E>
Arbin<E> creaArbolHomogeneo(){
	Arbin<int> arbol7 = Arbin<int>(Arbin<E>(), 7, Arbin<E>());
	Arbin<int> arbol2 = Arbin<int>(Arbin<E>(), 2, Arbin<E>());
	Arbin<int> arbol10 = Arbin<int>(Arbin<E>(), 10, Arbin<E>());
	Arbin<int> arbol9 = Arbin<int>(Arbin<E>(), 9, Arbin<E>());
	Arbin<int> arbol3 = Arbin<int>(arbol7, 3, arbol2);
	Arbin<int> arbol5 = Arbin<int>(arbol9, 5, arbol10);
	Arbin<int> arbolraiz = Arbin<int>(arbol3, 2, arbol5);
	return arbolraiz;
}
/////////////////EJERCICIOS DE LA PRACTICA 2//////////////////////////
//-----------------homogeneo----------------
template <class T>
bool homogeneo(const Arbin<T> &ab){
	if (ab.esVacio())
		return true;
	if (esHojaExt(ab))
		return true;
	if (ab.hijoIz().esVacio() || ab.hijoDr().esVacio())
		return false;
	else return (true && homogeneo(ab.hijoIz()) && homogeneo(ab.hijoDr()));
}
//..........................................

//----------------degenerado----------------
template  <class E>
bool degenerado(const Arbin<E> &ab){
	if (ab.esVacio())
		return true;
	if (esHojaExt(ab))
		return true;
	if (ab.hijoIz().esVacio() && ab.hijoDr().esVacio())
		return false;
	if (ab.hijoIz().esVacio() && !ab.hijoDr().esVacio())
		return degenerado(ab.hijoDr());
	return degenerado(ab.hijoIz());
}
//..........................................

//-----------crea_Arbin_Pre_In--------------
template <class P>
ArbinPrac<P> crea_Arbin_Pre_In(List<P> &preorden, List<P> &inorden){
	List<P>::Iterator itPreorden = preorden.begin();
	List<P>::Iterator itInorden = inorden.begin();
	List<P> preordenIZ;
	List<P> inordenIZ;

	P n = itPreorden.elem();
	if (preorden.size() == 1)
		return ArbinPrac<P>(ArbinPrac<P>(), n, ArbinPrac<P>());
	else{
		itPreorden = preorden.erase(itPreorden);
		while (itInorden.elem() != n){
			preordenIZ.push_back(itPreorden.elem());
			inordenIZ.push_back(itInorden.elem());
			itPreorden = preorden.erase(itPreorden);
			itInorden = inorden.erase(itInorden);
			if (itInorden == inorden.end())
				n = itInorden.elem();

		}
		itInorden = inorden.erase(itInorden);
		if (!inorden.empty() && !preorden.empty())
			return ArbinPrac<P>(crea_Arbin_Pre_In(preordenIZ, inordenIZ), n, crea_Arbin_Pre_In(preorden, inorden));
		else if (preordenIZ.empty())
			return ArbinPrac<P>(ArbinPrac<P>(), n, crea_Arbin_Pre_In(preorden, inorden));
		else
			return ArbinPrac<P>(crea_Arbin_Pre_In(preordenIZ, inordenIZ), n, ArbinPrac<P>());
	}
}

//..........................................

//-----------crea_Arbin_Post_In-------------
template <class P>
Arbin<P> crea_Arbin_Post_In(List<P> postorden, List<P> inorden){
	List<P>::Iterator itP = postorden.begin();
	List<P>::Iterator p = postorden.begin();
	List<P>::Iterator itI = inorden.begin();
	List<P> postAux, inoAux;
	P n; // raiz
	bool ultimo = false;

	if (postorden.size() <= 1) // si solo hay un elemento, nos quedamos con el
		n = p.elem();

	else{
		while (!ultimo && p != postorden.end()) {
			// mientras no hayamos llegado al final de la lista, y cuando lleguemos nos quedamos con el
			n = p.elem();
			p.next();

			if (p == postorden.end())
				ultimo = true;
		}
	}
		if (postorden.size() == 1)
			return Arbin<P>(Arbin<P>(), n, Arbin<P>());
		else{
			while (itI.elem() != n){
				postAux.push_back(itP.elem());
				itP = postorden.erase(itP);
				inoAux.push_back(itI.elem());
				itI = inorden.erase(itI);
				if (itI == inorden.end())
					n = itI.elem();
			}

			itI = inorden.erase(itI);
			while (itP.elem() != n)
				itP.next();

			itP = postorden.erase(itP);
			if (!postorden.empty() && !postAux.empty()){
				return Arbin<P>(crea_Arbin_Post_In(postAux, inoAux), n, crea_Arbin_Post_In(postorden, inorden));
			}
			else if (postAux.empty())
				return Arbin<P>(Arbin<P>(), n, crea_Arbin_Post_In(postorden, inorden));
			else
				return Arbin<P>(crea_Arbin_Post_In(postAux, inoAux), n, Arbin<P>());
		}
}
/*
template <class P>
Arbin<P> crea_Arbin_Post_In(List<P> postorden, List<P> inorden){
	List<P> listaInIz;
	List<P> listaPostIz;
	List<P>::Iterator itP = postorden.begin();
	List<P>::Iterator it = inorden.begin();
	if (postorden.size() < 1 && inorden.size() < 1)
		cout << " listas vacias" << endl;
	else{
		P elem = postorden.back();
		if (postorden.size() == 1 && inorden.size() == 1){
			return Arbin<P>(Arbin<P>(), elem, Arbin<P>());
		}
		else{
			postorden.pop_back();
			P elemAux = it.elem();
			while (elemAux != elem){
				listaInIz.push_back(it.elem());
				inorden.pop_front();
				listaPostIz.push_back(itP.elem());
				postorden.pop_front();
				itP.next();
				it.next();
				elemAux = it.elem();
			}
			inorden.pop_front();
			if (!inorden.empty() && !postorden.empty())
				return Arbin<P>(crea_Arbin_Pre_In(listaPostIz, listaInIz), elem, crea_Arbin_Pre_In(postorden, inorden));
			else if (listaPostIz.empty())
				return Arbin<P>(Arbin<P>(), elem, crea_Arbin_Pre_In(postorden, inorden));
			else
				return Arbin<P>(crea_Arbin_Pre_In(listaPostIz, listaInIz), elem, Arbin<P>());
		}
	}
}
*/
//..........................................

//----------------maxNivel------------------
template <class M>
int maxNivel(const Arbin<M> &ab){
	Queue<Arbin<M>> cola = Queue<Arbin<M>>();
	if (!ab.esVacio()){
		cola.push_back(ab);
		return maxNivelAux(cola, 1, 1);
	}
	else throw exception();
}

template <class M>
int maxNivelAux(Queue<Arbin<M>> cola, unsigned int nMax, unsigned int nAct){
	unsigned int cont = nAct;
	nAct = 0;
	while (!cola.empty() && cont > 0){
		Arbin<M> ab = cola.front();
		cola.pop_front();
		cont--;
		if (!(ab.hijoIz().esVacio())){
			cola.push_back(ab.hijoIz());
			nAct++;
		}
		if (!(ab.hijoDr().esVacio())){
			cola.push_back(ab.hijoDr());
			nAct++;
		}
	}
	if (nMax < nAct)
		nMax = nAct;
	if (cola.empty())
		return nMax;
	else
		return maxNivelAux(cola, nMax, nAct);
}
//..........................................

//------------esHojaExt--------------------
template <class E>
bool esHojaExt(const Arbin<E> &ab){
	return (ab.hijoDr().esVacio() && ab.hijoIz().esVacio());
}
//.........................................

//----------fronteraExt-------------------
template <class E>
List<E> fronteraExt(const Arbin<E> &ab){
	List<E> lista;
	fronteraAuxExt(ab, lista);
	return lista;
}

template <class E>
void fronteraAuxExt(const Arbin<E> &ab, List<E> &lista){
	if (esHojaExt(ab)){
		lista.push_back(ab.raiz());
		return;
	}
	else{
		fronteraAuxExt(ab.hijoIz(), lista);
		fronteraAuxExt(ab.hijoDr(), lista);
	}
}
//........................................

//----------espejoExt-------------------
template <class E>
Arbin<E> espejoExt(const Arbin<E> &ab){
	if (ab.esVacio())
		return Arbin<E>();
	return Arbin<E>(espejoExt(ab.hijoDr()), ab.raiz(), espejoExt(ab.hijoIz()));
}
//........................................

//----------minElemExt-------------------
template <class E>
E minElemExt(const Arbin<E> &ab){
	if (ab.esVacio())
		throw InvalidAccessException();
	E minElem = ab.raiz();
	E minElemIz;
	E minElemDr;
	if (!esHojaExt(ab)){
		minElemIz = minElemExt(ab.hijoIz());
		minElemDr = minElemExt(ab.hijoDr());
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
//........................................

List<int> crea_lista_pre(){
	List<int> lista;
	lista.push_back(5);
	lista.push_back(2);
	lista.push_back(1);
	lista.push_back(3);
	lista.push_back(7);
	lista.push_back(6);
	lista.push_back(8);
	return lista;
}

List<int> crea_lista_in(){
	List<int> lista;
	lista.push_back(1);
	lista.push_back(2);
	lista.push_back(3);
	lista.push_back(5);
	lista.push_back(6);
	lista.push_back(7);
	lista.push_back(8);
	return lista;
}

List<int> crea_lista_pos(){
	List<int> lista;
	lista.push_back(1);
	lista.push_back(3);
	lista.push_back(2);
	lista.push_back(6);
	lista.push_back(8);
	lista.push_back(7);
	lista.push_back(5);
	return lista;
}

int main(){
	clock_t reloj;
	Arbin<int> arbolH = Arbin<int>(7);
	if (esHojaExt(arbolH))
		cout << "es hoja" << endl;
	else
		cout << "NO es hoja" << endl;
	cout << "----------------------------------------" << endl;
	cout << "Creacion de un arbol homogeneo" << endl;
	Arbin<int> ab = creaArbolHomogeneo<int>();
	printArbol(ab);
	if (homogeneo(ab))
		cout << "ES HOMOGENEO" << endl;
	cout << "el elemento minimo es: " << minElemExt(ab) << endl;
	cout << "el maximo nivel es: " << maxNivel(ab) << endl;
	cout << "----------------------------------------" << endl << endl;

	cout << "----------------------------------------" << endl;
	cout << "Creacion de un arbol degenerado" << endl;
	ab = creaArbolDegenerado<int>();
	printArbol(ab);
	if (degenerado(ab))
		cout << "ES DEGENERADO" << endl;
	cout << "el maximo nivel es: " << maxNivel(ab) << endl;
	cout << "----------------------------------------" << endl << endl;
	
	cout << "----------------------------------------------" << endl;
	cout << "Creacion arbol con lista en preorden e inorden" << endl;
	List<int> listaPre = crea_lista_pre();
	List<int> listaIn = crea_lista_in();
	Arbin<int> arbol = crea_Arbin_Pre_In(listaPre, listaIn);
	printArbol(arbol);
	cout << "el elemento minimo es: " << minElemExt(arbol) << endl;
	cout << "el espejo de este arbol es:" << endl;
	printArbol(espejoExt(arbol));
	cout << "..........................." << endl;
	cout << "lista de las hojas del arbol" << endl;
	List<int> lista = fronteraExt(arbol);
	for(int i = 0; i < lista.size(); i++)
		cout << "[" << lista.at(i) << "]  ";
	cout << endl;

	cout << "----------------------------------------------" << endl << endl;

	cout << "-----------------------------------------------" << endl;
	cout << "Creacion arbol con lista en postorden e inorden" << endl;
	List<int> listaPos = crea_lista_pos();
	List<int> listaIn2 = crea_lista_in();
	Arbin<int> arbol_post_in = crea_Arbin_Post_In(listaPos, listaIn2);
	printArbol(arbol_post_in);
	cout << "-----------------------------------------------" << endl << endl;


	cout << "::::::::::::::::::::::::::::::::::::::::::" << endl;
	cout << "::::::::::::FUNCIONES EXTERNAS::::::::::::" << endl;
	cout << "::::::::::::::::::::::::::::::::::::::::::" << endl;
	reloj = clock();
	cout << "Comprobacion hoja externa" << endl;
	ArbinPrac<int> arbolInternoExt = ArbinPrac<int>(7);
	if (esHojaExt(arbolInternoExt))
		cout << "es hoja" << endl;
	else
		cout << "NO es hoja" << endl;

	//espejo
	cout << "Comprobacion espejo externa" << endl;
	listaPre = crea_lista_pre();
	listaIn = crea_lista_in();
	ArbinPrac<int> arbolT= crea_Arbin_Pre_In(listaPre, listaIn);

	printArbol(espejoExt(arbolT));
	//frontera
	cout << "Comprobacion frontera externa" << endl;
	List<int> lista4 = fronteraExt(arbolT);
	for (int i = 0; i < lista4.size(); i++)
		cout << " [ " << lista4.at(i) << " ] ";
	cout << endl;

	//elemento minimo
	cout << "Comprobacion elemento minimo externo" << endl;
	cout << "el elemento minimo: " << minElemExt(arbolT) << endl << endl;




	reloj = clock() - reloj;
	cout << "EL TIEMPO QUE HA TARDADO ES: " << reloj << endl;
	//eshoja
	cout << "::::::::::::::::::::::::::::::::::::::::::" << endl;
	cout << "::::::::::::FUNCIONES INTERNAS::::::::::::" << endl;
	cout << "::::::::::::::::::::::::::::::::::::::::::" << endl;
	reloj = clock();
	cout << "Comprobacion hoja interna" << endl;
	ArbinPrac<int> arbolInterno = ArbinPrac<int>(7);
	if (arbolInterno.esHoja())
		cout << "es hoja" << endl;
	else
		cout << "NO es hoja" << endl;

	//espejo
	cout << "Comprobacion espejo interno" << endl;
	listaPre = crea_lista_pre();
	listaIn = crea_lista_in();
	ArbinPrac<int> arbolPrac = crea_Arbin_Pre_In(listaPre, listaIn);

	printArbol(arbolPrac.espejo());
	//frontera
	cout << "Comprobacion frontera interna" << endl;
	lista4 = arbolPrac.frontera();
		for(int i = 0; i < lista4.size(); i++)
		cout << " [ " << lista4.at(i) << " ] ";
		cout << endl;
	
	//elemento minimo
		cout << "Comprobacion elemento minimo interno" << endl;
		cout << "el elemento minimo: " << arbolPrac.minElem() << endl;

		reloj = clock() - reloj;
		cout << "EL TIEMPO QUE HA TARDADO ES: " << reloj << endl;
	system("PAUSE");
}

