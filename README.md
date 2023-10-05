# README-Explicación Detallada del Código: Simón Parisca, Fernando Mesino y Nicolás Echeverri

El código permite la interacción con una placa mbed utilizando un teclado numérico y lleva a cabo tres tareas diferentes: cálculo de raíces de un polinomio cuadrático, asignación de una nota alfanumérica según un valor numérico y control de un LED RGB mediante valores RGB ingresados.

## 1. Inicialización de Componentes
El código comienza con la inicialización de varios componentes esenciales para el funcionamiento del programa:

TextLCD: Se crea un objeto lcd que representa una pantalla LCD. Este objeto se utiliza para mostrar resultados y mensajes en la pantalla.

PwmOut: Se crean objetos ledR, ledG y ledB para controlar los pines LED1, LED2 y LED3 de la placa mbed, que representan un LED RGB.

Matriz de Teclado Numérico: Se define una matriz keyMap que representa el diseño del teclado numérico.

UnbufferedSerial: Se establece una comunicación serial no bufferizada para interactuar con la consola.

DigitalOut y DigitalIn: Se definen arreglos de pines rowPins y colPins para controlar las filas y columnas del teclado numérico.

## 2. Función leerChar()
La función leerChar() se encarga de leer una tecla presionada en el teclado numérico. El proceso implica un bucle que recorre las filas y columnas de la matriz del teclado. Cuando se detecta una tecla presionada, se devuelve el carácter correspondiente. Esta función también incorpora una pausa de 500 ms para evitar múltiples lecturas mientras la tecla está presionada y espera a que se libere la tecla antes de retornar.
```C++
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
```

## 3. Función leer()
La función leer() utiliza la función leerChar() para recopilar varios caracteres presionados por el usuario y los concatena en una cadena hasta que se presiona el carácter #, lo que indica que se ha completado la entrada. Esto facilita la entrada de números o valores.
```C++
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
```

## 4. Función polinomio()
La función polinomio() permite al usuario calcular las raíces de un polinomio cuadrático ingresando los coeficientes de grado 2, grado 1 y la constante. Cada coeficiente se ingresa mediante la función leer(). Luego, el programa realiza el cálculo de las raíces y las muestra en la consola. También maneja casos donde los coeficientes pueden ser negativos.
```C++
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
```

## 5. Función nota()
La función nota() permite al usuario asignar una nota alfanumérica a un valor numérico en el rango de 0 a 10. Se ingresa un valor numérico mediante la función leer(), y luego se determina la nota correspondiente en función de los rangos predefinidos. Las notas alfanuméricas se muestran en la consola.
```C++
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
```

## 6. Función rgb()
La función rgb() permite al usuario controlar un LED RGB ingresando valores para las componentes de color rojo (R), verde (G) y azul (B) en formato RGB. Los valores se ingresan mediante la función leer(), y luego se calculan los valores PWM para las tres componentes del LED RGB. Esto permite cambiar el color del LED RGB según los valores ingresados.
```C++
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
```

## 7. Función main()
La función main() es la función principal del programa.
Comienza mostrando un menú en la consola para que el usuario elija una tarea: cálculo de polinomio, asignación de nota alfanumérica o control de LED RGB.
El usuario debe ingresar un número y confirmar con #. Luego, se llama a la función correspondiente según la elección del usuario.
```C++
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
```
