import processing.serial.*;
float angle = 0; 
float amplitude = 50; //No se, fue uno de los primeros vaores que estaban
float radial = 0; //Valor actual del radial
float distance = 200; //Valor de distancia dado por el ultrasonico
int x = 180; //Valores dados por el motor paso a paso, ¿Por que no lo llamo mas facil? no enias ganas
Serial mi_puerto;  // Inicializamos la variable mi_puerto
String serialData = "";  // Para almacenar los datos seriales recibidos

int lineUp = 0;
int lineRh = 0;
int lineDn = 0;
int lineLh = 0;

void setup() {
  //size(800, 700);  // Ventana más grande (ancho 800, alto 500)
  fullScreen();
  smooth();//NI idea, lo meti por facha
  textAlign(CENTER, CENTER); //Centra el texto
  mi_puerto = new Serial(this, "COM5", 9600); //Aqui lo llamo al arduino y le pido los valores que tiene
  mi_puerto.bufferUntil('\n');  // Recibiendo los datos de Arduino
}

void draw() {
  background(0);  
  translate(width / 2 + 450, height / 2);  // Desplazar todo hacia la derecha
  
  // Dibujar el círculo en el centro y rotarlo con el potenciomnetro
  drawNDB();

  // Dibujar la rosa de los vientos
  drawCompass();
  popMatrix();

  // Dibuja la flecha vertical fija en el centro
  drawVerticalArrow();

  // Dibuja la línea horizontal
  horizontalPoints();
  
  // Dibujar el rectángulo en el lado izquierdo
  drawLeftRectangle();
  
  drawILS();
}
void drawNDB(){
  strokeWeight(2);
  pushMatrix();
  rotate(-radial * PI / 180); 
  stroke(255);
  
  fill(0);
  ellipse(0, 0, 300, 300);
}

//Dibuja el compaz o rosa de los vientos
//NO comprendo para nada todo lo que me tiro chat GPT
//Alto topo ademas, le preguntaba algo y hacia cualquier cosa
//No fue facial hablarle
//Pero mas dificil es hablarle a una chica
//Por lo que no digo nada
void drawCompass() {
  strokeWeight(1);
  for (int i = 0; i < 360; i += 9) {  // Cambiado a 9 grados
    float x1 = cos(radians(i - 90)) * 140;
    float y1 = sin(radians(i - 90)) * 140;
    float x2 = cos(radians(i - 90)) * 150;
    float y2 = sin(radians(i - 90)) * 150;
    line(x1, y1, x2, y2);

    // Dibujar etiquetas de grados
    float xLabel = cos(radians(i - 90)) * 120;
    float yLabel = sin(radians(i - 90)) * 120;
    fill(255);
    textSize(12);
    text(i, xLabel, yLabel); 
  }

  // Dibujar indicadores principales (N, E, S, W)
  textSize(16);
  fill(255);
  text("N", 0, -170);
  text("E", 170, 0);
  text("S", 0, 170);
  text("W", -170, 0);
}

void drawCompassILS() {
  strokeWeight(1);
  for (int i = 0; i < 360; i += 15) {  // Cambiado a 9 grados
    float x1 = cos(radians(i - 90)) * 140;
    float y1 = sin(radians(i - 90)) * 140;
    float x2 = cos(radians(i - 90)) * 150;
    float y2 = sin(radians(i - 90)) * 150;
    line(x1, y1, x2, y2);

    // Dibujar etiquetas de grados
    float xLabel = cos(radians(i - 90)) * 120;
    float yLabel = sin(radians(i - 90)) * 120;
    fill(255);
    textSize(12);
    text(i, xLabel, yLabel); 
  }

  // Dibujar indicadores principales (N, E, S, W)
  textSize(16);
  fill(255);
  text("N", 0, -170);
  text("E", 170, 0);
  text("S", 0, 170);
  text("W", -170, 0);
}

void drawILS(){
  strokeWeight(2);
  translate(625, 75);
  ellipse(0, 0, 300, 300);
  pushMatrix();
  rotate(-radial * PI / 180); 
  stroke(255);
  
  fill(0);

  // Dibujar la rosa de los vientos
  drawCompassILS();
  popMatrix();

  aproxILS();

  // Dibuja la línea horizontal
  horizontalPoints();
  verticalPoints();
  drawCenterILS();
  
}

void aproxILS(){
  
  float y1 = -100;
  
  fill(255, 255, 0); 
  noStroke();
  triangle(-10, y1, 10, y1, 0, y1 - 20);
  
  stroke(255, 255, 255);
  
  ILSlines();
  
}

void ILSlines(){
  strokeWeight(2);  
  
  stroke(0, 255, 0);
  if(lineDn == 1){line(-90, 40, 90, 40);}///////////////////////////////////////////////////////////////////////////////////////////////////////////////
  else if(lineUp == 1){line(-90, -40, 90, -40);}
  else{line(100, 0, -100, 0);}
  
  if(lineRh == 1){line(75, 80, 75, -80);}
  else if(lineLh == 1){line(-75, 80, -75, -80);}///////////////////////////////////////////////////////////////////////////////////////////////////////////////
  else{line(0, 100, 0, -100);}
  
  //line(0, 100, 0, -100); //Centrada vertical
  //line(100, 0, -100, 0); //Centrada horizontal
  
}

//Dibuja la flecha vertical
void drawVerticalArrow() {
  float length = 100; 
  
  float x1 = 0;
  float y1 = -length;
  float x2 = 0;
  float y2 = length;

  stroke(0, 255, 0); 
  strokeWeight(2);  

  // Dibuja la línea vertical
  line(x1, y1, x2, y2-150); 
  
  drawAprox();
  
  // Dibuja la línea inferior
  line(x1, y1+100, x2, y2);

  // Dibujar el triángulo en la punta superior
  fill(255, 255, 255); 
  noStroke();
  triangle(-10, y1, 10, y1, 0, y1 - 20); 
}

//Mueve el radial hacia la derecha si se presiona
//Se usa en caso de que el potenciometro no este conectado
void keyPressed() {
  if (keyCode == RIGHT) {
    if (radial == 360) {
      radial = 0.0;
    }
    radial += 9; 
    println(radial);
  }
}

//Funcion que dibuja los ciculos horinzoltales de la rosa de los vientos
void horizontalPoints() {
  noStroke();
  
  fill(255, 255, 255);
  for (int i = 2; i <= 10; i += 2) {
    circle(i * 10, 0, 5);
    circle(-i * 10, 0, 5);
  }
}

void verticalPoints(){
  noStroke();
  
  fill(255, 255, 255);
  for (int i = 2; i <= 10; i += 2) {
    circle(0, i * 10, 5);
    circle(0, -i * 10, 5);
  }
}

void drawCenterILS(){
  noFill();
  circle(0, 0, 15);
  stroke(255, 255, 255);
}


//Funcion que dibuja la barra de aproximacion, moviendose hacia dentro si se acerca o hacia afuera si se aleja
//PROHIBIDO PREGUNTAR QUE HACE CADA COSA
//tampoco modifiquen esto, no entinedo un carajo que hace cada cosa
void drawAprox() {
  //Valores para simplificar el proceso
  int vy1 = 10;
  int vy2 = -50;
  int estatic = 0;
  stroke(255, 255, 0); // Color de la línea amarilla

  float diferencia = radial - x;
  float steps = diferencia / 9;

  if (abs(steps) > 6) {
    steps = steps > 0 ? 6 : -6;
  }
  
  line(estatic - steps * 20, vy1, estatic - steps * 20, vy2);
}

//Funcion que dibuja el rectangulo
void drawLeftRectangle() {
  //Valores de los rectangulos, x para la base, y para la altura
  int xRec = 350;
  int yRec = 150;
  int espaciado = 20;
  
  noFill();  // Sin relleno
  stroke(255, 255, 255);  // Bordes rojos
  strokeWeight(3);  // Grosor del borde
  translate(-1100, -75); //Translado todo a la izquierda del cuadro
  rect(0, 0, xRec, yRec, 10);  // Rectángulo más pequeño y centrado en el eje vertical
  
  //Valores de separacion de los textos
  //Para que no esten pegados y no repetir valores
  float espacio = 37.5;
  int col = 25;
  int linea = 50;
  
  // Primer bloque de texto para Distance
  textAlign(CENTER, CENTER);  // Centrar texto
  fill(255);  // Color blanco para el texto
  color redText = color(255, 0, 0);  // Rojo para los enunciados
  color yellowText = color(255, 255, 0);  // Amarillo para los valores
  
  fill(255, 255, 255);
  text("DME INSTRUMENT", 175, -20);

  //Textos dentro del rectangulo
  fill(redText);  // Color rojo para el texto de los enunciados
  text("DISTANCE", col + espacio + linea / 2, yRec / 2 - 20);  // Texto de la distancia de la aeronave con respecto al VOR
  
  fill(yellowText);  // Color amarillo para los valores
  text(distance * 1.852 + " nm", col + espacio + linea / 2, yRec / 2 + 10);  // Texto del valor de la distancia de la aeronave con respecto al VOR

  // Segundo bloque de texto para Speed
  fill(redText);  // Color rojo para el enunciado
  text("SPEED", col + espacio + linea + espacio + linea / 2, yRec / 2 - 20);  // Texto de la velocidad de la aeronave
  
  fill(yellowText);  // Color amarillo para el valor
  text("100 kt", col + espacio + linea + espacio + linea / 2, yRec / 2 + 10); // Texto del valor de la velocidad de la aeronave

  // Tercer bloque de texto para Time
  fill(redText);  // Color rojo para el enunciado
  text("TIME", col + espacio + linea + espacio + linea + espacio + linea / 2, yRec / 2 - 20); // Texto del tiempo de llegada
  
  fill(yellowText);  // Color amarillo para el valor
  text((distance * 1.852 / 185.2) + " Horas", col + espacio + linea + espacio + linea + espacio + linea / 2, yRec / 2 + 10); // Texto del valor del tiempo de llegada
  
  
  fill(255, 255, 255);
  text("MADE BY EETA N32", 170, 130);
  
  noFill();  // no rellena con colores los circulos en la esquina del rectangulo
  circle(espaciado, espaciado, 10); //Circulo en la esquina superior izquierda
  circle(xRec-espaciado, espaciado, 10); //Circulo en la esquina superior derecha
  circle(xRec-espaciado, yRec-espaciado, 10); //Circulo en la esquina inferior derecha
  circle(espaciado, yRec-espaciado, 10); //Circulo en la esquina inferior izquierda
}

//Crea una funcion en la que analiza todos los valores del arduino
void serialEvent(Serial mi_puerto) {
  //El valor recibido por el arduino lo lee hasta un salto de linea
  serialData = mi_puerto.readStringUntil('\n');
  //Verifica que los valores no sean null osea nulos o vacios
  if (serialData != null) {
    String[] values = trim(split(serialData, ','));  // Divide los valores recibidos
    //Comprueba si los valores recibidos son mayores a 3 elementos
    if (values.length == 7) {
      x = int(values[0]);         // Segundo valor es el motor paso a paso
      if (int(values[1]) != 0){distance = int(values[1]);}  // Primer valor es el ultrasonico
      radial = float(values[2]);  // Tercer valor es el del potenciómetro
      lineUp = int(values[3]);
      lineRh = int(values[4]);
      lineDn = int(values[5]);
      lineLh = int(values[6]);
    }
  }
}