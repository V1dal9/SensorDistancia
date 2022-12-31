#define TRIG_PIN 13
#define ECHO_PIN 14
unsigned long InicialTimeSonar;
unsigned long CurrentTimeSonar;
unsigned long InicialTimeContador;
unsigned long CurrentTimeContador;
unsigned long tempo;
int contar = 0;
long Distancia;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(115200);
  InicialTimeSonar = micros();
  InicialTimeContador = millis();
  digitalWrite(TRIG_PIN, HIGH); 
}

void loop() {
  CurrentTimeSonar = micros();
  CurrentTimeContador = millis();
  contar++;
  if(CurrentTimeSonar - InicialTimeSonar >= 67000){
    digitalWrite(TRIG_PIN, LOW); 
    tempo = pulseIn(ECHO_PIN, HIGH);
    digitalWrite(TRIG_PIN, HIGH);
    Distancia = tempo * 0.017;
    Serial.print("\nDistancia: \n");
    Serial.print(Distancia);
    InicialTimeSonar += 67000;
    Serial.print("\n\n");
  }
  if(CurrentTimeContador - InicialTimeContador >= 1000){
    Serial.print("\nContador: \n");
    Serial.print(contar);
    contar = 0;
    InicialTimeContador += 1000;   
  } 
}
