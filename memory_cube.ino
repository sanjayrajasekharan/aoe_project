
const int BUTTON_PIN = 3;

const int r_LED_PIN = 8;
const int g_LED_PIN = 10;
const int b_LED_PIN = 11;
const int y_LED_PIN = 12;
const int w_LED_PIN = 9;

const int r_BUTTON_PIN = 3;
const int g_BUTTON_PIN = 4;
const int b_BUTTON_PIN = 5;
const int y_BUTTON_PIN = 6;
const int w_BUTTON_PIN = 7;

const int LED_PINS[] = {r_LED_PIN, b_LED_PIN, y_LED_PIN};
const int BUTTON_PINS[] = {r_BUTTON_PIN, b_BUTTON_PIN, y_BUTTON_PIN};
const int NUM_COLORS = 3;

const int INITIAL_LENGTH = 5; //number of flashes
const int INITIAL_DELAY = 400; //milliseconds

const int FINAL_LENGTH = 12;
const int FINAL_DELAY = 100;

const int LEVELS_PER_LENGTH = 2;
const int LEVEL_TIME_DECREMENT = 30;

bool seqRunning = false;
int currentLevel = 0;
int currentTimeDelay = INITIAL_DELAY;

void setup() {
  for (int i = 0; i < NUM_COLORS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    pinMode(BUTTON_PINS[i], INPUT);
  }
  Serial.begin(9600);

}

void loop() {
//  delay(10);
//  if (digitalRead(BUTTON_PIN) == HIGH && !seqRunning) {
//    seqRunning = true;
//    currentLevel++;
//  }
//  if (seqRunning) {
//    play();
//    seqRunning = false;
//  }

    for (int i = 0; i < NUM_COLORS; i++) {
      if(digitalRead(BUTTON_PINS[i]) == HIGH){
        delay(10);
        play();
        currentLevel = 0;
        currentTimeDelay = INITIAL_DELAY;
//        Serial.print("buttonPressed: " + (String) BUTTON_PINS[i] + " ");
//        Serial.println("corresponingLED: " + (String) LED_PINS[i] + " ");
        delay(200);
      }
      
    }

 }

void play() {
  Serial.println("here");
  bool lost = false;
  while(!lost) {
    int currentLevelLength = currentLevel / LEVELS_PER_LENGTH + INITIAL_LENGTH;
    currentTimeDelay -= LEVEL_TIME_DECREMENT;
    if (currentTimeDelay < FINAL_DELAY) currentTimeDelay = FINAL_DELAY;
    
    int sequence[currentLevelLength];
    generateSequence(sequence, currentLevelLength);
    
    runSequence(sequence, currentLevelLength, currentTimeDelay);
    
    lost =  !readSequence(sequence, currentLevelLength);
  }
  gameOver();
}

void generateSequence(int sequence[], int len) {

  for (int i = 0; i < len; i++) {
    sequence[i] = LED_PINS[(int) random(0, NUM_COLORS)];
  }

}

void runSequence(int sequence[], int len, int timeDelay) {
  for (int i = 0; i < len; i++) {
    digitalWrite(sequence[i], HIGH);
    delay(timeDelay);
    digitalWrite(sequence[i], LOW);
    delay(timeDelay);
  }
}

bool readSequence(int sequence[], int len) {
  int counter = 0;
  int alt = 0;
  int desiredPin;
  bool pressed = false;
  for (int i = 0; i < len; i++) {
    Serial.print("ledPin: " + (String) sequence[i] + " ");
    Serial.println("buttonPin: " + (String) matchPin(sequence[i]));
  }
  while(counter < len) {
    desiredPin = matchPin(sequence[counter]);
    Serial.println("Button desired: " + (String) desiredPin);
    for (int i = 0; i < NUM_COLORS; i++) {
      if (digitalRead(BUTTON_PINS[i]) == HIGH) {
        if(BUTTON_PINS[i] == desiredPin){ 
          counter++;
          delay(300);
        }
        else return false;
      }
    }
  }

  flashAllColors();
  return true;

}

int matchPin(int ledPin) {
  if (ledPin == r_LED_PIN) return r_BUTTON_PIN;
  else if (ledPin == g_LED_PIN) return g_BUTTON_PIN;
  else if (ledPin == b_LED_PIN) return b_BUTTON_PIN;
  else if (ledPin == y_LED_PIN) return y_BUTTON_PIN;
  else if (ledPin == w_LED_PIN) return w_BUTTON_PIN;
  else return -1;
}

void flashAllColors() {
  for (int i = 0; i < 3; i++) {
    for (int j =0; j < NUM_COLORS; j++) {
      digitalWrite(LED_PINS[j], HIGH);
    }
    
    delay(currentTimeDelay);
    
    for (int j = 0; j < NUM_COLORS; j++) {
      digitalWrite(LED_PINS[j], LOW);
    }
    
    delay(currentTimeDelay);
  }  
}
void gameOver() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(r_LED_PIN, HIGH);
    delay(300 * i);
    digitalWrite(r_LED_PIN, LOW);
    delay(300 * i);
  }
}
