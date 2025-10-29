// Defines the pins for the ultrasonic sensor.
#define trigPin 12;
#define echoPin 14;
#define buzzer 25;
// Declares the variables.
long duration;
long distance;

void setup() {
  // Sets the trigger pin as an OUTPUT and the echo pin as an INPUT.
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Initializes serial communication for printing distance.
  Serial.begin(115200);
}

void loop() {
  // Clears the trigPin to ensure a clean start.
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin HIGH for 10 microseconds to send the ultrasonic pulse.
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measures the duration of the echo pulse.
  duration = pulseIn(echoPin, HIGH);
  
  // Calculates the distance based on the speed of sound.
  // The speed of sound is approximately 0.034 cm/microsecond.
  // The pulse travels to the object and back, so we divide the result by 2.
  distance = duration * 0.034 / 2;
  
  // Prints the distance to the Serial Monitor.
  Serial.print("The distance is: ");
  Serial.print(distance);
  Serial.println(" cm");

  if(distance < 30){
    switch(distance){
      
      case 0 ... 10:
      digitalWrite(buzzer,HIGH);
      delay(10);
      digitalWrite(buzzer,LOW);
      break;

      case 11 ... 20:
      digitalWrite(buzzer,HIGH);
      delay(5);
      digitalWrite(buzzer,LOW);
      break;

      case 21 ... 30:
      digitalWrite(buzzer,HIGH);
      delay(2);
      digitalWrite(buzzer,LOW);
      break;


    }
  }
  
  delay(100); // Wait between measurements.
}
