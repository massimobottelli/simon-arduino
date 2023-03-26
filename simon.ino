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

// define sequence 
int sequence[100];
int sequenceLength = 0;
int currentIndex = 0;
int error = 0;
int prevNumber = 0;
int randomNumber = random(1, 5);


void play(int led, int note) {
  digitalWrite(led, HIGH);
  tone(BUZZER, note);
  delay (400);
  digitalWrite(led, LOW);           
  noTone(BUZZER);
}

void setup()
{
  Serial.begin(9600);

  // initialize buttons
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  pinMode(BUTTON4, INPUT_PULLUP);

  // initialize LEDs
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  
  // initialize BUZZER
  pinMode(BUZZER, OUTPUT);

  // initial sequence
  play(LED1, NOTE1);
  play(LED2, NOTE2);
  play(LED3, NOTE3);
  play(LED4, NOTE4);

  delay(1000);
}


void loop()
{
  if (error == 0) {
    
  // add random number to sequence
  randomSeed(analogRead(0));
  while (randomNumber == prevNumber) 
    randomNumber = random(1, 5);
  sequence[sequenceLength] = randomNumber;
  sequenceLength++;
  prevNumber = randomNumber;
  }
  else {
    
    // Game over and reset
    delay(500);
    play(LED4, NOTE4);
    play(LED3, NOTE3);
    play(LED2, NOTE2);
    play(LED1, NOTE1);
    
    Serial.println("Game over");
    delay (2000);
    error = 0;
    currentIndex = 0;
    sequenceLength = 0;
    // add random number to sequence
    randomSeed(analogRead(0));
    int randomNumber = random(1, 5);
    sequence[sequenceLength] = randomNumber;
    sequenceLength++;
  }
  
  // Print the sequence to console
  Serial.print("Sequence: ");
  for (int i = 0; i < sequenceLength; i++) {
    Serial.print(sequence[i]);
    Serial.print(" ");
  }
  Serial.println();
  
  // Play the sequence
  for (int i = 0; i < sequenceLength; i++) {
	  if (sequence[i] == 1) play(LED1, NOTE1);
    if (sequence[i] == 2) play(LED2, NOTE2);
    if (sequence[i] == 3) play(LED3, NOTE3);
    if (sequence[i] == 4) play(LED4, NOTE4);
    delay(200);
  }
  
  // Get user sequence
  while ((currentIndex < sequenceLength) && (error == 0)) {

    // Check if any button is pressed
    
    if (digitalRead(BUTTON1) == LOW) {
      // Button 1 is pressed
      Serial.println("1");
      
      while (digitalRead(BUTTON1) == LOW) {
        digitalWrite(LED1, HIGH);
        tone(BUZZER, NOTE1);
      }
      digitalWrite(LED1, LOW);           
      noTone(BUZZER);
      
      if (sequence[currentIndex] == 1) {
        // Correct button pressed
        currentIndex++;
      } else {
        // Incorrect button pressed
        Serial.println("Error");
        error = 1;
        return;
      }
    delay(100);
      
    } else if (digitalRead(BUTTON2) == LOW) {
      // Button 2 is pressed
      Serial.println("2");  
      
      while (digitalRead(BUTTON2) == LOW) {
        digitalWrite(LED2, HIGH);
        tone(BUZZER, NOTE2);
      }
      digitalWrite(LED2, LOW);           
      noTone(BUZZER);  
      
      if (sequence[currentIndex] == 2) {
        // Correct button pressed
        
        currentIndex++;
      } else {
        // Incorrect button pressed
        Serial.println("Error");
        error = 1;
        return;
      }
    delay(100);
      
    } else if (digitalRead(BUTTON3) == LOW) {
      // Button 3 is pressed
      Serial.println("3");
      
      while (digitalRead(BUTTON3) == LOW) {
        digitalWrite(LED3, HIGH);
        tone(BUZZER, NOTE3);
      }
      digitalWrite(LED3, LOW);           
      noTone(BUZZER);  
      
      if (sequence[currentIndex] == 3) {
        // Correct button pressed
        currentIndex++;
      } else {
        // Incorrect button pressed
        Serial.println("Error");
        error = 1;
        return;
      }
    delay(100);
      
    } else if (digitalRead(BUTTON4) == LOW) {
      // Button 4 is pressed
      Serial.println("4");
      
      while (digitalRead(BUTTON4) == LOW) {
        digitalWrite(LED4, HIGH);
        tone(BUZZER, NOTE4);
      }
      digitalWrite(LED4, LOW);           
      noTone(BUZZER);
      
      if (sequence[currentIndex] == 4) {
        // Correct button pressed
        currentIndex++;
      } else {
        // Incorrect button pressed
        Serial.println("Error");
        error = 1;
        return;
      }
    delay(100);
    }
  }
  
  if (error == 0) {
    // sequence correct, add one number
    Serial.println("Sequence correct, add one number");
    currentIndex = 0;
    
    delay(500);

  }
}
  
  
  
  
