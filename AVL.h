#ifndef AVL_H
#define AVL_H

class NodoAVL
{
public:
    NodoAVL(int dato);
    int getDato() const { return mDato; }
    NodoAVL *getIzq() const { return mIzq; }
    NodoAVL *getDer() const { return mDer; }
    void setDato(int dato) { mDato = dato; }
    void setAltura(int altura) { mAltura = altura; }
    void setIzq(NodoAVL *izq) { mIzq = izq; }
    void setDer(NodoAVL *der) { mDer = der; }
    NodoAVL *rotaDer();
    NodoAVL *rotaIzq();
    NodoAVL *nodoMenorValor();
    static int getAltura(NodoAVL *nodo);
    static int getFE(NodoAVL *nodo);
private:
    int mDato;
    int mAltura;
    NodoAVL *mIzq;
    NodoAVL *mDer;
};

class AVL
{
public:
    AVL();
    void inserta(int dato);
    void elimina(int dato);
    NodoAVL *getRaiz() const { return mRaiz; }
    template<typename F> void preorden(NodoAVL *raiz, const F &f);
    template<typename F> void postorden(NodoAVL *raiz, const F &f);
    template<typename F> void inorden(NodoAVL *raiz, const F &f);
private:
    NodoAVL *inserta(NodoAVL *nodo, int dato);
    NodoAVL *elimina(NodoAVL *raiz, int dato);

    NodoAVL *mRaiz;
};

template<typename F> void AVL::preorden(NodoAVL *raiz, const F &f)
{
    if (raiz != nullptr) {
        f(raiz);
        preorden(raiz->getIzq(), f);
        preorden(raiz->getDer(), f);
    }
}

template<typename F> void AVL::postorden(NodoAVL *raiz, const F &f)
{
    if (raiz != nullptr) {
        postorden(raiz->getIzq(), f);
        postorden(raiz->getDer(), f);
        f(raiz);
    }
}

template<typename F> void AVL::inorden(NodoAVL *raiz, const F &f)
{
    if (raiz != nullptr) {
        inorden(raiz->getIzq(), f);
        f(raiz);
        inorden(raiz->getDer(), f);
    }
}

#endif // AVL_H
