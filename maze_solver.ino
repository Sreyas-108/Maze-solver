int relay1=6;
int relay2=9;
int relay3=5;
int relay4=3;
int echo_front=7;
int trig_front=8;
int echo_left=10;
int trig_left=11;
int echo_right=12;
int trig_right=13;

long time_front,distance_front,minimum_front,distance_left,minimum_left,time_left,distance_right,minimum_right,time_right;
int note=0;
boolean deadend=false;
  
void setup()
{
  Serial.begin(9600);
  pinMode(trig_front,OUTPUT);
  pinMode(echo_front,INPUT);
  pinMode(trig_left,OUTPUT);
  pinMode(echo_left,INPUT);
  pinMode(trig_right,OUTPUT);
  pinMode(echo_right,INPUT);
  
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  pinMode(relay4,OUTPUT);
}

void loop() 
{
      
    sensor_front();
    sensor_left();
    sensor_right();
    forward_robot();
    Serial.println("Robot Forward1");
    
    
    if(distance_front<=minimum_front&&distance_right<=minimum_right)
    {
       reverse_robot();
       turn_left();
       note=-1;
       Serial.println("Robot Left1");
    }
    else if(distance_left>=minimum_left)
    {
      reverse_robot();
      turn_left();
      note=-1;
      Serial.println("Robot Left1");
      
    }
    else if(distance_right>=minimum_right&&distance_front<=minimum_front)
    {
      reverse_robot();
      turn_right();
      note=1;
      Serial.println("Robot Right1");
      
    }
    else if((distance_left<=minimum_left)&&(distance_right<=minimum_right))
    {
      deadend=true;
      while(distance_left>=minimum_left||distance_right>=minimum_right)
      {
        reverse_robot();
        Serial.println("Robot Back1");
        sensor_front();
        sensor_left();
        sensor_right();
      }
      if(distance_left>=minimum_left&&distance_right>=minimum_right)
      {
        turn_right();
        Serial.println("Robot right");
      }
      else if(distance_left>=minimum_left)
      {
        turn_left();
        Serial.println("Robot Left");
      }
      else
      {
        turn_right();
        Serial.println("Robot right");
      }
    }
}

void sensor_front()
{
digitalWrite(trig_front, LOW); 
delayMicroseconds(2);
digitalWrite(trig_front, HIGH); 
delayMicroseconds(20);
digitalWrite(trig_front, LOW);
 
time_front=pulseIn(echo_front,HIGH);
distance_front=time_front/58.2;
Serial.println("distance front=");
Serial.println(distance_front);
delayMicroseconds(10);
minimum_front=10;  
}

void sensor_left()
{
digitalWrite(trig_left, LOW); 
delayMicroseconds(2);
digitalWrite(trig_left, HIGH); 
delayMicroseconds(20);
digitalWrite(trig_left, LOW);
 
time_left=pulseIn(echo_left,HIGH);
distance_left=time_left/58.2;
Serial.println("distance left=");
Serial.println(distance_left);
delayMicroseconds(10);
minimum_left=10;    
}

void sensor_right()
{
digitalWrite(trig_right, LOW); 
delayMicroseconds(2);
digitalWrite(trig_right, HIGH); 
delayMicroseconds(20);
digitalWrite(trig_right, LOW);
 
time_right=pulseIn(echo_right,HIGH);
distance_right=time_right/58.2;
Serial.println("distance right=");
Serial.println(distance_right);
delayMicroseconds(10);
minimum_right=10;    
}



void forward_robot()
{
 analogWrite(relay1,0); 
 analogWrite(relay2,255);
 analogWrite(relay3,0);
 analogWrite(relay4,255);
 delay(500);
}

void reverse_robot()
{
 analogWrite(relay1,255); 
 analogWrite(relay2,0);
 analogWrite(relay3,255);
 analogWrite(relay4,0);
 delay(500);
}
void stop_robot()
{
 analogWrite(relay1,0); 
 analogWrite(relay2,0);
 analogWrite(relay3,0);
 analogWrite(relay4,0);
 delay(500);
}

void turn_left()
{
 analogWrite(relay1,255); 
 analogWrite(relay2,0);
 analogWrite(relay3,0);
 analogWrite(relay4,255);
 delay(4);
}

void turn_right()
{
 analogWrite(relay1,0); 
 analogWrite(relay2,255);
 analogWrite(relay3,255);
 analogWrite(relay4,0);
 delay(4);
}
