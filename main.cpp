// Código creado por Jorge Buenestado para la práctica P4 de Física Cuántica
//                                                             28/11/2023
//Este código comprueba que un valor de la Intensidad es mayor o menor que la precision de numeros adyacentes.
//Entiende que si hay 2 máximos separados por la variable "prec" valores, son 2 máximos distintos.
//Si un máximo o mínimo se repite, ya que alcanza valores similares durante las subidas/bajadas, solo toma el primer valor.
//Los primeros valores que toma pueden no ser válidos, ya que al principio no tiene subida/bajadas clara, configurar Vmin
//Una manera de comprobar que los resultados son correctos es contar visualmente el número de minimos y máximos. 
//El numero de minimo y maximos deben variar como mucho 1 unidad.
//Para valores extremos de temperatura, los máximos/minimos pueden coincidir y por ello, registrarte menos
#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip> 
#include <sstream>
using namespace std;

int main()
{
    int i, k, start;
    int prec = 20, nmin = 0, nmax = 0;
    double Vmin;
    double v[2][2500], m1[2][40], m2[2][40];
    bool min, max, repetido;
    ifstream fich;
    ofstream print;

    fich.open("./Medida120-1"); // Archivo con las medidas
    print.open("./Texto.txt");  //Archivo con las respuestas, poner el nombre que deseas

    //Si para limpiar valores, prefieres que solo empiece a buscar a partir de cierto voltaje, pon Vmin = al valor al que quieras que empiece a buscar
    Vmin = 0;

    if(!fich.is_open()){   
            cout << "Error al abrir el archivo introducido";
    }
    else{
        cout << "Archivo abierto" << endl;
    }

    i = 0;
    while (true){ //leer el archivo introducido
        fich >> v[0][i];
        fich >> v[1][i];
        i++;
        if(fich.eof() ) break;
    }

    for( k = 0; k < i; k++){ // Para empezar a buscar valores a partir del Vmin
        if(Vmin < v[0][k]){
            start = k;
            break;
        }
    }

    for(int k = start; k < i; k++){ //buscar min/max
        max = true;
        min = true;
        for(int l = 0; l < prec; l++){
            if((v[1][k] < v[1][k+l])||(v[1][k] < v[1][k-l])){
                max = false;
            }
            if((v[1][k] > v[1][k+l])||(v[1][k] > v[1][k-l])){
                min = false;
            }
        }
        if(max){// Comprueba que ese máximo no haya salido antes
            repetido = false;
            for(int j = 0; j < nmax+1; j++){
                if(v[1][k] == m1[1][j]){
                    repetido = true;
                }
            }
            if(!repetido){          
                nmax += 1;
                m1[0][nmax] = v[0][k];
                m1[1][nmax] = v[1][k];
            }
        }
        if(min){ // Comprueba que ese mínimo no haya salido antes
            repetido = false;
            for(int j = 0; j < nmin+1; j++){
                if(v[1][k] == m2[1][j]){
                    repetido = true;
                }
            }
            if(!repetido){
                nmin += 1;
                m2[0][nmin] = v[0][k];
                m2[1][nmin] = v[1][k];
            }   
        }
    }

    //Exportar los resultados
    print << "Número de Máximos encontrados: " << nmax-1 << endl;
    print << "n  " << "U_{1}(V)  " << "I(nA)  "<< "Delta U" << endl;
    for(int j = 1; j < nmax; j++){
        print << j << "  "<< m1[0][j] << "   " << m1[1][j] << "  " << m1[0][j] - m1[0][j-1] << endl;
    }
    print << endl;

    print << "Número de Mínimos encontrados: " << nmin-1 <<  endl;
    print << "n" << "U_{1}(V)  " << "I(nA)  "<< "Delta U" << endl;
    for(int j = 1; j < nmin; j++){
        print << j << "  "<< m2[0][j] << "   " << m2[1][j] << "  " << m2[0][j] - m2[0][j-1] << endl;
    }

    print << endl;
    print.close();
    fich.close();
    cout << "End of Program" << endl;
    return 0;
}