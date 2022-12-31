#define TRIG_PIN 13
#define ECHO_PIN 14
unsigned long InicialTime;
unsigned long CurrentTime;
long tempo;
unsigned long tempoSegundos;
unsigned long InicialTimeSonar;
unsigned long FinalTimeSonar;
int contar = 0;
volatile long Distancia;
hw_timer_t*timer_n = NULL;
bool disparar;
bool novaDistancia;


void IRAM_ATTR trig(){
  digitalWrite(TRIG_PIN, disparar);
  disparar = !disparar;
}

void IRAM_ATTR echo(){
  //bool estado = digitalRead(ECHO_PIN);
  if(digitalRead(ECHO_PIN) == HIGH){
    InicialTimeSonar = micros();
  }
  else{
    FinalTimeSonar = micros();
    tempo = FinalTimeSonar - InicialTimeSonar;
    novaDistancia = true;
  }
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(115200);
  InicialTime = millis();
  timer_n = timerBegin(0, 80, true);
  timerAttachInterrupt(timer_n, trig, true);
  timerAlarmWrite(timer_n, 67000, 1);
  timerAlarmEnable(timer_n);
  attachInterrupt(ECHO_PIN, echo, CHANGE); 
  digitalWrite(TRIG_PIN, HIGH);
}

void loop() {
  CurrentTime = millis();
  contar++;
  if(novaDistancia == true){
      Distancia = tempo * 0.017;
    if(Distancia < 3){
       Distancia = 0;
    }
    else if(Distancia > 399){
      Distancia = 400;
    }
  }
  if(CurrentTime - InicialTime >= 1000){
    Serial.print("\nDistancia: \n");
    Serial.print(Distancia);
    Serial.print("\nContador: \n");
    Serial.print(contar);
    Serial.print("\n\n");
    contar = 0;
    InicialTime += 1000;
  }
}
