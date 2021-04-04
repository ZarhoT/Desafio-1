#include <iostream>
#include <list>
#include <stack>
#include <queue>
#include <fstream>
using namespace std;
#define N       9

class Action{
public:
    int value;
    int col,row;
}; 

class State{
public:
    int table[N][N];
    list<Action> steps;
    
    //Contructor.
    State(int sudoku[]){
        int k=0,j=k/9,i=k-9*j;
        while(k<N*N){
            table[j][i] = sudoku[k];
            k++;
            j = k/9;
            i = k - 9*j;
        }
    }

    //Metodo para imprimir el contenido del estado actual del sudoku.
    void printTable(){
        int i,j;
        for(i=0;i<N;i++){
            for(j=0;j<N;j++){
                cout << table[i][j] << " ";
            }
            cout << "\n";
        }
    }

    //Metodo que aplica la accion al estado.
    State transition(Action& action){
        State new_state=*this;
        new_state.table[action.col][action.row] = action.value;
        new_state.steps.push_back(action);
        return new_state;
    }

    //Metodo para verificar si el estado es el final.
    bool is_final_state(){
        int i, j;
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
                //Si encuentra una casilla vacia se detendra de inmediato.
                if(table[i][j] == 0){
                    return false;
                }
            }
        }
        if(!is_valid_state()){
            return false;
        }
        return true;
    }

    bool is_valid_state(){
        int z=0,y=0;
        int comienzoVertical;
        int comienzoHorizontal;
        int i,j,k;
        //Verificación de filas y columnas
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(table[i][j] != 0){
                    z=j+1;
                    y=i+1;
                    while(z<9 && y<9){
                        if(table[i][j]==table[i][z] || table[i][j]==table[y][j]){
                            return false;
                        }
                        z++;
                        y++;
                    }
                }
            }
        }
        //Verificación sub matrices
        for(comienzoVertical=0; comienzoVertical<9; comienzoVertical=comienzoVertical+3){
            for(comienzoHorizontal=0; comienzoHorizontal<9; comienzoHorizontal=comienzoHorizontal+3){
                for(i=comienzoVertical; i<comienzoVertical+3; i++){
                    for(j=comienzoHorizontal; j<comienzoHorizontal+3; j++){
                        for(k=i; k<comienzoVertical+3; k++){
                            for(z=j+1; z<comienzoHorizontal+3; z++){  
                                if(table[i][j] != 0){
                                    if(table[i][j] == table[k][z]){
                                        return false;
                                    }
                                }  
                            }
                        }
                    }
                }  
            }
        }
    
        return true;
    }

    //Metodo que encuentra los distintos estados que le siguen al actual
    list<Action> get_actions(){
        int i, j, z, i_pos, j_pos;
        list<Action> actions;
        int menor=9;
        int max_actions;
        //En el proceso de obtener las acciones, primero busca la casilla con menos opciones
        for(i=0;i<N;i++){
            for(j=0;j<N;j++){
                if(table[i][j]==0){
                    max_actions=0;
                    for(z=1;z<10;z++){
                        table[i][j]=z;
                        if(is_valid_state()){
                            max_actions++;
                        }
                    }
                    table[i][j]=0;
                    //Cuando encuentra la mejor opcion la guarda
                    if(max_actions < menor){
                        menor = max_actions;
                        i_pos = i;
                        j_pos = j;
                    }
                }
            }
        }
        for(z=1;z<10;z++){
            table[i_pos][j_pos]=z;
            if(is_valid_state()){
                Action a;
                a.col = i_pos;
                a.row = j_pos;
                a.value = z;
                actions.push_back(a);
            }
        }
        table[i][j]=0;
        return actions;
    }

};

//Busqueda en profundidad.
int DFS(State& initial){
    stack<State> S;
    int steps=0;
    int iter=0;
    S.push(initial);
    while(!S.empty()){
        iter++;
        State s= S.top(); S.pop();
        if(s.steps.size() > steps){
            steps = s.steps.size();
        }
        if(s.is_final_state()){
            s.printTable();
            cout << "Nivel de Profundidad:" << steps << " Tamano del Stack:" << S.size() << endl;
            return iter;
        }
        list<Action> actions = s.get_actions();
        for( Action a : actions){
            State ss=s.transition(a);
            S.push(ss);
        }
    }
    return iter;
}

//Busqueda en anchura.
int BFS(State& initial){
    int steps=0;
    int iter=0;
    queue<State> Q;
    Q.push(initial);
    while(!Q.empty()){
        iter++;
        State s= Q.front(); Q.pop();
        if(s.steps.size() > steps) {
            steps = s.steps.size();
        }
        if(s.is_final_state()){
            s.printTable();
            cout << "Nivel de Profundidad:" << steps << " Tamano de la Cola:" <<Q.size() << endl;
            return iter;
        }
        list<Action> actions = s.get_actions();
        for( Action a : actions){
            State ss=s.transition(a);    
            Q.push(ss);
        }
    }
    return iter;
}

//Metodo que cargara la dataset que se ingrese, eligiendo una de sus instancias aleatoriamente.
string cargar(string archivo){
    string s, sudoku;
    int i=0, instancia = rand() % 50 + 1;
    ifstream f( archivo );

    while (!f.eof()) {   
        f >> s;
        if(instancia == i){
            sudoku = s;
            break;
        }
        i++;
    }
    f.close();
    return sudoku;
}

//Metodo que donde se crea el estado inicial y desplega un menu para elegir que busqueda realizar.
void obtenerResultado(string cadena){
    int i, sudoku[N*N];
    for (i=0;i<N*N;i++) {
        sudoku[i] = cadena[i] - 48;
    }
    State s1(sudoku);
    cout << "Estado Inicial: " << endl;
    s1.printTable();
    int respuesta;
    do{
        cout << "Cuidado al elegir la opcion de anchura ya que podria ocupar demasiada memoria!!!" << endl;
        cout << "Elija una opcion de las siguientes -> (1)Busqueda en Profundidad, (2)Busqueda en Anchura, (0)Salir: ";
        cin >> respuesta;
        switch (respuesta)
        {
            case 0:
                cout << "Saliendo..." << endl;
                break;
            case 1:
                cout << "Estado Final Busqueda en Profundidad: " << endl;
                cout << DFS(s1) << endl;
                break;

            case 2:
                cout << "Estado Final Busqueda en Anchura: " << endl;
                cout << BFS(s1) << endl;
                break;

            default:
                cout << "Opcion inexistente. Elija de nuevo";
        }
    }while (respuesta != 0);
}

int main(){
    int answer;
    
    //Menu para elegir el data set de donde se sacara la instancia.
    do{
        string cadena;
        cout << "Elija una opcion de las siguientes -> (1)Sudoku Facil, (2)Sudoku Intermedio, (3)Sudoku Dificil, (0)Salir: ";
        cin >> answer;
        switch (answer)
        {
            case 0:
                cout << "Saliendo...";
                break;
            case 1:
                cadena = cargar("sudokuFacil50.txt");
                obtenerResultado(cadena);
                break;

            case 2:
                cadena = cargar("sudokuMedio50.txt");
                obtenerResultado(cadena);
                break;

            case 3:
                cadena = cargar("sudokuDificil50.txt");
                obtenerResultado(cadena);
                break;

            default:
                cout << "Opcion inexistente. Elija de nuevo";
        }
    }while (answer != 0);
    
}