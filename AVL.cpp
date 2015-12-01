#include "AVL.h"
#include <QtMath>

NodoAVL::NodoAVL(int dato)
{
    mDato = dato;
    mIzq = nullptr;
    mDer = nullptr;
    mAltura = 1;
}

int NodoAVL::getAltura(NodoAVL *nodo)
{
    if (nodo == nullptr) {
        return 0;
    }
    return nodo->mAltura;
}

NodoAVL *NodoAVL::rotaDer()
{
    auto x = mIzq;
    auto t2 = x->mDer;

    // realiza rotación
    x->mDer = this;
    mIzq = t2;

    // actualiza alturas
    mAltura = 1 + qMax(NodoAVL::getAltura(mIzq), NodoAVL::getAltura(mDer));
    x->mAltura = 1 + qMax(NodoAVL::getAltura(x->mIzq),
                          NodoAVL::getAltura(x->mDer));

    // regresa raíz nueva
    return x;
}

NodoAVL *NodoAVL::rotaIzq()
{
    auto y = mDer;
    auto t2 = y->mIzq;

    // realiza rotación
    y->mIzq = this;
    mDer = t2;

    // actualiza alturas
    mAltura = 1 + qMax(NodoAVL::getAltura(mIzq), NodoAVL::getAltura(mDer));
    y->mAltura = 1 + qMax(NodoAVL::getAltura(y->mIzq),
                          NodoAVL::getAltura(y->mDer));

    // regresa raíz nueva
    return y;
}

int NodoAVL::getFE(NodoAVL *nodo)
{
    if (nodo == nullptr) {
        return 0;
    }
    return NodoAVL::getAltura(nodo->mIzq) - NodoAVL::getAltura(nodo->mDer);
}

NodoAVL *NodoAVL::nodoMenorValor()
{
    // dado un árbol de búsqueda no vacío, regresa el nodo
    // con el valor del dato más pequeño encontrado en ese árbol.
    // El árbol entero no necesita ser buscado
    auto actual = this;

    // bucle hacia abajo para encontrar la hoja más a la izquierda
    while (actual->getIzq() != nullptr) {
        actual = actual->getIzq();
    }
    return actual;
}

AVL::AVL()
{
    mRaiz = nullptr;
}

NodoAVL *AVL::inserta(NodoAVL *nodo, int dato)
{
    // realiza la rotación de árbol binario de búsqueda
    if (nodo == nullptr) {
        return new NodoAVL(dato);
    }
    if (dato < nodo->getDato()) {
        nodo->setIzq(inserta(nodo->getIzq(), dato));
    } else {
        nodo->setDer(inserta(nodo->getDer(), dato));
    }

    // actualiza la altura de este nodo ancestro
    nodo->setAltura(1 + qMax(NodoAVL::getAltura(nodo->getIzq()),
                             NodoAVL::getAltura(nodo->getDer())));
    int fe = NodoAVL::getFE(nodo);

    // si este nodo se desequilibra, entonces hay 4 casos

    // caso izq izq
    if (fe > 1 && dato < nodo->getIzq()->getDato()) {
        return nodo->rotaDer();
    }

    // caso der der
    if (fe < -1 && dato > nodo->getDer()->getDato()) {
        return nodo->rotaIzq();
    }

    // caso izq der
    if (fe > 1 && dato > nodo->getIzq()->getDato()) {
        nodo->setIzq(nodo->getIzq()->rotaIzq());
        return nodo->rotaDer();
    }

    // caso der izq
    if (fe < -1 && dato < nodo->getDer()->getDato()) {
        nodo->setDer(nodo->getDer()->rotaDer());
        return nodo->rotaIzq();
    }

    // regresa el nodo sin cambiar
    return nodo;
}

NodoAVL *AVL::elimina(NodoAVL *raiz, int dato)
{
    // realiza la eliminación normal
    if (raiz == nullptr) {
        return nullptr;
    }

    // si el dato para borrar es más pequeño que el dato de la raíz
    // entonces está en el subárbol izquierdo
    if (dato < raiz->getDato()) {
        raiz->setIzq(elimina(raiz->getIzq(), dato));

    // si el dato para borrar es más grande que el dato de la raíz
    // entonces estpa en el subárbol derecho
    } else if (dato > raiz->getDato()) {
        raiz->setDer(elimina(raiz->getDer(), dato));

    // si el dato es el mismo que el dato de la raíz, entonces este es el nodo
    // para borrar
    } else {
        // nodo con un solo hijo o ninguno
        if (raiz->getIzq() == nullptr || raiz->getDer() == nullptr) {
            auto temp = raiz->getIzq() ? raiz->getIzq() : raiz->getDer();

            // caso sin hijo
            if (temp == nullptr) {
                temp = raiz;
                raiz = nullptr;

            // caso con un solo hijo
            } else {
                // copia el contenido del hijo no vacío
                *raiz = *temp;
            }
            delete temp;
        } else {
            // nodo con dos hijos
            // obtiene el sucesor en inorden
            // el más pequeño en el subárbol derecho
            auto temp = raiz->getDer()->nodoMenorValor();

            // copia el dato del sucesor en inorden a este nodo
            raiz->setDato(temp->getDato());

            // elimina el sucesor en inorden
            raiz->setDer(elimina(raiz->getDer(), temp->getDato()));
        }
    }

    // si el árbol tenía solo un nodo entonces adiós
    if (raiz == nullptr) {
        return nullptr;
    }

    // actualiza la altura del nodo actual
    raiz->setAltura(1 + qMax(NodoAVL::getAltura(raiz->getIzq()),
                             NodoAVL::getAltura(raiz->getDer())));

    // obtiene el factor de equilibrio de este nodo
    // para saber si este nodo se desequilibró
    int fe = NodoAVL::getFE(raiz);

    // si este nodo se desequilibró, entonces hay 4 casos

    // caso izq izq
    if (fe > 1 && NodoAVL::getFE(raiz->getIzq()) >= 0) {
        return raiz->rotaDer();
    }

    // caso izq der
    if (fe > 1 && NodoAVL::getFE(raiz->getIzq()) < 0) {
        raiz->setIzq(raiz->getIzq()->rotaIzq());
        return raiz->rotaDer();
    }

    // caso der der
    if (fe < -1 && NodoAVL::getFE(raiz->getDer()) <= 0) {
        return raiz->rotaIzq();
    }

    // caso der izq
    if (fe < -1 && NodoAVL::getFE(raiz->getDer()) > 0) {
        raiz->setDer(raiz->getDer()->rotaDer());
        return raiz->rotaIzq();
    }

    return raiz;
}

void AVL::inserta(int dato)
{
    mRaiz = inserta(mRaiz, dato);
}

void AVL::elimina(int dato)
{
    mRaiz = elimina(mRaiz, dato);
}
