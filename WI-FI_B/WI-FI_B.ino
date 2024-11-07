/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL4vIsHY9dK"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "3aqnTjMF_ttgNUVWqzPHh-yefziQn1dq"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Xiaomi_oleg_Plus";
char pass[] = "MoBB5369814";

BlynkTimer timer;




const uint8_t SELECTED_PIN = D1;
const uint8_t BUTTON_PIN = D2;

unsigned long pressStart = 0;
unsigned long unpressStart = 0;
unsigned long pressDuration = 0;
unsigned long unpressDuration = 0;
bool firstPress = false;
bool isPressed = false;
String morseCode = "";
String wordOut = "";

String receivedWord = "";





void setup() {
  pinMode(SELECTED_PIN, OUTPUT);  // Ініціалізуємо світлодіод як вихід
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Ініціалізуємо кнопку як вхід з підтягувальним резистором
  Serial.begin(9600);  // Запускаємо серійну передачу для налагодження
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 8080);

}



// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}



BLYNK_WRITE(V1) {
  String receivedWordTest = param.asStr();  // Get the word from ESP8266 A
  Serial.println("Received word: " + receivedWordTest);
  stringToMorse(receivedWordTest, SELECTED_PIN);
}


String morseToWord(String morseCode){
  String letterMorse;
  String word;
  for(int i=0;i<morseCode.length();i++){
    if(morseCode.charAt(i)!= ' ' || morseCode.charAt(i)== '.' || morseCode.charAt(i)== '-'){
      letterMorse += morseCode.charAt(i);
    }
    if(morseCode.charAt(i) == ' '){
      // append founded word to return and clean String letterMorse
        if(letterMorse== ".-")
         word+= "A";
          else
        if(letterMorse== "-...")
         word+= "B";
          else
        if(letterMorse== "-.-.")
         word+= "C";
          else
        if(letterMorse== "-..")
         word+= "D";
          else
        if(letterMorse== ".")
         word+= "E";
          else
        if(letterMorse== "..-.")
         word+= "F";
          else
        if(letterMorse== "--.")
         word+= "G";
          else
        if(letterMorse== "....")
         word+= "H";
          else
        if(letterMorse== "..")
         word+= "I";
          else
        if(letterMorse== ".---")
         word+= "J";
          else
        if(letterMorse== "-.-")
         word+= "K";
          else
        if(letterMorse== ".-..")
         word+= "L";
          else
        if(letterMorse== "--")
         word+= "M";
          else
        if(letterMorse== "-.")
         word+= "N";
          else
        if(letterMorse== "---")
         word+= "O";
          else
        if(letterMorse== ".--.")
          word+= "P";
          else
        if(letterMorse== "--.-")
         word+= "Q";
          else
        if(letterMorse== ".-.")
         word+= "R";
          else
        if(letterMorse== "...")
         word+= "S";
          else
        if(letterMorse== "-")
         word+= "T";
          else
        if(letterMorse== "..-")
         word+= "U";
          else
        if(letterMorse== "...-")
         word+= "V";
          else
        if(letterMorse== ".--")
         word+= "W";
          else
        if(letterMorse== "-..-")
         word+= "X";
          else
        if(letterMorse== "-.--")
         word+= "Y";
          else
        if(letterMorse== "--..")
         word+= "Z";
      letterMorse = "";
    }
  }
  return word;
} 

void stringToMorse(String data, uint8_t PIN_N){
  delay(500);  // Small pause before starting the Morse code
  data.toUpperCase();
  for (int i = 0; i < data.length(); i++) {
    switch (data.charAt(i)) {
      case 'A':
        LED_D(PIN_N);  // dot
        LED_L(PIN_N);  // dash
        break;
      case 'B':
        LED_L(PIN_N);  // dash
        LED_D(PIN_N);  // dot
        LED_D(PIN_N);  // dot
        LED_D(PIN_N);  // dot
        break;
      case 'C':
        LED_L(PIN_N);  // dash
        LED_D(PIN_N);  // dot
        LED_L(PIN_N);  // dash
        LED_D(PIN_N);  // dot
        break;
      case 'D':
        LED_L(PIN_N);  // dash
        LED_D(PIN_N);  // dot
        LED_D(PIN_N);  // dot
        break;
      case 'E':
        LED_D(PIN_N);  // dot
        break;
      case 'F':
        LED_D(PIN_N);  // dot
        LED_D(PIN_N);  // dot
        LED_L(PIN_N);  // dash
        LED_D(PIN_N);  // dot
        break;
      case 'G':
        LED_L(PIN_N);  // dash
        LED_L(PIN_N);  // dash
        LED_D(PIN_N);  // dot
        break;
      case 'H':
        LED_D(PIN_N);  // dot
        LED_D(PIN_N);  // dot
        LED_D(PIN_N);  // dot
        LED_D(PIN_N);  // dot
        break;
      case 'I':
        LED_D(PIN_N);  // dot
        LED_D(PIN_N);  // dot
        break;
      case 'J':
        LED_D(PIN_N);  // dot
        LED_L(PIN_N);  // dash
        LED_L(PIN_N);  // dash
        LED_L(PIN_N);  // dash
        break;
      case 'K':
        LED_L(PIN_N);  // dash
        LED_D(PIN_N);  // dot
        LED_L(PIN_N);  // dash
        break;
      case 'L':
        LED_D(PIN_N);  // dot
        LED_L(PIN_N);  // dash
        LED_D(PIN_N);  // dot
        LED_D(PIN_N);  // dot
        break;
      case 'M':
        LED_L(PIN_N);  // dash
        LED_L(PIN_N);  // dash
        break;
      case 'N':
        LED_L(PIN_N);  // dash
        LED_D(PIN_N);  // dot
        break;
      case 'O':
        LED_L(PIN_N);  // dash
        LED_L(PIN_N);  // dash
        LED_L(PIN_N);  // dash
        break;
      case 'P':
        LED_D(PIN_N);  // dot
        LED_L(PIN_N);  // dash
        LED_L(PIN_N);  // dash
        LED_D(PIN_N);  // dot
        break;
      case 'Q':
        LED_L(PIN_N);  // dash
        LED_L(PIN_N);  // dash
        LED_D(PIN_N);  // dot
        LED_L(PIN_N);  // dash
        break;
      case 'R':
        LED_D(PIN_N);  // dot
        LED_L(PIN_N);  // dash
        LED_D(PIN_N);  // dot
        break;
      case 'S':
        LED_D(PIN_N);  // dot
        LED_D(PIN_N);  // dot
        LED_D(PIN_N);  // dot
        break;
      case 'T':
        LED_L(PIN_N);  // dash
        break;
      case 'U':
        LED_D(PIN_N);  // dot
        LED_D(PIN_N);  // dot
        LED_L(PIN_N);  // dash
        break;
      case 'V':
        LED_D(PIN_N);  // dot
        LED_D(PIN_N);  // dot
        LED_D(PIN_N);  // dot
        LED_L(PIN_N);  // dash
        break;
      case 'W':
        LED_D(PIN_N);  // dot
        LED_L(PIN_N);  // dash
        LED_L(PIN_N);  // dash
        break;
      case 'X':
        LED_L(PIN_N);  // dash
        LED_D(PIN_N);  // dot
        LED_D(PIN_N);  // dot
        LED_L(PIN_N);  // dash
        break;
      case 'Y':
        LED_L(PIN_N);  // dash
        LED_D(PIN_N);  // dot
        LED_L(PIN_N);  // dash
        LED_L(PIN_N);  // dash
        break;
      case 'Z':
        LED_L(PIN_N);  // dash
        LED_L(PIN_N);  // dash
        LED_D(PIN_N);  // dot
        LED_D(PIN_N);  // dot
        break;
      default:
        delay(500);
    }
    delay(500);  // Small delay between letters
  }
}

void loop() {
  Blynk.syncVirtual(V1);  // Sync the state of Virtual Pin V1 on startup
  Blynk.run();
}

void LED_D(uint8_t PIN_N) {
  // digitalWrite(PIN_N, HIGH);  // Вмикаємо світлодіод
  tone(PIN_N, 400); 
  delay(250);              // Затримка для точки
  // digitalWrite(PIN_N, LOW);   // Вимикаємо світлодіод
  noTone(PIN_N); 
  delay(250);  
}

void LED_L(uint8_t PIN_N) {
  // digitalWrite(PIN_N, HIGH);  // Вмикаємо світлодіод
  tone(PIN_N, 400); 
  delay(750);              // Затримка для тире
  // digitalWrite(PIN_N, LOW);   // Вимикаємо світлодіод
  noTone(PIN_N); 
  delay(250); 
}
