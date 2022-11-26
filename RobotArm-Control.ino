
#include <VarSpeedServo.h> //Biblioteca para comandar os servos motores

//Essas variaves são responsaveis por armazenar a posição zero maquina de cada eixo
String readString;
int posx = 90; 
int posy = 90; 
int posz = 80; 
int posw = 90; 
int posc = 90; 
int posb = 90; 
int intensidade = 10;
int CalcEixosY;
int ajuste = 9;
int tempoLocomocao = 1200;

//Declaração dos eixos X (BASE)
#define EixoX_PWM A0
VarSpeedServo MG995_ServoX; 

//Declaração dos eixos Y (BRAÇO)
#define EixoY1_PWM A1
VarSpeedServo MG995_ServoY1;

#define EixoY2_PWM A2
VarSpeedServo MG995_ServoY2;

//Declaração dos eixos Z (ANTEBRAÇO)
#define EixoZ_PWM A3
VarSpeedServo MG995_ServoZ;

//Declaração dos eixos W (PULSO)
#define EixoW_PWM A4
VarSpeedServo MG995_ServoW;

//Declaração dos eixos C (TORÇÃO PULSO)
#define EixoC_PWM A5
VarSpeedServo SG90_ServoC;

//Declaração dos eixos B (GARRA)
#define EixoB_PWM 3
VarSpeedServo SG90_ServoB;

void setup(){
  //Inicializando os servos e referenciandos 
  MG995_ServoX.attach(EixoX_PWM);
  MG995_ServoY1.attach(EixoY1_PWM);
  MG995_ServoY2.attach(EixoY2_PWM);
  MG995_ServoZ.attach(EixoZ_PWM);
  MG995_ServoW.attach(EixoW_PWM);
  SG90_ServoC.attach(EixoC_PWM);
  SG90_ServoB.attach(EixoB_PWM);

  Serial.begin(9600);//Inicializando o monitor serial
  Serial.println("Digite help para ver os comandos");
  
}
void Help(){
  //Função responsavel por demostrar ao usuario as possibilidades que pode fazer com os eixos
  Serial.println("Codigo de teste de movimentacao dos motores");
  Serial.println();
  Serial.println("no serial digite o angulo desejado junto ao eixo e pressione enter");
  Serial.println("por exemplo:");
  Serial.println();
  Serial.println("45x para mover o eixo X (Base) para 45 graus");
  Serial.println("35y para mover o eixo Y (Braco) para 35 graus");
  Serial.println("15z para mover o eixo Z (AnteBraco) ára 15 graus");
  Serial.println("180w para mover o eixo W (Pulso) em 180 graus");
  Serial.println("45c para mover o eixo C (Torcao Pulso) em 45 graus");
  Serial.println("60b para mover o eixo B (Garra) em 60 graus");
  Serial.println();
  Serial.println("Digite q para mostrar todas as posiçoes atuais");
  Serial.println("9i para alterar o ajuste do eixo Y (Braco)");

  Serial.println();
  Serial.println("w para movimentar eixo Y (Braco) para cima");
  Serial.println("s para movimentar eixo Y (Braco) para baixo");
  Serial.println("a para movimentar eixo X (Base) para a esquerda");
  Serial.println("d para movimentar eixo X (Base) para a direita");
  Serial.println("t para movimentar eixo Z (Antebraco) para cima");
  Serial.println("g para movimentar eixo Z (Antebraco) para baixo");
  Serial.println("r para movimentar eixo w (Pulso) para cima");
  Serial.println("f para movimentar eixo w (Pulso) para baixo");
  Serial.println("h para movimentar eixo C (TorcaoPulso) para a esquerda");
  Serial.println("j para movimentar eixo C (TorcaoPulso) para a direita");
  }


  
void Base(int anguloX, int velocidadeBase){
  //Função responsavel por comandar o eixo X correspondente a BASE
  MG995_ServoX.write(anguloX, velocidadeBase);
  Serial.println("eixo X em: ");
  Serial.println(anguloX);
}

void Braco(int anguloY, int velocidadeBraco){
  //Função responsavel por fazer o calculo dos eixos e deixar pronto para atuação
  CalcEixosY = (179 - anguloY);
  CalcEixosY -= ajuste;
  MG995_ServoY1.write(anguloY, velocidadeBraco);
  MG995_ServoY2.write(CalcEixosY, velocidadeBraco);
  Serial.println("eixo Y em: ");
  Serial.println(anguloY);
}

void Antebraco(int angulo_anteBraco, int velocidade_anteBraco){
  //Função responsavel por comandar o eixo Z correspondente ao ANTEBRAÇO
  MG995_ServoZ.write(angulo_anteBraco, velocidade_anteBraco); 
  Serial.println("eixo Z em: ");
  Serial.println(angulo_anteBraco);
  MG995_ServoZ.attach(EixoZ_PWM);
}

void Pulso(int angulo_pulso, int velocidade_pulso){
  //Função responsavel por comandar o eixo W correspondente ao PULSO
  MG995_ServoW.write(angulo_pulso, velocidade_pulso); 
  Serial.println("eixo W em: ");
  Serial.println(angulo_pulso);
}
void torcaoPulso(int angulo_torcaoPulso, int velocidade_torcaoPulso){
  //Função responsavel por comandar o eixo C correspondente a TORÇÃO DO PULSO
  SG90_ServoC.write(angulo_torcaoPulso, velocidade_torcaoPulso); 
  Serial.println("eixo C em: ");
  Serial.println(angulo_torcaoPulso);
}

void Garra(int angulo_garra, int velocidade_garra){
  //Função responsavel por comandar o eixo B correspondente a GARRA
  SG90_ServoB.write(angulo_garra, velocidade_garra); 
  Serial.println("eixo B em: ");
  Serial.println(angulo_garra);
}


void loop()
{
  while (Serial.available()) {
    char c = Serial.read();  //gets one byte from serial buffer
    readString += c; //makes the string readString
    delay(2);  //slow looping to allow buffer to fill with next character
  
  if (readString.length() >0) {
        if(readString.indexOf('x') >0) { 
      posx = readString.toInt();
      Base(posx, 50);
    }
        if(readString.indexOf('y') >0) { 
      posy = readString.toInt();
      Braco(posy, 50);
    }
        if(readString.indexOf('z') >0) { 
      posz = readString.toInt();
      Antebraco(posz, 70);
    }
        if(readString.indexOf('w') >0) { 
      posw = readString.toInt();
      Pulso(posw, 50);
    }
        if(readString.indexOf('c') >0) { 
      posc = readString.toInt();
      torcaoPulso(posc, 50);
    }
        if(readString.indexOf('b') >0) { 
      posb = readString.toInt();
      Garra(posb, 50);
    }
        if(readString.indexOf('i') >0) { 
      ajuste = readString.toInt();
    }
        if (readString =="w"){
          // Movimenta o Eixo Y (Braco) para a Cima
            posy = posy + intensidade;
            if(posy<0) (posy=0); //Previne valor menor que zero
            if(posy>180) (posy=180); // previne valor maior que 180
            Braco(posy, 50);
    }
        if (readString =="s"){
          // Movimenta o Eixo Y (Braco) para a Baixo
            posy = posy - intensidade;
            if(posy<0) (posy=0); //Previne valor menor que zero
            if(posy>180) (posy=180); // previne valor maior que 180
            Braco(posy, 50);
    }
      if (readString =="a"){
        // Movimenta o Eixo X (Base) para a Esquerda 
            posx = posx + intensidade;
            if(posx<0) (posx=0); //Previne valor menor que zero
            if(posx>180) (posx=180); // previne valor maior que 180
            Base(posx, 50);
    }
      if (readString =="d"){
        // Movimenta o Eixo X (Base) para a Direita 
            posx = posx - intensidade;
            if(posx<0) (posx=0); //Previne valor menor que zero
            if(posx>180) (posx=180); // previne valor maior que 180
            Base(posx, 50);
    }
    if (readString =="t"){
        // Movimenta o Eixo Z (Antebraco) para a cima 
            posz = posz + intensidade;
            if(posz<0) (posz=0); //Previne valor menor que zero
            if(posz>180) (posz=180); // previne valor maior que 180
            Antebraco(posz, 70);
    }
    if (readString =="g"){
        // Movimenta o Eixo Z (Antebraco) para a baixo 
            posz = posz - intensidade;
            if(posz<0) (posz=0); //Previne valor menor que zero
            if(posz>180) (posz=180); // previne valor maior que 180
            Antebraco(posz, 50);
    }
    if (readString =="r"){
        // Movimenta o Eixo W (Pulso) para a cima 
            posw = posw + intensidade;
            if(posw<0) (posw=0); //Previne valor menor que zero
            if(posw>180) (posw=180); // previne valor maior que 180
            Pulso(posw, 50);
    }
    if (readString =="f"){
        // Movimenta o Eixo W (Pulso) para a baixo 
            posw = posw - intensidade;
            if(posw<0) (posw=0); //Previne valor menor que zero
            if(posw>180) (posw=180); // previne valor maior que 180
            Pulso(posw, 50);
    }
      if (readString =="h"){
        // Movimenta o Eixo C (TorcaoPulso) para a Esquerda 
            posc = posc + intensidade;
            if(posc<0) (posc=0); //Previne valor menor que zero
            if(posc>180) (posc=180); // previne valor maior que 180
            torcaoPulso(posc, 50);
    }
      if (readString =="g"){
        // Movimenta o Eixo C (TorcaoPulso) para a Direita 
            posc = posc - intensidade;
            if(posc<0) (posc=0); //Previne valor menor que zero
            if(posc>180) (posc=180); // previne valor maior que 180
            torcaoPulso(posc, 50);
    }
      if (readString =="help"){
        Help();
    }
    
    if (readString =="q"){
        Serial.println("eixo X (Base) em: ");
        Serial.println(posx);
        Serial.println("eixo Y (Braco) em: ");
        Serial.println(posy);
        Serial.println("eixo Z(Antebraco) em: ");
        Serial.println(posz);
        Serial.println("eixo W(Pulso) em: ");
        Serial.println(posw);
        Serial.println("eixo C(Torcao Pulso) em: ");
        Serial.println(posc);
        Serial.println("eixo B(Garra) em: ");
        Serial.println(posb);
        Serial.println("ajuste do Eixo Y em: ");
        Serial.println(ajuste);
    }
  }
       }
  readString=""; //empty for next input
}
