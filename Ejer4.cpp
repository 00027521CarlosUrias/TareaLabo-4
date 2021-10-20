#include <iostream>
#include <string>
using namespace std;

struct Lista{
    int ID;
    string nombre;
    string perfil;   
};
Lista solicitarLista(void){
    Lista p;
    cout << "Id: ";
    cin >> p.ID;cin.ignore();
    cout << "Nombre del usuario: ";
    getline(cin, p.nombre);
    cout << " Tipo de Perfil del Usuario: ";
    getline(cin, p.perfil);
    return p;
}

void mostrarLista(Lista p){
    cout << "Id: " << p.ID<<endl;
    cout << "Nombre de usuario: " << p.nombre<<endl;
    cout << "Perfil: " << p.perfil<< endl;
}

typedef Lista T;
const T noValido = {0,"",""};

struct nodo{
    T dato;
    nodo *sig;
    nodo *ant;
};

class ListaDoble{
    private:
        nodo *pInicio;
    public:
        ListaDoble();
        ~ListaDoble();
        void insInicio(T);
        void insFinal(T);
        void mostrarListaDirectoIter(void);
        void mostrarListaDIIter(void);
        void deleteItem(T);
        bool empty(void);
};

ListaDoble::ListaDoble(void){
    pInicio = NULL;
}

ListaDoble::~ListaDoble(void){
    nodo *p;
    while(pInicio){
        p = pInicio;
        pInicio = pInicio->sig;
        delete p;
    }
}

void ListaDoble::insInicio(T dato){
    nodo *nuevo = new nodo;
    nuevo->dato = dato;
    nuevo->sig = pInicio;
    if(pInicio != NULL)
        pInicio->ant = nuevo;
    pInicio = nuevo;
}

void ListaDoble::insFinal(T dato){
    nodo *nuevo = new nodo;
    nuevo->dato = dato;
    if(!pInicio){
        pInicio = nuevo;
        pInicio->sig = pInicio->ant = NULL;
    }
    else{
        nodo *saltarin = pInicio;
        while(saltarin->sig != NULL)
            saltarin = saltarin->sig;
        saltarin->sig = nuevo;
        nuevo->ant = saltarin;
        nuevo->sig = NULL;
    }
}

void ListaDoble::mostrarListaDirectoIter(void){
    nodo *saltarin = pInicio;
    while(saltarin != NULL){
        mostrarLista(saltarin->dato);
        saltarin = saltarin->sig;
    }
}

void ListaDoble::mostrarListaDIIter(void){
    if(!pInicio)
        return;
    nodo *p = pInicio;
    nodo *q = NULL;
    while(p){
        q = p;
        p = p->sig;
    }
    while(q){
        mostrarLista(q->dato);
        q = q->ant;
    }
}

void ListaDoble::deleteItem(T datoB){
    if(!pInicio){ 
        cout << "Actualmente no hay usuarios en la lista." << endl;
    }
    else{ 
        nodo *saltarin = pInicio;
        while(saltarin && (saltarin->dato).nombre.compare(datoB.nombre)!=0) 
            saltarin = saltarin->sig; 
        if(!saltarin) 
            cout << "El usuario no está en la lista ingresada" << endl;
        else{ 
            if(!saltarin->ant && saltarin->sig){ 
                pInicio = pInicio->sig;
                pInicio->ant = NULL;
                delete saltarin;
            }
            else
                if(saltarin->ant && !saltarin->sig){
                    saltarin->ant->sig = NULL;
                    delete saltarin;
                }
                else
                    if(saltarin->ant && saltarin->sig){
                        saltarin->ant->sig = saltarin->sig;
                        saltarin->sig->ant = saltarin->ant;
                        delete saltarin;
                    }
                    else{
                        pInicio = NULL;
                        delete saltarin;
                    }
            cout << "Usuario eliminado exitosamente de la lista ingresada!" << endl;
        }
    }
}
bool ListaDoble::empty(void){
    return pInicio == NULL;
}

int menu(){
    int opcion = 0;
    cout << endl << "1) Agregar al principio." << endl;
    cout << "2) Agregar de ultimo." << endl;
    cout << "3) Mostrar al derecho." << endl;
    cout << "4) Mostrar al reves." << endl;
    cout << "5) Eliminar usuario de la lista ingresada"<<endl;
    cout << "6) Salir del programa." << endl;
    cout << "Opcion: ";
    cin >> opcion; cin.ignore();
    cout<<endl;
    return opcion;
}

int main(void){
    ListaDoble objListaDoble;
    Lista p;
    bool continuar = true;
do{
        switch(menu()){
            case 1: 
                p = solicitarLista();
                objListaDoble.insInicio(p);
                cout <<"Usuario almacenado en la lista exitosamente!" << endl;
                break;
            case 2: 
                p = solicitarLista();
                objListaDoble.insFinal(p);
                cout <<"Usuario almacenado exitosamente!" << endl;
                break;
            
            case 3: 
                objListaDoble.mostrarListaDirectoIter();
                break;
            case 4: 
                objListaDoble.mostrarListaDIIter();
                break;
            case 5: 
                  if(objListaDoble.empty())
                    cout << "No hay usuarios por eliminar" << endl;
                else{
                    p = solicitarLista();
                    objListaDoble.deleteItem(p);
                }
                break;
            case 6: 
                continuar = false;
                break;
            default: 
                cout << "La opcion no es valida, favor intente de nuevo." << endl;
                break;
        }
    }while(continuar);
    return 0;
}