// Simon.ino game

#define NOTE1 165 // blue tone: E 3
#define NOTE2 139 // yellow tone: C♯ 3
#define NOTE3 220 // red tone: A 3
#define NOTE4 82 // green tone: E 2 

#define LED1 8 // blue button
#define LED2 9 // yellow button
#define LED3 10 // red button
#define LED4 11 // green button

#define BUTTON1 4 // blue LED
#define BUTTON2 5 // yellow LED
#define BUTTON3 6 // red LED
#define BUTTON4 7 // green LED

#define BUZZER 2

// define variables 
int sequence[100];
int sequenceLength = 0;
int currentIndex = 0;
int prevNumber = 0;
int randomNumber = random(1, 5);
int error = 0;

void setup()
{
  // Initialize buttons
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  pinMode(BUTTON4, INPUT_PULLUP);

  // Initialize LEDs
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  // initialize BUZZER
  pinMode(BUZZER, OUTPUT);

  // Play initial sequence
  playNote(LED1, NOTE1);
  playNote(LED2, NOTE2);
  playNote(LED3, NOTE3);
  playNote(LED4, NOTE4);

  delay(1000);
}

void addToSequence() {
  // Add random number to sequence
  randomSeed(analogRead(0));
  while (randomNumber == prevNumber) 
    randomNumber = random(1, 5);
  sequence[sequenceLength] = randomNumber;
  sequenceLength++;
  prevNumber = randomNumber;
}

void handleUserInput(int button, int led, int note, int expected) {
  // Read press button, turn on LED and play note
  if (digitalRead(button) == LOW) {
    while (digitalRead(button) == LOW) {
      digitalWrite(led, HIGH);
      tone(BUZZER, note);
    }
    digitalWrite(led, LOW);           
    noTone(BUZZER);
    // Check correct sequence
    if (sequence[currentIndex] == expected) {
      currentIndex++;
    } else {
      error = 1;
      return;
    }
  }
}

void getUserSequence() {
  handleUserInput(BUTTON1, LED1, NOTE1, 1); 
  handleUserInput(BUTTON2, LED2, NOTE2, 2); 
  handleUserInput(BUTTON3, LED3, NOTE3, 3); 
  handleUserInput(BUTTON4, LED4, NOTE4, 4); 
}

void playNote(int led, int note) {
  // Play a note and turn on LED
  digitalWrite(led, HIGH);
  tone(BUZZER, note);
  delay (400);
  digitalWrite(led, LOW);           
  noTone(BUZZER);
}

void playSequence() {
  // Play the sequence
  for (int i = 0; i < sequenceLength; i++) {
    if (sequence[i] == 1) playNote(LED1, NOTE1);
    if (sequence[i] == 2) playNote(LED2, NOTE2);
    if (sequence[i] == 3) playNote(LED3, NOTE3);
    if (sequence[i] == 4) playNote(LED4, NOTE4);
    delay(200);
  }
}

void gameOver() {
  // Game over and reset
  delay(500);
  playNote(LED4, NOTE4);
  playNote(LED3, NOTE3);
  playNote(LED2, NOTE2);
  playNote(LED1, NOTE1);

  delay (2000);
  error = 0;
  currentIndex = 0;
  sequenceLength = 0;
}

void loop()
{
  if (error == 0) {
    // Add new note to sequence and play
    addToSequence();
    playSequence();

    // Get user sequence
    while ((currentIndex < sequenceLength) && (error == 0)) {
      getUserSequence();
    }
    currentIndex = 0;
    delay(500);
  }
  else {
    // In case of mistake
    gameOver();
  } 
}
