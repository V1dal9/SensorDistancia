#define TRIG_PIN 13
#define ECHO_PIN 14
#define LED_PIN 12
long tempo;
volatile long Distancia;
int luz;
bool disparar;
hw_timer_t*timer_n = NULL;
unsigned long InicialTimeSonar;
unsigned long FinalTimeSonar;
bool novaDistancia;


void IRAM_ATTR trig(){
  digitalWrite(TRIG_PIN, disparar);
  disparar = !disparar;
}

void IRAM_ATTR echo(){
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
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  timer_n = timerBegin(0, 80, true);
  timerAttachInterrupt(timer_n, trig, true);
  timerAlarmWrite(timer_n, 67000, 1);
  timerAlarmEnable(timer_n);
  ledcSetup(0, 1000, 8);
  ledcAttachPin(LED_PIN, 0);
  attachInterrupt(ECHO_PIN, echo, CHANGE); 
  digitalWrite(TRIG_PIN, HIGH);
  
}

void loop() {
  if(novaDistancia == true){
    Distancia = tempo * 0.017;
    if(Distancia < 3){
      Distancia = 0;     
    }
    else if(Distancia > 399){
      Distancia = 400;
    }
    Serial.print("\nDistancia:");
    Serial.print(Distancia);    
    Serial.print("\nLuz:");
    Serial.print(luz);
  }
  luz = (((Distancia - 3) * (255 - 0)) / ((400 - 3) + 0));
  ledcWrite(0, luz);
}
  
