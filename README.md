# README Sudoku
~~~
CAMILO ACEVEDO ÁLVAREZ
RODRIGO MORALES PEÑA
BASTIÁN ROLDÁN PULGAR
~~~

Link al video: https://drive.google.com/file/d/1uAapjOp_qkQ-zVtqj3hRodFD9znKml08/view?usp=drivesdk

## Instrucciones. 

1. Tener instalado compilador para correr c++. (https://code.visualstudio.com/docs/cpp/config-mingw)
2. Abrir archivo main.cpp desde Visual Studio Code.
3. Presionar "Terminal->Run Task" en la barra superior y seleccionar "g++"
4. Abrir Terminal, ir a ubicación donde se encuentra el archivo "main.exe" (misma ubicación donde se encuentra main.cpp).
5. Ejecutar esta linea de codigo, ".\main"

## Explicación del problema.

El problema del Sudoku consiste en un Estado Inicial con una matriz T de 9x9, divididas en 9 submatrices U de 3x3 denominadas regiones, en las cuales hay que rellenar con cifras del 1 al 9. En un inicio, existen números que son agregados de forma predeterminada dentro de algunas casillas, los cuales se denominan pistas. Estas pistas están posicionadas estratégicamente para que el jugador pueda rellenar las casillas en blanco cumpliendo las restricciones. La restricción por ley del sudoku se basa en no repetir las cifras del 1 al 9 tanto en columnas, filas y regiones.  
Cada una de las filas de la matriz T está compuesta por 9 celdas, en las cuales se deben de rellenar con las cifras del 1 al 9 en el orden que el jugador le parezca prudente, es decir, al posicionar un número en una casilla vacía hay que tener en cuenta que el número no se repita. A su vez, las columnas de las matriz T poseen una estructura idéntica que las filas, sólo que en este caso en forma vertical, también se poseen las mismas condiciones anteriormente mencionadas. Además, se deben rellenar las regiones de las submatrices U con la serie completa del 1 al 9 sin que estos se repitan.  
Al intentar resolver un sudoku nos encontramos que pueden existir diferentes niveles de dificultad. Esta dificultad dependerá netamente de la relevancia y posición que se encuentren los números dados, no de la cantidad de número de pistas iniciales como se puede llegar a creer. La dificultad reside en los métodos que ocupa el jugador para rellenar la matriz.  
Para poder llegar a un Estado Final de la matriz T no se deben de poder agregar más cifras, ya sea porque no existen más casillas en blanco dentro de la matriz o porque al intentar agregar una cifra ésta ya se encuentra digitada y además no existe otra casilla en blanco para rellenar con otra cifra. Si se encuentra dentro de este último estado, se deberá comenzar de nuevo con el problema, en cambio si se encuentra en el primer Estado Final mencionado; ¡Felicidades!, ha logrado completar el Sudoku.

## Solución propuesta
El algoritmo que nosotros propusimos para resolver el problema fue la Búsqueda en Profundidad, opción que mostró mejores resultados en comparación con el algoritmo Búsqueda en Anchura, según nuestro análisis de los resultados.  
El algoritmo de búsqueda requiere de nodos, estados, una pila y un grafo. Comienza el recorrido en el nodo inicial, que equivale al estado inicial del algoritmo, luego se avanza hacia la profundidad del grafo, de nodo en nodo, hasta que se llega al final, si en este punto el estado no fuera un estado final (solución del problema), se devuelve en el camino hasta encontrar otro y seguir así iteradamente. Cada vez que cambie de estado, este nodo es ingresado en la pila, la cual permite extraer los últimos ingresados, por eso mismo la estructura es ideal para el algoritmo, ya que cada vez que sea necesario devolverse en el camino del grafo, se extraerán los nodos desde el último visitado, hasta encontrar otra opción.  
Una explicación en pseudocódigo del algoritmo empleado, se itera mientras la pila no esté vacía, luego se extrae el primer valor de esta y es asignado al estado, se consulta si este es un estado final (si cumple con la condiciones); si lo es, se imprime el estado final, junto al número de pasos ejecutados y el tamaño de la pila; si no es así, se obtiene la lista de acciones correspondientes al estado, dentro de este proceso se aplica un filtrado de estos. El resultado de lo anterior, es ingresado a la pila.

~~~
DFS()
|   while(criterio de término: pila esté vacía)
|	|   Se extrae primer valor de la pila y se asigna al estado
|	|   if(esEstadoFinal)
|	|	|    imprimeEstadoFinal
|	|	|    retorna numeroIteraciones
|	|   endif
|	|    obtener_acciones(estados)
|    endWhile	
retorna numeroIteraciones
~~~

Como se mencionó anteriormente, al momento de generar los nodos del estado en la parte superior de la pila, se aplica un filtro a la búsqueda, de manera que no aparezcan la cantidad exorbitante de nodos que normalmente se tendria al tener como estado el colocar un valor entero del 1 al 9 en cualquiera de los espacios vacíos. 
~~~
obtener_acciones()
|	lista_acciones
|	posicion_vacia
|	maximo <- 9
|	for(casillas)
|	|	if(casilla_vacia)
|	|	|	filtro_busqueda()
|	|	endif
|	endfor
|	for(numeros_posibles)
|	|	lista_acciones <- agrego_accion()
|	endfor
retorna acciones
~~~

El filtrado se realiza dentro del método que obtiene los siguientes nodos al nodo actual, el filtro inicial radica en tomar exclusivamente valores que respeten las restricciones del problema, lo cual limita a tomar ciertos números enteros del 1 al 9, pero no bastaría solo con esto ya que aún quedan muchos espacios vacíos donde colocar un valor, para esta parte se decide encontrar la casilla que tenga la menor cantidad de números posibles que respeten las restricciones, siendo 1 el valor mínimo, para ello requiere de almacenar la posición en donde lo encuentra dentro de la matriz, para posteriormente solo obtener los nodos con números en solo esa posición y que no causen restricciones.

~~~
filtro_busqueda:
                for(numeros_posibles)
                |	if(es_valido)
                |	|	cantidad_numeros_posibles++
                |	endif
                endfor
                if(cantidad_numeros_posibles menor a maximo)
                |	maximo <- cantidad_numeros_posibles
                |	posicion_vacia <- ubicacion en el sudoku
                endif


~~~
## Coevaluación

### **Autor: Camilo Acevedo Álvarez**
\
-*Rodrigo Morales Peña*-

Criterio | Evaluación
-- | --
Asistencia y puntualidad | 1
Integración | 1
Responsabilidad | 1
Contribución | 1
Resolución de conflictos | 1  
TOTAL: +5
* Aspecto positivo:  Disposición a trabajar en los momentos necesarios.
* Aspecto negativo:  Falta de comunicación.
\
-*Bastían Roldán Pulgar*-

Criterio | Evaluación
-- | --
Asistencia y puntualidad | 1
Integración | 1
Responsabilidad | 1
Contribución | 1
Resolución de conflictos | 1
TOTAL: +5
* Aspecto positivo:  Motivación por el trabajo.
* Aspecto negativo:  Poco control de la motivación.

***
### **Autor: Rodrigo Morales Peña**
\
-*Camilo Acevedo Álvarez*-

Criterio | Evaluación
-- | --
Asistencia y puntualidad | 1
Integración | 1
Responsabilidad | 1
Contribución | 1
Resolución de conflictos | 1
TOTAL: +5

* Aspecto positivo: Tiene buena disposición en ayudar a sus compañeros, tiene paciencia
* Aspecto negativo: Es muy disperso.
\
-*Bastían Roldán Pulgar*-

Criterio | Evaluación
-- | --
Asistencia y puntualidad | 1
Integración | 1
Responsabilidad | 1
Contribución | 1
Resolución de conflictos | 1
TOTAL: +5
* Aspecto positivo: Tiene buena disposición, es centrado.
* Aspecto negativo: Tiene poca paciencia.

***
### **Autor: Bastían Roldán Pulgar**
\
-*Camilo Acevedo Álvarez*-

Criterio | Evaluación
-- | --
Asistencia y puntualidad | 1
Integración | 1
Responsabilidad | 1
Contribución | 1
Resolución de conflictos | 1
TOTAL: +5
* Aspecto positivo: Veloz aprendizaje.
* Aspecto negativo: Es desordenado.
\
-*Rodrigo Morales Peña*-

Criterio | Evaluación
-- | --
Asistencia y puntualidad | 1
Integración | 1
Responsabilidad | 1
Contribución | 1
Resolución de conflictos | 1
TOTAL: +5
* Aspecto positivo:  Se esfuerza para obtener buenos resultados.
* Aspecto negativo:  Dificultad en organizar el tiempo.
