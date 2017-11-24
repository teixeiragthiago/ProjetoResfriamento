#include <LiquidCrystal.h>                 //biblioteca do LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int lm35 = 0;     //definindo o estado inicial do sensor LM35
float temp = 0;   //definindo o estado inicial da TEMPERATURA
int ADClido = 0; // definindo o estado do ADClido
int buzzer = 6;  // definindo porta do buzzer 
int cooler = 13; //definindo a porta do cooler
int led = 10;


// definindo portas, entradas/saidas
void setup() {
  lcd.begin(16, 2);     
  Serial.begin(9600);  
  analogReference(INTERNAL);  
  pinMode(cooler, OUTPUT);     
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
}

void loop() {

  // Cálculos de temperatura
  ADClido = analogRead(lm35);
  temp = ADClido * 0.1075268817;
 
  //Mostrando no Monitor Serial as temperaturas  
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.println(" Graus");
  delay(1000);
  
  mostraTempDisplay();  

  controlador(); 

//Controles do Buzzer, Cooler, LCD, LED terminam aqui
  
} 


// Funções para controles de Buzzer, Cooler, LED etc -
void controlador()
{
   if(temp <= 40.00)
  {
        noTone(buzzer);
        digitalWrite(cooler, HIGH);
        digitalWrite(led, HIGH);    
        lcd.clear();
        mostraMsgOff();
  }
  else
    {
        tone(buzzer, 1000);
        delay(1000);
        digitalWrite(cooler, LOW);
        digitalWrite(led, LOW);
        mostraMsgOn();     
    }
}


// Funções para controles de Buzzer, Cooler, LED etc terminam aqui!



// Funções de mensagem para o Display começam aqui!

void mostraTempDisplay()
{
  lcd.clear();          //limpa o display do LCD.     
  lcd.print("Termometro  ");  //imprime a string no display do LCD.
  delay(2000);
  lcd.clear();
  
  lcd.print("Temperatura: "); //imprime a string no display do LCD.
  delay(2000);    

  lcd.clear();
  lcd.print(temp);
  lcd.setCursor(0,1);
  lcd.println("graus celsius C");
  delay(5000);
  
}

void mostraMsgOff()  
{
        lcd.print("SISTEMA DE REFRIGERAMENTO DESATIVADO!");
        delay(1000);
    
        for (int i = 0; i < 21; i++)
        {
           lcd.scrollDisplayLeft();
           delay(300);
        }
}

void mostraMsgOn() 
{
         
        lcd.clear();
        lcd.println("SISTEMA DE RESFRIAMENTO ATIVADO!");
        delay(1000);
        
        //Rolando o display para a esquerda 12 vezes
        for (int i = 0; i < 18; i++)
        {
           lcd.scrollDisplayLeft();
           delay(300);
        } 
}

//Funcoes de mensagem para o Display terminam aqui




