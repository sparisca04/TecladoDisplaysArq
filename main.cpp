#include "Keypad.h"
#include "TextLCD.h"
#include "iostream"
#include "mbed.h"
#include "string"
#include <cmath>
#include <cstdio>

using namespace std;

TextLCD lcd(D2, D3, D4, D5, D6, D7, TextLCD::LCD16x2);


PwmOut ledR(LED1);
    PwmOut ledG(LED2);
    PwmOut ledB(LED3);

    const int numRows = 4;
    const int numCols = 3;

    char keyMap[numRows][numCols] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
    };

    UnbufferedSerial serial(USBTX, USBRX, 9600);
    using namespace std;
    DigitalOut rowPins[numRows] = {DigitalOut(D2), DigitalOut(D3), DigitalOut(D4), DigitalOut(D5)};
    DigitalIn colPins[numCols] = {DigitalIn(D6), DigitalIn(D7), DigitalIn(D8)};

    char leerChar(){
        char teclaPresionada = '\0';
        while(teclaPresionada == '\0'){
            for (int i = 0; i < numRows; i++) {
                        rowPins[i] = 0;
                        
                        for (int j = 0; j < numCols; j++) {
                            if (!colPins[j]) {
                                teclaPresionada= keyMap[i][j];
                                ThisThread::sleep_for(500ms);  // Evita lecturas múltiples mientras la tecla está presionada
                                while (!colPins[j]) {
                                // Espera hasta que se libere la tecla
                                }
                                break;
                            }
                            
                        }
                        rowPins[i] = 1;
                        if (teclaPresionada != '\0') {
                            break; // Sal del bucle externo después de encontrar una tecla
                        }
            }
        }
        return teclaPresionada;
    }

    string leer() {
        string cadena = "";
        char pressedKey;

        while (true) {
            pressedKey = leerChar();

            if (pressedKey == '#') {
                break; // Confirma con '*'
            } else if (isdigit(pressedKey)) {
                cadena += pressedKey; // Agrega el número a la cadena
            }
        }

        return cadena;
    }

   void polinomio() {
    string A;
    string B;
    string C;
    int a;
    int b;
    int c;
    
    printf("Introduzca el coeficiente de grado 2:\n");
    A = leer();
    if (A.at(0) == '#')
        a = -1*std::stoi(A);
    else
        a = std::stoi(A);
        
    printf("Introduzca el coeficiente de grado 1:\n");
    B = leer();
    if (B.at(0) == '#')
        b = -1*std::stoi(B);
    else
        b = std::stoi(B);

    printf("Introduzca el coeficiente constante:\n");
    C = leer();
    if (C.at(0) == '*')
        c = -1*std::stoi(C);
    else
        c = std::stoi(C);


    int discriminante = b * b - 4 * a * c;
    if (discriminante < 0) {
        printf("solucion en los imaginarios");
        return;
    }

    int raiz1 = (-b + sqrt(discriminante)) / (2 * a);
    int raiz2 = (-b - sqrt(discriminante)) / (2 * a);

    std::cout << "Polinomio: " << std::to_string(a) << " " << std::to_string(b) << " " << std::to_string(c) << std::endl;
    // Imprimir las raíces como números decimales
    std::cout << "Raices: " << std::to_string(raiz1) << " y " << std::to_string(raiz2) << std::endl;

}


    void nota(){
        string n;
        printf("Ingrese su nota de 0 a 10:\n");
        n = leer();
        int N = std::stoi(n);

        if (0 <= N && N <= 3)
            printf("A\n");
        else if (3 < N && N <= 4)
            printf("B\n");
        else if (4 < N && N <= 5)
            printf("C\n");
        else if (5 < N && N <= 7)
            printf("D\n");
        else if (7 < N && N < 9)
            printf("E\n");
        else if (9 <= N && N <= 10)
            printf("F\n");
    }

    void rgb(){
            string R, G, B; 
            int r, g, b;
            
            printf("Ingrese el color en formato RGB\n");
            printf("R:\n");
            R = leer();
            r = std::stoi(R);

            printf("G:\n");
            G = leer();
            g = std::stoi(G);

            printf("B:\n");
            B = leer();
            b = std::stoi(B);
            
            // Calculate PWM values
            

            ledR = (1 - (float)r/255);
            ledG = (1 - (float)g/255);
            ledB = (1 - (float)b/255);
    }

    int main() {
        
            printf("Pulse un numero para ejecutar una tarea\n");
            printf("1 para polinomio,\n");
            printf("2 para nota alfanumerica\n");
            printf ("3 para LED RGB\n");
            printf ("al digitar un numero confirme con '#'\n");
            string c = leer();
            int numero = std::stoi(c);
            if (numero == 1){
                polinomio();
            }else if (numero == 2){
                nota();
            }else if (numero == 3){
                rgb();
            }
           
    }