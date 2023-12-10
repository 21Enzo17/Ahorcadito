# TF Estructura de Datos 2022 - Ahorcadito

Trabajo final de la materia Estructura de Datos en el año 2022

## Descripcion
El tradicional juego de “El Ahorcadito” tiene por
objetivo descubrir una palabra adivinando las letras
que la componen. Para ello, el jugador deberá
escoger, sucesivamente, aquellas letras que
considere forman parte de la palabra. Si la palabra
contiene la letra escogida, entonces se mostrará en
qué posición o posiciones se encuentra. Sin
embargo, cuando la letra no exista en la palabra, se
dibujará una parte del cuerpo del muñeco del
jugador. Para ganar el jugador debe adivinar la
palabra antes que las 6 partes del cuerpo del
muñeco estén dibujadas, caso contrario el jugador
perderá de la partida. El jugador podrá arriesgarse a
adivinar la palabra en cualquier momento.

<hr>

- En base al juego original los diseñadores de la
empresa Kingdom of Gamers lanzarán a finales de
2022 un nueva versión del juego denominado
“Ahorcadito Final Destination”
- La versión 2022 contará con un tablero de 6
palabras, donde 2 jugadores se enfrentarán
tratando de adivinar las palabras ocultas para
ganar la partida y salvar su vida.
- El jugador presentará 3 niveles de dificultad:
básico, intermedio y avanzado.
- Según el nivel de juego, las palabras tendrán
diferente longitud: 4 caracteres (nivel 1), 6
caracteres (nivel 2) y 8 o más caracteres (nivel 3).

- En cada nivel se asignan 3 palabras a cada jugador
y se permiten n intentos para probar letras, siendo
n la mitad de la longitud de la palabra.
- Por cada palabra, el jugador podrá solicitar 2 pistas
que se descontarán de su puntaje: 1) primera letra
de la palabra (-5 puntos), 2) definición de la
palabra (-10 puntos).
- Los jugadores podrán arriesgar las palabras ocultas
en cualquier momento, es decir, no es necesario
que prueben letras o soliciten pistas para
adivinarlas.
- Los jugadores podrán elegir el nivel del juego en el
que se desarrollará la partida.

## Implementacion
- El programa debe presentar un menú con las
siguientes opciones:
  -  Gestión de Jugadores
  -  Gestión de Palabras
  -  Jugar
  -  Ranking de jugadores
  -   Salir
    
- La opción Gestión de Jugadores accede a un submenú
para agregar jugadores, consultar y/o modificar
jugadores, listar jugadores y eliminar jugadores
- La opción Gestión de Palabras accede a un submenú
que permite agregar palabras, consultar palabras y
listar palabras.
- La opción Jugar accede a un submenú que permite: a)
elegir jugadores, b) seleccionar nivel de juego y cargar
(aleatoriamente) las palabras en el tablero y c) iniciar
la partida (submenú).
- El submenú Partida debe presentar 3 opciones:
probar letra, solicitar pista y arriesgar. 


- La opción Ranking muestra los jugadores ordenados
por puntaje, omitiendo aquellos que no hayan
ganado ninguna partida. El orden es indicado por el
usuario.
- Los jugadores y las palabras deben almacenarse en
archivos binarios. No se admiten jugadores/palabras
repetidos.
  - Por cada jugador debe registrarse: id de jugador,
apellido, nombre, nickname, puntaje y cantidad
de partidas ganadas.
  - Por cada palabra debe registrarse: id de palabra,
palabra, cantidad de caracteres y definición
(significado).
- El tablero debe construirse con listas simples.
- El ranking de jugadores debe desarrollarse utilizando
árboles binarios de búsqueda.
- El puntaje se calcula según el tamaño de las palabras
(3 puntos por letra), duplicándose en caso de
palabras palíndromo y triplicándose si la palabra
tiene todos sus caracteres distintos.
- La verificación de palíndromo debe realizarse
aplicando el TDA bicola implementado con listas
dobles.
- La verificación de caracteres distintos debe realizarse
aplicando el TDA conjunto implementado con
arreglos.
- Las estructuras para mostrar los guiones y letras de
las palabras ocultas en pantalla quedan a elección
del programador.
- Para ayudar al jugador, el programa no debe hacer
diferencia entre mayúsculas y minúsculas. Por
ejemplo, será indistinto probar la letra ‘A’ o ‘a’ para
la verificación de la palabra oculta.
- El jugador que obtenga el mayor puntaje ganará la
partida. El puntaje sólo se registra para el ganador.
En caso de empate se almacena el puntaje para
ambos jugadores.
- Si ninguno de los jugadores adivina las palabras
de la partida, ésta se da por desierta (no hay
ganador).
- Si el ganador adivinó las 3 palabras de la partida,
se le asigna un extra de 15 puntos.
- Durante la partida los jugadores alternarán turnos
hasta completar las 6 palabras.
- El tablero no puede contener palabras repetidas.
- Un jugador no puede enfrentarse a sí mismo.
- Para iniciar un partida debe verificarse que al
menos existan 2 jugadores registrados y que se
cuente con la cantidad suficiente de palabras para
elegir cualquiera de los niveles del juego.
- Adicione todos los controles y datos adicionales
que considere necesarios para el correcto
funcionamiento del juego.
