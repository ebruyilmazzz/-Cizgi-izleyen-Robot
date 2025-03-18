 int led=A1,bt=A2;
int R_mt_b=9;
int R_mt_a=6;
int L_mt_a=10;
int L_mt_b=11;
int bt_s=1;
int yon=0;
int L3=A0;
int L2=A3;
int L1=8;
int L0=7;
int R0=5;
int R1=4;
int R2=3;
int R3=2;
int e=0,sayac=0;
int PD,P,D,e0,d_e;
int kp=10,kd=5;
int hiz1=0,hiz2=0;
int base_L=100,base_R=100;
char kavsak;
#define bekle 1000
void sensor_oku(){
  e0=e;
  e=0;
  sayac=0;
  if(digitalRead(L3)==1){Serial.print(1);sayac++;e=e-7;}
  else Serial.print(0);
  if(digitalRead(L2)==1){Serial.print(1);sayac++;e=e-5;}
  else Serial.print(0);
  if(digitalRead(L1)==1){Serial.print(1);sayac++;e=e-3;}
  else Serial.print(0);
  if(digitalRead(L0)==1){Serial.print(1);sayac++;e=e-1;}
  else Serial.print(0);
  if(digitalRead(R0)==1){Serial.print(1);sayac++;e=e+1;}
  else Serial.print(0);
  if(digitalRead(R1)==1){Serial.print(1);sayac++;e=e+3;}
  else Serial.print(0);
  if(digitalRead(R2)==1){Serial.print(1);sayac++;e=e+5;}
  else Serial.print(0);
  if(digitalRead(R3)==1){Serial.println(1);sayac++;e=e+7;}
  else Serial.println(0);
  if(sayac>0) e=e/sayac;
  else e=0;
  //else if(e0<0) e=-9;
  //else e=9;
  P=e*kp;
  d_e=e0-e;
  D=d_e*kd;
  PD=P+D;
  
}

void motor(int h1, int h2){
 if(h1>0){
    digitalWrite(L_mt_a,0);analogWrite(L_mt_b,h1);
  }
 else{
    digitalWrite(L_mt_b,0);analogWrite(L_mt_a,abs(h1));
  } 
 if(h2>0){
    digitalWrite(R_mt_a,0);analogWrite(R_mt_b,h2);
  }
 else{
    digitalWrite(R_mt_b,0);analogWrite(R_mt_a,abs(h2));
  }  
  
}

void ses(int gl){
  for(int i=0;i<gl;i++){
    digitalWrite(led,1);delay(300); digitalWrite(led,0);delay(300); 
    }
  
  }
void azgit(){
  motor(60,60);delay(220); motor(0,0);delay(1500);
  }
void ileri(){
  motor(60,60);delay(200); motor(0,0);delay(bekle);
  }
 void geri(){
  soladon();
  }
void sagadon(){
  motor(80,-80);
  while(digitalRead(R3)==0);
  motor(50,-50);
  while(digitalRead(L0)==0);
  delay(100);
  motor(0,0);delay(bekle);
  }
void soladon(){
  motor(-80,80);
  while(digitalRead(L3)==0);
  motor(-50,50);
  while(digitalRead(R0)==0);
  delay(100);
  motor(0,0);delay(bekle);
  }
void soltakip(){
  if(kavsak=='c' ||kavsak=='t'||kavsak=='l') soladon();
  else if(kavsak=='r') ileri();
  else if(kavsak=='x') geri();
  }
  
void setup() {
  Serial.begin(9600);
pinMode(led,OUTPUT);
pinMode(L_mt_a,OUTPUT);pinMode(L_mt_b,OUTPUT);pinMode(R_mt_a,OUTPUT);pinMode(R_mt_b,OUTPUT);
pinMode(L3,INPUT);pinMode(L2,INPUT);pinMode(L1,INPUT);pinMode(L0,INPUT);pinMode(R3,INPUT);pinMode(R2,INPUT);pinMode(R1,INPUT);pinMode(R0,INPUT);
pinMode(bt,INPUT_PULLUP);

bt_s=digitalRead(bt);
while(bt_s==1){bt_s=digitalRead(bt); sensor_oku();}
for(int i=0;i<1;i++){
  digitalWrite(led,1);delay(300);
  digitalWrite(led,0);delay(300);
  }
delay(500);
}

void loop() {
//motor(150,100);while(1);
sensor_oku();

if(sayac>5){
    azgit();
    sensor_oku();  
    if(sayac==0) {ses(4); kavsak='t';}
    else {kavsak='c';ses(1);}
    delay(bekle);
    soltakip();  
 }
else if(sayac>3) {
    azgit(); 
    yon=e;
    sensor_oku();
    if(sayac==0) {
      if (yon<0) soladon();
      else if (yon>0)sagadon();
      }
     else{
      if (yon<0) {kavsak='l';ses(3);}
      else if (yon>0) {ses(2);kavsak='r';}
     }
//while(digitalRead(bt));
delay(bekle);
soltakip();

}

else if(sayac==0){
  azgit();
  sensor_oku();kavsak='x';
  if(sayac==0) {digitalWrite(led,1);delay(1000);digitalWrite(led,0);
  //while(digitalRead(bt));
  delay(bekle);
  soltakip();

  }}
//Serial.print("Sol:");Serial.print(100+PD);
//Serial.print("  Sag:");Serial.println(110-PD);
if(PD<0){hiz1=base_L+PD;hiz2=base_R;}
else {hiz1=base_L;hiz2=base_R-PD;}
if(hiz1>255) hiz1=255;
if(hiz2>255) hiz2=255;
if(hiz1<-55) hiz1=-255;
if(hiz2<-55) hiz2=-255;


motor(hiz1,hiz2);
//delay(200);

}
