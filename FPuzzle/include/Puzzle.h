#ifndef PUZZLE_H
#define PUZZLE_H
#include "stdlib.h"
#include "list"
#include "algorithm"
#include "vector"
#include "map"
#include "ArbolDeJuego.h"

using namespace std;

enum Posiciones{ARRIBAIZQUIERDA,ARRIBA,ARRIBADERECHA,DERECHA,ABAJODERECHA,ABAJO,ABAJOIZQUIERDA,IZQUIERDA,CENTRO};

class Puzzle;

void desple(Puzzle actual, list<tuple<int,Puzzle>>&resultado, Puzzle anterior, int valorIncorrecto);

class Puzzle
{
    public:
        class Square{
            public:
                Square();
                Square(int,int,int,int,string);
                virtual ~Square(){};
                bool operator!=(Square second){
                    if(fil == second.fil and col == second.col and valor == second.valor and n == second.n and image == second.image)return false;
                    return true;
                };
                void _llenarValores(int,int,int,int,string);
                int getValorReal();
                int getPosicion();
                int fil;
                int col;
                int valor;
                int n;
                string image;
        };
        Puzzle();
        Puzzle(int,string);
        Puzzle(int**,int,string);
        Puzzle(map<int,map<int,Square>>,string,int,int,int);
        void next();
        map<int,map<int,Square>> getMatriz(){return matriz;};
        void print();
        int estaResuelto();
        void Resolver();
        Puzzle copiarPuzzle();
        tuple<int,int> getVacio();
        int getValor(int,int);
        void swapValores(int,int);
        list<Square> getVecinos(int,int,int,int);
        int vacioFil;
        int vacioCol;
        virtual ~Puzzle();
        string name;
    protected:
    private:
        map<int,map<int,Square>> matriz;
        ///int getMejorSolucion(list<Square *>, Square *&);
        int resuelto;
        void nextPorPaso(list<Puzzle>&);
        ArbolDeJuego<Puzzle> juego;
};


Puzzle::Puzzle(map<int,map<int,Square>> matriz,string name, int fil,int col, int resuelto){
    this->matriz = matriz;
    this->name = name;
    vacioCol = col;
    vacioFil = fil;
    this->resuelto = resuelto;
}

void Puzzle::swapValores(int fil, int col){
    Square nuevoVacio = matriz[fil][col];
    Square atras = matriz[vacioFil][vacioCol];
    nuevoVacio.fil = vacioFil;
    nuevoVacio.col = vacioCol;
    atras.fil = fil;
    atras.col = col;
    /*
    swap(matriz[fil][col],matriz[vacioFil][vacioCol]);
    matriz[fil][col].fil = fil;
    matriz[fil][col].fil = col;
    matriz[vacioFil][vacioCol].fil = vacioFil;
    matriz[vacioFil][vacioCol].col = vacioCol;
    */
    matriz[vacioFil][vacioCol] = nuevoVacio;
    matriz[fil][col] = atras;
    vacioFil = fil;
    vacioCol = col;
}

int Puzzle::getValor(int fil, int col){
    Square vecino = matriz[fil][col];
    Square vacio = matriz[vacioFil][vacioCol];
    if(vecino.getValorReal() == vecino.valor)return 1;
    if(vacio.getValorReal() == vecino.valor)return -1;
    return 0;
}

tuple<int,int> Puzzle::getVacio(){
    return make_tuple(vacioFil,vacioCol);
}

int Puzzle::estaResuelto(){
    return resuelto;
}

void Puzzle::print(){
    for(int i = 1; i <= matriz.size(); i++){
        for(int j = 1; j <= matriz.size(); j++){
            cout<<matriz[i][j].valor<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

list<Puzzle::Square> Puzzle::getVecinos(int filS, int colS, int filAnterior, int colAnterior){
    Square s  = matriz[filS][colS];
    cout<<"FIL->"<<s.fil<<endl;
    cout<<"COL->"<<s.col<<endl;
    Square anterior;
    bool flag;
    if(filAnterior == -1 or colAnterior == -1)flag = false;
    else{
        anterior = matriz[filAnterior][colAnterior];
        flag = true;
    }
    int pos = s.getPosicion();
    list<Square> vecinos;
    switch(pos){
        case ARRIBAIZQUIERDA:
            if(!flag or matriz[s.fil][s.col + 1] != anterior) vecinos.push_back(matriz[s.fil][s.col + 1]);
            if(!flag or matriz[s.fil + 1][s.col] != anterior) vecinos.push_back(matriz[s.fil + 1][s.col]);
            break;
        case ARRIBA:
            if(!flag or matriz[s.fil][s.col - 1] != anterior) vecinos.push_back(matriz[s.fil][s.col - 1]);
            if(!flag or matriz[s.fil][s.col + 1] != anterior) vecinos.push_back(matriz[s.fil][s.col + 1]);
            if(!flag or matriz[s.fil + 1][s.col] != anterior) vecinos.push_back(matriz[s.fil + 1][s.col]);
            break;
        case ARRIBADERECHA:
            if(!flag or matriz[s.fil][s.col - 1] != anterior) vecinos.push_back(matriz[s.fil][s.col - 1]);
            if(!flag or matriz[s.fil + 1][s.col] != anterior) vecinos.push_back(matriz[s.fil + 1][s.col]);
            break;
        case DERECHA:
            if(!flag or matriz[s.fil][s.col - 1] != anterior) vecinos.push_back(matriz[s.fil][s.col - 1]);
            if(!flag or matriz[s.fil - 1][s.col] != anterior) vecinos.push_back(matriz[s.fil - 1][s.col]);
            if(!flag or matriz[s.fil + 1][s.col] != anterior) vecinos.push_back(matriz[s.fil + 1][s.col]);
            break;
        case ABAJODERECHA:
            if(!flag or matriz[s.fil][s.col - 1] != anterior) vecinos.push_back(matriz[s.fil][s.col - 1]);
            if(!flag or matriz[s.fil - 1][s.col] != anterior) vecinos.push_back(matriz[s.fil - 1][s.col]);
            break;
        case ABAJO:
            if(!flag or matriz[s.fil][s.col - 1] != anterior) vecinos.push_back(matriz[s.fil][s.col - 1]);
            if(!flag or matriz[s.fil - 1][s.col] != anterior) vecinos.push_back(matriz[s.fil - 1][s.col]);
            if(!flag or matriz[s.fil][s.col + 1] != anterior) vecinos.push_back(matriz[s.fil][s.col + 1]);
            break;
        case ABAJOIZQUIERDA:
            if(!flag or matriz[s.fil - 1][s.col] != anterior) vecinos.push_back(matriz[s.fil - 1][s.col]);
            if(!flag or matriz[s.fil][s.col + 1] != anterior) vecinos.push_back(matriz[s.fil][s.col + 1]);
            break;
        case IZQUIERDA:
            if(!flag or matriz[s.fil - 1][s.col] != anterior) vecinos.push_back(matriz[s.fil - 1][s.col]);
            if(!flag or matriz[s.fil][s.col + 1] != anterior) vecinos.push_back(matriz[s.fil][s.col + 1]);
            if(!flag or matriz[s.fil + 1][s.col] != anterior) vecinos.push_back(matriz[s.fil + 1][s.col]);
            break;
        case CENTRO:
            if(!flag or matriz[s.fil][s.col - 1] != anterior) vecinos.push_back(matriz[s.fil][s.col - 1]);
            if(!flag or matriz[s.fil - 1][s.col] != anterior) vecinos.push_back(matriz[s.fil - 1][s.col]);
            if(!flag or matriz[s.fil][s.col + 1] != anterior) vecinos.push_back(matriz[s.fil][s.col + 1]);
            if(!flag or matriz[s.fil + 1][s.col] != anterior) vecinos.push_back(matriz[s.fil + 1][s.col]);
            break;
    }
    return vecinos;
}

/*
int Puzzle::getMejorSolucion(list<Square *> vecinos, Square *& resultado){
    resultado = nullptr;
    for(Square * s : vecinos){
        if(vacio->getValorReal() == s->valor){
            resultado = s;
            return -1;
        }
        if(s->getValorReal() != s->valor and !resultado){
            resultado = s;
        }
    }
    if(!resultado){
        resultado = vecinos.front();
        return 1;
    }
    return 0;
}
*/

void Puzzle::Resolver(){
    cout<<"Tablero al inicio"<<endl;
    cout<<"Nivel->"<<juego.nivel()<<endl;
    cout<<"Size->"<<juego.size()<<endl;
    print();
    while(resuelto){
        next();
    }
}

void Puzzle::nextPorPaso(list<Puzzle>& camino){
    cout<<"ENCONTRO CAMINO"<<endl<<endl;
    for(Puzzle p : camino){
        matriz = p.getMatriz();
        ///Lentearlo;
        cout<<"NEXT"<<endl;
        print();
        vacioFil = p.vacioFil;
        vacioCol = p.vacioCol;
    }
}

void Puzzle::next(){
    list<Puzzle> camino;
    while(!juego.desplegar(camino,resuelto)){
        camino.clear();
    }
    nextPorPaso(camino);
    cout<<"ACTUAAAAAAAAAAAAAAAAAALLLLLLLLL"<<endl;
    cout<<"RESUELTO->"<<resuelto<<endl;
    print();
    char t;
    cin>>t;
}

int Puzzle::Square::getPosicion(){
    if(fil == 1){
        if(col == 1){
            return ARRIBAIZQUIERDA;
        }
        else if(col == n){
            return ARRIBADERECHA;
        }
        else{
            return ARRIBA;
        }
    }
    else if(col == n){
        if(fil == n){
            return ABAJODERECHA;
        }
        else{
            return DERECHA;
        }
    }
    else if(fil == n){
        if(col == 1){
            return ABAJOIZQUIERDA;
        }
        else{
            return ABAJO;
        }
    }
    else if(col == 1){
        return IZQUIERDA;
    }
    else return CENTRO;
}

Puzzle::Puzzle(int **m,int n,string name){
    void (*des)(Puzzle, list<tuple<int,Puzzle>>&, Puzzle, int);
    des = desple;
    juego = ArbolDeJuego<Puzzle>(-1,1,des,n);
    this->name = name;
    resuelto = 0;
    for(int i = 0; i < n;i++){
        for(int j = 0; j < n; j++){
            matriz[i+1][j+1] = Square(i+1,j+1,m[i][j],n,name);
            if(m[i][j] == n*n){
                vacioFil = i+1;
                vacioCol = j+1;
            }
            if(m[i][j] != matriz[i+1][j+1].getValorReal()) resuelto++;
        }
    }
    Puzzle nuevo(matriz,name,vacioFil,vacioCol,resuelto);
    juego.insert(nuevo);
    cout<<"hola"<<endl;
}

Puzzle::Puzzle(int n, string name){
    void (*des)(Puzzle, list<tuple<int,Puzzle>>&, Puzzle, int);
    des = desple;
    juego = ArbolDeJuego<Puzzle>(-1,1,des,n);
    resuelto = 0;
    this->name = name;
    vector<int> valores;
    for(int i = 1; i <= n * n; i++){
        valores.push_back(i);
    }
    for(int i = 1; i <= n; i++){
        if(valores.empty())break;
        for(int j = 1; j <= n; j++){
            ///FALTA PONER LA IMAGEN;
            int h = rand() % valores.size();
            int numero = valores[h];
            matriz[i][j] = Square(i,j,numero,n,name);
            if(numero == n * n){
               vacioFil = i;
               vacioCol = j;
            }
            if(numero != matriz[i][j].getValorReal()) resuelto++;
            valores.erase(valores.begin() + h);
        }
    }
    Puzzle nuevo(matriz,name,vacioFil,vacioCol,resuelto);
    juego.insert(nuevo);
    cout<<"hola"<<endl;
}

Puzzle::Puzzle(){
    name = "default";
}

int Puzzle::Square::getValorReal(){
    return n * (fil - 1) + col;
}

void Puzzle::Square::_llenarValores(int fil, int col , int val, int n, string img){
    this->fil = fil;
    this->col = col;
    this->n = n;
    valor = val;
    image = img;
}

Puzzle::Square::Square(){
    image = "noHayImagen";
    n = 0;
    fil = 0;
    col = 0;
    valor = -1;
}



Puzzle::Square::Square(int fil, int col, int val,int n, string img){
    this->fil = fil;
    this->col = col;
    this->n = n;
    valor = val;
    image = img;
}

Puzzle::~Puzzle(){
   /* for(int i = 1; i <= matriz.size(); i++){
        for(int j = 1; j <= matriz.size(); j++){
            delete matriz[i][j];
        }
    }
    */
}



void desple(Puzzle actual, list<tuple<int,Puzzle>>&resultado, Puzzle anterior, int valorIncorrecto){
    int filAnte;
    int colAnte;
    if(anterior.name == "default"){
        filAnte = -1;
        colAnte = -1;
    }
    else{
        filAnte = anterior.vacioFil;
        colAnte = anterior.vacioCol;
    }
    list<Puzzle::Square> vecinos = actual.getVecinos(actual.vacioFil,actual.vacioCol,filAnte,colAnte);
    Puzzle temp = actual;
    cout<<"DESPLEGANDO"<<endl<<endl;
    actual.print();
    for(Puzzle::Square s : vecinos){
        cout<<"VECINO->"<<s.valor<<endl;
        actual = temp;
        int valor = actual.getValor(s.fil,s.col);
        if(valor != valorIncorrecto){
            actual.swapValores(s.fil,s.col);
            cout<<"DESPLIEGUE"<<endl<<endl;
            actual.print();
            resultado.push_back(make_tuple(valor,actual));
        }
    }
}


#endif // PUZZLE_H
