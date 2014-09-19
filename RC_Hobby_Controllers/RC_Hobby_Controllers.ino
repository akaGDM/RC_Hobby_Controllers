  /*******************************************************************************
   * Project  : RC Car controll using RC radio                                   *
   * Compiler : Arduino 1.5.2                                                    *
   * Board    : Arduino Dudemilanove                                             *
   * Device   : L288 Shield                                                      *
   *          : Servo motor                                                      *
   *          : RC Car with motor                                                *
   * Link     : -                                                                * 
   * Author   : Bavensky :3                                                      *
   * E-Mail   : Aphirak_Sang-ngenchai@hotmail.com                                *
   * Date     : 19/09/2014 [dd/mm/yyyy]                                          *
   *******************************************************************************/
  #include <Servo.h>
  
  // Channel Receive  //
  #define CH1   9
  #define CH2  10
  #define CH3  11
  #define CH4  12
  
  // EN   output PWM
  // IN1  output 0 or 1
  // IN2  output 0 or 1
  // if IN1 active 1 and IN2 active 0 then Forward
  // if IN1 active 0 and IN2 active 1 then Reverse
  #define EN    5
  #define IN1   6
  #define IN2   7

  // variable  //
  Servo servo;
  int roll, pitch, thro, yaw;
  int fw =0; 
  
  void setup() {
    //  begin servo motor  //
    servo.attach(8);
    
    //  Input  //
    pinMode(CH1, INPUT);
    pinMode(CH2, INPUT); 
    pinMode(CH3, INPUT);
    pinMode(CH4, INPUT);
    
    //  Output  //
    pinMode(EN, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
   
  }
   
  void loop() {
    
    // Read from Recive  //
    roll = pulseIn(CH1, HIGH, 25000);
    pitch = pulseIn(CH2, HIGH, 25000); 
    thro = pulseIn(CH3, HIGH, 25000); 
    yaw = pulseIn(CH4, HIGH, 25000);
    
    //  Stop Motor  //
      if(pitch > 1400 && pitch < 1500){
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      analogWrite(EN, 0);
    }
    // Forward //  
    if(pitch > 1500){
      fw = abs(map(pitch, 1500,2000,0,255));
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(EN, fw);
    }
    //  Reverse  //
    if(pitch < 1400){
      fw = abs(map(pitch, 1400,980,0,255));
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      analogWrite(EN, fw);
    }
    
    //  Straight  //
    if(roll > 1400 && roll < 1500){
      servo.write(15);
    }
    //  Turn Right  //
    if(roll > 1500){
      fw = abs(map(roll, 1500,2000,15,0));
      servo.write(fw);
    }
    //  Turn Left  //
    if(roll < 1400){
      fw = abs(map(roll, 1400,980,15,32));
      servo.write(fw);
    }
  }
