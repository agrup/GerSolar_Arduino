#include <SD.h>

File myFile;
int ledBlue = 43; //Define the LED pin
int ledRed = 41; //Define the LED pin
int buttonpin = 3; //Define the push button pin
int val; //Define a numeric variable
bool isSaving =false;

int pinCS = 53;

void setup()
{
  Serial.begin(9600);

  pinMode(pinCS,OUTPUT);
  
  Serial.print("Iniciando SD ...");
  if (!SD.begin(53)) {
    Serial.println("No se pudo inicializar");
    return;
  }
  Serial.println("inicializacion exitosa");
 
  myFile = SD.open("datalog.txt");//abrimos  el archivo 
  if (myFile) {
    Serial.println("datalog.txt:");
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    myFile.print("AGU GRIOSO ");
    myFile.close(); //close file
  } else {
    Serial.println("Error al abrir el archivo");
  }
  
  digitalWrite(ledRed,HIGH);//Led red ON
  
  
}

void loop()
{
  
  val = digitalRead(buttonpin); // check the state of the button
  if(val==LOW) // if button is pressed, turn LED on
  {
    if(isSaving){
      digitalWrite(ledRed,LOW);  
      digitalWrite(ledBlue,HIGH);  
      
      Serial.println("Deja de grabar");
      delay(500);
    }
    else
    {
      digitalWrite(ledRed,HIGH);  
      digitalWrite(ledBlue,LOW);

      Serial.println("Vuelve a grabar");
      delay(500);
    }
    Serial.println("out");
    isSaving = !isSaving;
    delay(500);
  }
  else
  {
    if (isSaving) {
        if (!SD.begin(53)) {
          Serial.println("initialization failed!");
          //while (1);
        }
      myFile = SD.open("datalog.txt", FILE_WRITE);//Open File datalog.txt
  
      if(myFile){
        myFile.println("agu");
        Serial.println("dump");
        myFile.close();
        delay(500);
     }
     else
     {

      delay(200);
     }
    }
  }

}
