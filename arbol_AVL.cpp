//Autores: Nicolás Arciniegas y Daniela Torres
//Taller 3: Árboles de búsqueda
//Objetivo:Evaluar la eficiencia de los árboles binarios ordenados en operaciones de búsqueda de elementos. En especial, se desea evaluar las habilidades del estudiante en el uso y análisis de las operaciones de inserción, eliminación y búsqueda de datos en árboles AVL.
//Desarrollo del taller: Consiste en utilizar implementación de árbol AVL para organizar unos datos de entrada y así identificar la mediana de esos dato.


#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class arbol_AVL {
  public:
    int dato;
    arbol_AVL *left;
    arbol_AVL *right;
    arbol_AVL *padre;
    int altura;
    arbol_AVL *a, *nuevo, *recorrer; //a=raiz
    arbol_AVL *padreAB; //padreAB: Mantiene un puntero al nodo anterior para referirse a el como el padre del nuevo nodo

    arbol_AVL(); //constructor por defecto
    arbol_AVL(int); //consructor con parametros
    int alturaAVL(arbol_AVL *); //calcula la altura del arbol
    int balancear(arbol_AVL *); //busca encontrar el factor de balanceo del arbol
    arbol_AVL *rotacionDerecha(arbol_AVL *); //realiza una rotacion hacia la derecha
    arbol_AVL *rotacionIzquierda(arbol_AVL *); //realiza una rotacion a la izquierda
    arbol_AVL *rotacionIzquierdaDerecha(arbol_AVL*); // realiza una rotacion del tipo izquierda derecha
    arbol_AVL *rotacionDerechaIzquierda(arbol_AVL *); //realiza rotacion derecha izquierda
    arbol_AVL *balance(arbol_AVL *); // balancea el arbol
    arbol_AVL *insertarAVL(arbol_AVL *, int);
    arbol_AVL *borrarAVL(arbol_AVL*, int); 
    void ImprimirInOrderAVL(arbol_AVL*);
    arbol_AVL *modificarArbol(arbol_AVL *, vector< struct infoarch> &);
};

arbol_AVL::arbol_AVL(int i) {
    dato = i;
    left = nullptr;
    right = nullptr;
    altura = 1;
}
int arbol_AVL::alturaAVL(arbol_AVL *a){
  int alt = 0;
  if(a != NULL){
    int alt_right= alturaAVL(a->right);
    int alt_left=alturaAVL(a->left);
    int alt_Max= max(alt_right, alt_left);
    alt=alt_Max+1;
  }
  return alt;
}
int arbol_AVL::balancear(arbol_AVL *a){
  int alt_right= alturaAVL(a->right);
  int alt_left=alturaAVL(a->left);
  int factor_balance= alt_left-alt_right;
  return factor_balance;
}
arbol_AVL *arbol_AVL::rotacionDerecha(arbol_AVL *a){
  arbol_AVL *aux;
  aux=a->right;
  a->right=aux->left;
  aux->left=a;
  return aux;
}
arbol_AVL *arbol_AVL::rotacionIzquierda(arbol_AVL *a){
  arbol_AVL *aux;
  aux=a->left;
  a->right=aux->right;
  aux->right=a;
  return aux;
}
arbol_AVL *arbol_AVL::rotacionDerechaIzquierda(arbol_AVL *a){
  arbol_AVL *aux;
  aux=a->right;
  a->right=rotacionIzquierda(aux);
  return rotacionDerecha(a);
}

arbol_AVL *arbol_AVL::rotacionIzquierdaDerecha(arbol_AVL *a){
  arbol_AVL *aux;
  aux=a->left;
  a->left=rotacionDerecha(a);
  return rotacionIzquierda(a);
}

arbol_AVL *arbol_AVL::balance(arbol_AVL *a){
  int factor_Balance = balancear(a);
  if(factor_Balance>1){
    if(balancear(a->left)>0)
      a=rotacionIzquierda(a);
    else 
      a=rotacionIzquierdaDerecha(a);  
  }else if (factor_Balance < -1){
    if(balancear(a->right)>0)
      a=rotacionDerechaIzquierda(a);
    else
    a=rotacionDerecha(a);
  }
  return a;
}
/*
arbol_AVL *arbol_AVL::insertarAVL(arbol_AVL *recorrer, arbol_AVL *nuevo, arbol_AVL *padreAB){
  if(a==NULL){
    a=nuevo;
    a->padre=NULL;
}else{
  if (nuevo->dato <= recorrer->dato){
    if(recorrer->left!=NULL){
      padreAB=recorrer->left;
      insertarAVL(recorrer->left, nuevo, padreAB);
    }else{
      recorrer->left=nuevo;
      nuevo->padre=padreAB;
      balance(a);
    }
} else if (nuevo->dato > recorrer->dato){
    if(recorrer->right!=NULL){
      padreAB=recorrer->right;
      insertarAVL(recorrer->right, nuevo, padreAB);
    }else{
      recorrer->right=nuevo;
      nuevo->padre=padreAB;
      balance(a);
    }
 }
}
}
*/
arbol_AVL *arbol_AVL::insertarAVL(arbol_AVL *a, int ndato){
  if(a==NULL)
    return a=new arbol_AVL(ndato);
  if (ndato < a->dato)
    a->left = insertarAVL(a->left, ndato);
  else if (ndato >a->dato)
    a->right = insertarAVL(a->right, ndato);
  else return a;
  int balance = balance(a);
  if(balance >1 && ndato <a->left->dato)
    return rotacionDerecha(a);
  if (balance <-1 && ndato>a->right->dato)
    return rotacionIzquierda(a);
  if (balance > 1 &&ndato > a->left->dato){
    a->left =rotacionIzquierda(a->left);
    return rotacionDerecha(a);
  }
  if( balance <-1 && ndato < a->right->dato){
    a->right = rotacionDerecha(a->right);
    return rotacionIzquierda(a);
  }
return a;

}

arbol_AVL *arbol_AVL::borrarAVL(arbol_AVL *a, int numeroBorrar){
  arbol_AVL *aux;
  if(a==NULL)
    return NULL;
  else
    if(numeroBorrar > a->dato){
      a->right=borrarAVL(a->right, numeroBorrar);
     balance(a);
    }
  else if (numeroBorrar < a->dato){
    a->left=borrarAVL(a->left, numeroBorrar);
    balance(a);
  }
  else if (a->right !=NULL)
  {
    aux=a->right;
    while(aux->left!=NULL)
      aux=aux->left;

    a->dato= aux-> dato;
    a->right = borrarAVL(a->right, aux->dato);
    balance(a);
  }
  else return(a->left);
}
  
void arbol_AVL::ImprimirInOrderAVL(arbol_AVL *a){
  if (a != NULL)
  {
    ImprimirInOrderAVL(a->left);
    cout<<a->dato<<"=>";
    ImprimirInOrderAVL(a->right);
  }
} 

struct infoarch{
string accion;
int valor;
};

arbol_AVL arbol_AVL::*modificarArbol(arbol_AVL *a, vector<infoarch> &info){
  int aux;
  string elim,add;
  add="A";
  elim="E";
  
  for(auto data: info ){
    cout<<"algo pa que no salga error"<<endl;
    cout<<data.accion<<data.valor<<endl;
    if((aux=add.compare(data.accion))==0){//si la accion es igual a "A" significa que se va a agregar ese elemento al arbolAVL, si es diferente, se asume que sera igual a "E", entonces significa que toca eliminar el elemento y se asume que no se ingresaran valores diferentes a estos
      //ACA LLAMAR FUNCION INSERTAR
      a->insertarAVL(a, data.valor);
    }
    else{
      a->borrarAVL(a, data.valor);
    }
    }
  return NULL;  //para que no salgan errores de que debe retornar algo
  }
//sacar info del archivo


void sacar_info(vector<infoarch> &informacion){
  ifstream arch ("entrada.txt");
  infoarch aux;
  string linea, linea_aux, linea_aux3;
  vector<string> vector_aux, vector_aux2;
  if (arch.is_open()){
    while(getline(arch, linea))
      vector_aux.push_back(linea);

    for(string info: vector_aux){
      linea_aux=info;
      stringstream linea_aux2(linea_aux);
      while(getline(linea_aux2, linea_aux3,' ')){
        vector_aux2.push_back(linea_aux3);
      }
      aux.accion=vector_aux2[0];
      aux.valor=stoi(vector_aux2[1]);
      cout<<aux.accion<<" "<<aux.valor<<endl;
      informacion.push_back(aux);
      vector_aux2.clear();
    }
  } else{
    cout<<"no se pudo abrir el archivo"<<endl;
  }
  arch.close();
}

int main(){
vector<infoarch> informacion;
sacar_info(informacion);
cout<<informacion.size();
arbol_AVL *arbolito =new arbol_AVL();

}