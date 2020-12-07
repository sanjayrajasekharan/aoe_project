
const int BUTTON_PIN = 3;

const int r_PIN = 8;
const int g_PIN = 10;
const int b_PIN = 11;
const int y_PIN = 12;
const int w_PIN = 9;

const int LED_PINS[] = {r_PIN, g_PIN, g_PIN, y_PIN, w_PIN};
const int NUM_COLORS = 5;

const int INITIAL_LENGTH = 5; //number of flashes
const int INITIAL_DELAY = 400; //milliseconds 

const int FINAL_LENGTH = 20;
const int FINAL_DELAY = 10;

const int LEVELS_PER_LENGTH = 2;
const int LEVEL_TIME_DECREMENT = 30;

bool seqRunning = false;
int currentLevel = 0;
int currentTimeDelay = INITIAL_DELAY;

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  for (int i = 0; i < NUM_COLORS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
  Serial.begin(9600); 
  

}

void loop() {
  
  delay(10);
  if(digitalRead(BUTTON_PIN) == HIGH && !seqRunning){ 
    seqRunning = true;
    currentLevel++;
    }
  if(seqRunning){

    play();
    seqRunning = false;
  }
  
//  Serial.print(digitalRead(BUTTON_PIN));
}

void play() {
  int currentLevelLength = currentLevel/LEVELS_PER_LENGTH + INITIAL_LENGTH;
  currentTimeDelay -= LEVEL_TIME_DECREMENT;
  if(currentTimeDelay < FINAL_DELAY) currentTimeDelay = FINAL_DELAY;
  int sequence[currentLevelLength];
  generateSequence(sequence, currentLevelLength);
  runSequence(sequence, currentLevelLength, currentTimeDelay);
  readSequence(sequence);
}

void generateSequence(int sequence[], int len){
  
  for (int i = 0; i < len; i++) {
      sequence[i] = LED_PINS[random(0, NUM_COLORS)];
  }
  
}

void runSequence(int sequence[], int len, int timeDelay) {
  for (int i = 0; i <len; i++) {
    digitalWrite(sequence[i], HIGH);
    delay(timeDelay);
    digitalWrite(sequence[i], LOW);
    delay(timeDelay);
  }
}

bool readSequence(int sequence[], int len) {
  
}

int readPress() {
  for(int i = 0; i < NUM_COLORS; i++) {
    if (digitalRead(LED_PINS[i]) == HIGH) return i;
  } 
  return -1; 
}
