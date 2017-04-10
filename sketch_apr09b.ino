float Kp=50,Ki=20,Kd=2;
float error=0, P=0, I=0, D=0, PID_value=0;
float previous_error=0, previous_I=0;
float s[6]={0, 0, 0, 0, 0, 0};
int initial_motor_speed=180;
void read_sensor_values();
void calculate_pid();
void motor_control();
int left_motor_speed;
int right_motor_speed;
void setup()
{
 pinMode(11,OUTPUT); //PWM Pin 1
 pinMode(10,OUTPUT); //PWM Pin 2
 pinMode(13,OUTPUT);//Right Motor Pin1
 pinMode(12,OUTPUT);//Right Motor Pin2
 pinMode(9,OUTPUT);//Left Motor Pin1
 pinMode(8,OUTPUT);//Left Motor Pin2
 pinMode(A0,INPUT);
 pinMode(A1,INPUT);
 pinMode(A2,INPUT);
 pinMode(A3,INPUT);/*
 pinMode(A4,INPUT);
 pinMode(A5,INPUT);*/
 digitalWrite(13,HIGH);
 digitalWrite(12,LOW);

 
 digitalWrite(9,HIGH);
 digitalWrite(8,LOW);
}

void loop()
{
   read_sensor_values();
   calculate_pid();
   motor_control();
}

void read_sensor_values()
{
  s[0]=analogRead(A0);
  s[1]=analogRead(A1);
  s[2]=analogRead(A2);
  s[3]=analogRead(A3);/*
  s[4]=analogRead(A4);
  s[5]=analogRead(A5);*/
  error=((-2.3*s[3]-0.6*s[2]+0.6*s[1]+2.3*s[0])/(s[0]+s[1]+s[2]+s[3]));
  
}

void calculate_pid()
{
    P = error;
    I = I + previous_I;
    D = error-previous_error;
    
    PID_value = (Kp*P) + (Ki*I) + (Kd*D);
    
    previous_I=I;
    previous_error=error;
    /*Serial.print("P=");
    Serial.println(P);
    Serial.print("I=");
    Serial.println(I);
    Serial.print("D=");
    Serial.println(D);
    Serial.print("PID_value =");
    Serial.println(PID_value);*/
}

void motor_control()
{
    // Calculating the effective motor speed:
    left_motor_speed = initial_motor_speed-PID_value;
    right_motor_speed = initial_motor_speed+PID_value;
    
    // The motor speed should not exceed the max PWM value
    /*constrain(left_motor_speed,0,255);
    constrain(right_motor_speed,0,255);*/
    if(left_motor_speed<0)
    left_motor_speed=0;
    else if(left_motor_speed>255)
    left_motor_speed=255;
    if(right_motor_speed<0)
    right_motor_speed=0;
    else if(right_motor_speed>255)
    right_motor_speed=255;
    analogWrite(11,left_motor_speed);   //Left Motor Speed
    analogWrite(10,right_motor_speed);
   /* Serial.print("left: ");
    Serial.println(left_motor_speed);
    Serial.print("right: ");//Right Motor Speed
    Serial.println(right_motor_speed);*/
    //following lines of code are to make the bot move forward 
   
 /* The pin numbers and high, low values might be different
    depending on your connections */
 /* digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,HIGH);*/
}
