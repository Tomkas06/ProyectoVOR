float angle = 0; // Ángulo para el balanceo de la flecha
float amplitude = 50; // Amplitud del movimiento lateral del radial
float radial = 0; // Angulo para el radial
int x = 180; //Este valor sera sacado del valor dado por el arduino
int xNega = x - 360; //Le resta 360

//Funcion que configura el dibuj0
void setup() {
  size(500, 500);   // Tamaño de la ventana
  smooth();
  textAlign(CENTER, CENTER);
}

//Funcion principal del programa
void draw() {
  background(0);  // Color de fondo negro
  translate(width / 2, height / 2);  // Trasladar el origen al centro de la ventana

  // Dibujar el círculo en el centro y rotarlo
  pushMatrix();
  //Jeje, este estaba escondido
  rotate(-radial*(3.1415923/180));
  stroke(255);
  strokeWeight(2);
  fill(0);
  ellipse(0, 0, 300, 300);

  // Dibujar la rosa de los vientos
  drawCompass();
  popMatrix();

  // Dibuja la flecha vertical fija en el centro
  drawVerticalArrow();
  
  //Dibuja la linea horizontal
  horizontalPoints();

}

//Funcion que dibuja el compaz
void drawCompass() {
  strokeWeight(1);
  for (int i = 0; i < 360; i += 15) {
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
    text(i, xLabel, yLabel); // Etiquetas de grados
  }

  // Dibujar indicadores principales (N, E, S, W)
  textSize(16);
  fill(255);
  text("N", 0, -170);
  text("E", 170, 0);
  text("S", 0, 170);
  text("W", -170, 0);
}

//Funcion que dibuja la flecha vertical. Eu soy muito ingles. nigas nigas
void drawVerticalArrow() {
  float length = 100; // Longitud de la flecha
  
  // Coordenadas de la punta superior y la base de la flecha
  float x1 = 0;
  float y1 = -length;
  float x2 = 0;
  float y2 = length;

  stroke(0, 255, 0); // Color de la línea (verde)
  strokeWeight(2);   // Grosor de la línea

  // Dibuja la línea vertical
  line(x1, y1, x2, y2-150); //Linea superior
  
  //Empieza toda una linea de condicionales. sufri mucho? si
  
  if(radial == x || radial == xNega){
  line(x1, y1+50, x2, y2-100); //Linea del medio
  }
  
  else if(radial == x-15 || radial == xNega-15){
    line(x1+20, y1+50, x2+20, y2-100); //Linea del medio
  }
  
  else if(radial == x+15|| radial == xNega+15){
    line(x1-20, y1+50, x2-20, y2-100); //Linea del medio
  }
  
  else if(radial == x-30 || radial == xNega-30){
    line(x1+35, y1+50, x2+35, y2-100); //Linea del medio
  }
  
  else if(radial == x+30 || radial == xNega+30){
    line(x1-35, y1+50, x2-35, y2-100); //Linea del medio
  }
  
  else if(radial == x-45 || radial == xNega-45){
    line(x1+50, y1+50, x2+50, y2-100); //Linea del medio
  }
  
  else if(radial == x+45 || radial == xNega+45){
    line(x1-50, y1+50, x2-50, y2-100); //Linea del medio
  }
  
  else if(radial == x-60 || radial == xNega-60){
    line(x1+65, y1+50, x2+65, y2-100); //Linea del medio
  }
  
  else if(radial == x+60 || radial == xNega+60){
    line(x1-65, y1+50, x2-65, y2-100); //Linea del medio
  }
  
  else if(radial == x-75 || radial == xNega-75){
    line(x1+80, y1+50, x2+80, y2-100); //Linea del medio
  }
  
  else if(radial == x+75 || radial == xNega+75){
    line(x1-80, y1+50, x2-80, y2-100); //Linea del medio
  }
  
  else if(radial == x-90 || radial == xNega-90){
    line(x1+80, y1+50, x2+80, y2-100); //Linea del medio
  }
  
  else if(radial == x+90 || radial == xNega+90){
    line(x1-80, y1+50, x2-80, y2-100); //Linea del medio
  }
  
  
  //Aca estan los cambiados
  //Aca marco devuelta
  //Aca digo SEXOOOO
  
  else if(radial == x-105 || radial == xNega-105){
    line(x1+80, y1+50, x2+80, y2-100); //Linea del medio
  }
  
  else if(radial == x+105 || radial == xNega+105){
    line(x1-80, y1+50, x2-80, y2-100); //Linea del medio
  }
  
  else if(radial == x-120 || radial == xNega-120){
    line(x1+80, y1+50, x2+80, y2-100); //Linea del medio
  }
  
  else if(radial == x+120 || radial == xNega+120){
    line(x1-80, y1+50, x2-80, y2-100); //Linea del medio
  }
  
  else if(radial == x-135 || radial == xNega-135){
    line(x1+80, y1+50, x2+80, y2-100); //Linea del medio
  }
  
  else if(radial == x+135 || radial == xNega+135){
    line(x1-80, y1+50, x2-80, y2-100); //Linea del medio
  }
  
  //Otros mas
  
  else if(radial == x-150 || radial == xNega-150){
    line(x1+80, y1+50, x2+80, y2-100); //Linea del medio
  }
  
  else if(radial == x+150 || radial == xNega+150){
    line(x1-80, y1+50, x2-80, y2-100); //Linea del medio
  }
  
  else if(radial == x-165 || radial == xNega-165){
    line(x1+80, y1+50, x2+80, y2-100); //Linea del medio
  }
  
  else if(radial == x+165 || radial == xNega+165){
    line(x1-80, y1+50, x2-80, y2-100); //Linea del medio
  }
  
  else if(radial == x-180 || radial == xNega-180){
    line(x1+80, y1+50, x2+80, y2-100); //Linea del medio
  }
  
  else if(radial == x+180 || radial == xNega+180){
    line(x1-80, y1+50, x2-80, y2-100); //Linea del medio
  }
  
  //Quilombo full
  
  else if(radial == x-195 || radial == xNega-195){
    line(x1+80, y1+50, x2+80, y2-100); //Linea del medio
  }
  
  else if(radial == x+195 || radial == xNega+195){
    line(x1-80, y1+50, x2-80, y2-100); //Linea del medio
  }
  
  else if(radial == x-210 || radial == xNega-210){
    line(x1+80, y1+50, x2+80, y2-100); //Linea del medio
  }
  
  else if(radial == x+210 || radial == xNega+210){
    line(x1-80, y1+50, x2-80, y2-100); //Linea del medio
  }
  
  //Mas quilombo ehhh
  
  else if(radial == x-225 || radial == xNega-225){
    line(x1+80, y1+50, x2+80, y2-100); //Linea del medio
  }
  
  else if(radial == x+225 || radial == xNega+225){
    line(x1-80, y1+50, x2-80, y2-100); //Linea del medio
  }
  
  else if(radial == x-240 || radial == xNega-240){
    line(x1+80, y1+50, x2+80, y2-100); //Linea del medio
  }
  
  else if(radial == x+240 || radial == xNega+240){
    line(x1-80, y1+50, x2-80, y2-100); //Linea del medio
  }
  
  //Es un descajete
  
  else if(radial == x-255 || radial == xNega-255){
    line(x1+80, y1+50, x2+80, y2-100); //Linea del medio
  }
  
  else if(radial == x+255 || radial == xNega+255){
    line(x1-80, y1+50, x2-80, y2-100); //Linea del medio
  }
  
  else if(radial == x-270 || radial == xNega-270){
    line(x1+80, y1+50, x2+80, y2-100); //Linea del medio
  }
  
  else if(radial == x+270 || radial == xNega+270){
    line(x1-80, y1+50, x2-80, y2-100); //Linea del medio
  }
  
  //Hola hola ehhh
  else if(radial == x-285 || radial == xNega-285){
    line(x1+80, y1+50, x2+80, y2-100); //Linea del medio
  }
  
  else if(radial == x+285 || radial == xNega+285){
    line(x1-80, y1+50, x2-80, y2-100); //Linea del medio
  }
  
  else if(radial == x-300 || radial == xNega-300){
    line(x1+80, y1+50, x2+80, y2-100); //Linea del medio
  }
  
  else if(radial == x+300 || radial == xNega+300){
    line(x1-80, y1+50, x2-80, y2-100); //Linea del medio
  }
  //Hasta aqui son todas las condicionales que se fijan la posicion del radial
  //El autor hace incapie que sufrio mucho
  //Tambien hace incapie en que le escriban y le digan cosas lindas. 3625635233
  //atte: pete
  
  //Dibuja la linea inferior
  line(x1, y1+100, x2, y2);

  // Dibujar el triángulo en la punta superior
  fill(255, 255, 255); // Color del triángulo (blanco)
  //Esto es para que no se apague la pc. Ni idea pa, se puso solo (:
  noStroke();
  triangle(-10, y1, 10, y1, 0, y1 - 20); // Triángulo en la punta superior
}

//Aqui una funcion cuando se presione uno de los botones del teclado
void keyPressed() {
  //Cuando se presiona la flecha Izquierda
  if (keyCode == LEFT) {
    //Esto esta para resetear el contador y que no sea mayor o menor a 360
    if(radial == -360){
      radial = 0.0;
    }
    
    //Resta el valor de radial
    radial -= 15;  // Girar el radial hacia la izquierda
    
    //Aca flashee matematica y pase de radianes a grados
    //println(round(radial*(180/3.14159265359)));
    //Imprime el valor de radial
    println(radial);
    
    //Cuando se presiona la flecha Izquierda
  } else if (keyCode == RIGHT) {
    if (radial == 360){
      radial = 0.0;
    }
    radial += 15;  // Girar el radial hacia la derecha
    //println(round(radial*(180/3.14159265359)));
    println(radial);
  }
}

void horizontalPoints(){
  //Color del circulo
  fill(255, 255, 255);
  
  //Ciculo a 2 grados
  circle(20, 0, 5);
  
  //Ciculo a 4 grados
  circle(35, 0, 5);
  
  //Ciculo a 6 grados
  circle(50, 0, 5);
  
  //Ciculo a 8 grados
  circle(65, 0, 5);
  
  //Ciculo a 10 grados
  circle(80, 0, 5);
  
  //Negativos
  
  //Ciculo a -2 grados
  circle(-20, 0, 5);
  
  //Ciculo a -4 grados
  circle(-35, 0, 5);
  
  //Ciculo a -6 grados
  circle(-50, 0, 5);
  
  //Ciculo a -8 grados
  circle(-65, 0, 5);
  
  //Ciculo a -10 grados
  circle(-80, 0, 5);
  
}

//Esto no sirve xD
//El que lo usa es putoo
float gradRad(int grados){
  return grados * (3.1415923/180);
}
