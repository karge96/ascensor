#include <iostream>
#include <limits>
//para mejorar y asegurar la compilacion
#ifdef _WIN32
    #include <windows.h> 
#else
    #include <unistd.h> 
#endif
// genera un retraso entre mensaje y mensaje, segun los segundos introducidos
void espera(int segundos) {
    #ifdef _WIN32
        Sleep(segundos * 1000); 
    #else
        sleep(segundos);
    #endif
}
//abre la puerta del ascensor despues de 2 segundos. 
void abrirPuerta() {
    std::cout << "La puerta se abre.\n";
    espera(2);
}
//cierra la puerta del ascensor despues de 2 segundos. 
void cerrarPuerta() {
    std::cout << "La puerta se cierra.\n";
    espera(2);
}
//mueve el ascensor, arriba o abajo con un retraso de 3 segundos entre piso y piso
void moverAscensor(int &pisoActual, int pisoDestino) {
    while (pisoActual != pisoDestino) {
        if (pisoDestino > pisoActual) {
            std::cout << "Subiendo...\n";
            pisoActual++;
        } else if (pisoDestino < pisoActual) {
            std::cout << "Bajando...\n";
            pisoActual--;
        }
        std::cout << "El ascensor se encuentra en el piso " << pisoActual << ".\n";
        espera(3);
    }
}
//valida el ingreso del piso, no puede ser mayor a 20 pisos
int solicitarPisoDestino( int pisoActual) {
    int pisoDestino;
    std::cout << "Ingrese el numero del piso al que desea ir: ";
    
    while (true) {
        while (!(std::cin >> pisoDestino)) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Ingrese un piso valido: ";
        }
        
        if (pisoDestino >= 0 && pisoDestino <= 20) {
            if (pisoDestino != pisoActual ) { //validamos el no ingreso del mismo piso en el que estamos
                break;
            } else {
                std::cout << "Ya esta en el piso " << pisoActual << ". Ingrese un piso diferente: ";
            }
        } else {
            std::cout << "Piso no valido, ingrese un nuevo numero de piso: ";
        }
    }
    return pisoDestino;
}
//ejecuta todos los movimientos del ascensor
void simularAscensor() {
    int pisoActual = 1; //el ascensor comienza en el piso 1

    while (true) {
        abrirPuerta();
        std::cout << "Estamos en el piso " << pisoActual << ".\n";

        int pisoDestino = solicitarPisoDestino(pisoActual);
        espera(3);
        cerrarPuerta();
        moverAscensor(pisoActual, pisoDestino);
        //el cero sera el comando para terminar la simulacion
        if (pisoDestino == 0) {
            std::cout << "Saliendo del simulador de ascensor.\n";
            break;
        }
    }
}

int main() {
    simularAscensor();
    return 0;
}
