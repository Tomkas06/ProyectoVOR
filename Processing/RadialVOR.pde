import processing.serial.*;
float angle = 0; 
float amplitude = 50; 
float radial = 0; 
int x = 180; 
Serial mi_puerto;  // Inicializamos la variable mi_puerto
String serialData = "";  // Para almacenar los datos seriales recibidos

void setup() {
  size(500, 500);  
  smooth();
  textAlign(CENTER, CENTER);
  mi_puerto = new Serial(this, "COM5", 115200);
  mi_puerto.bufferUntil('\n');  // Recibiendo los datos de Arduino
}

void draw() {
  background(0);  
  translate(width / 2, height / 2); 

  // Dibujar el círculo en el centro y rotarlo
  pushMatrix();
  rotate(-radial * PI / 180); 
  stroke(255);
  strokeWeight(2);
  fill(0);
  ellipse(0, 0, 300, 300);

  // Dibujar la rosa de los vientos
  drawCompass();
  popMatrix();

  // Dibuja la flecha vertical fija en el centro
  drawVerticalArrow();

  // Dibuja la línea horizontal
  horizontalPoints();
}

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

void keyPressed() {
  if (keyCode == RIGHT) {
    if (radial == 360) {
      radial = 0.0;
    }
    radial += 9; 
    println(radial);
  }
}

void horizontalPoints() {
  fill(255, 255, 255);
  for (int i = 2; i <= 10; i += 2) {
    circle(i * 10, 0, 5);
    circle(-i * 10, 0, 5);
  }
}

void drawAprox(){
  int vy1 = 10;
  int vy2 = -50;
  int estatic = 0;
  stroke(255, 255, 0); // Color de la línea amarilla

  if(radial == x){
    line(estatic, vy1, estatic, vy2);
  }
  // Valores pasando x
  else if(radial == x + 9*1){line(estatic-20, vy1, estatic-20, vy2);}
  else if(radial == x + 9*2){line(estatic-40, vy1, estatic-40, vy2);}
  else if(radial == x + 9*3){line(estatic-60, vy1, estatic-60, vy2);}
  else if(radial == x + 9*4){line(estatic-80, vy1, estatic-80, vy2);}
  else if(radial == x + 9*5){line(estatic-100, vy1, estatic-100, vy2);}
  else if (radial >= x + 9*6){line(estatic-100, vy1, estatic-100, vy2);}
  
  // Valores anteriores a x
  else if(radial == x - 9*1){line(estatic+20, vy1, estatic+20, vy2);}
  else if(radial == x - 9*2){line(estatic+40, vy1, estatic+40, vy2);}
  else if(radial == x - 9*3){line(estatic+60, vy1, estatic+60, vy2);}
  else if(radial == x - 9*4){line(estatic+80, vy1, estatic+80, vy2);}
  else if(radial == x - 9*5){line(estatic+100, vy1, estatic+100, vy2);}
  else if (radial <= x - 9*6){line(estatic+100, vy1, estatic+100, vy2);}
}

void serialEvent(Serial mi_puerto) {
  serialData = mi_puerto.readStringUntil('\n');
  if (serialData != null) {
    String[] values = trim(split(serialData, ','));  // Divide los valores recibidos
    if (values.length == 2) {
      radial = float(values[0]);  // Primer valor es el del potenciómetro
      x = int(values[1]);         // Segundo valor es el número aleatorio
    }
  }
}
