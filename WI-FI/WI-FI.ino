#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

WiFiClient wifiClient;


char ssid[] = "TP-LINK_F9970D";
char pass[] = "49401318";
const char* serverUrl = "http://192.168.0.102:3000/data";

const uint8_t SELECTED_PIN = D1;
const uint8_t BUTTON_PIN = D2;
const uint8_t MODE_PIN = D3;

unsigned long pressStart = 0;
unsigned long unpressStart = 0;
unsigned long pressDuration = 0;
unsigned long unpressDuration = 0;
bool firstPress = false;
bool isPressed = false;
String morseCode = "";
String wordOut = "";
String wordIn = "";
HTTPClient http;

void setup() {
  pinMode(SELECTED_PIN, OUTPUT);  // Ініціалізуємо світлодіод як вихід
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Ініціалізуємо кнопку як вхід з підтягувальним резистором
  pinMode(MODE_PIN, INPUT);  // Ініціалізуємо кнопку як вхід з підтягувальним резистором
  Serial.begin(9600);  // Запускаємо серійну передачу для налагодження
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
        delay(200);
        Serial.println("Connecting to WiFi...");
    }
  Serial.println("Connected to WiFi");
  http.begin(wifiClient,serverUrl);// Встановлюємо URL сервера
  Serial.println("connected to server");
 
}



// This function is called every time the device is connected to the Blynk.Cloud
// BLYNK_CONNECTED()
// {
//   // bridge1.setAuthToken("3aqnTjMF_ttgNUVWqzPHh-yefziQn1dq"); // Token of the hardware B
//   // Change Web Link Button message to "Congratulations!"
//   Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
//   Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
//   Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
// }


void postRequest(String word){
  if (WiFi.status() == WL_CONNECTED) {
      
    http.addHeader("Content-Type", "text/plain");  // Вказуємо тип контенту

    int httpResponseCode = http.POST(word);  // Виконуємо POST-запит

    if (httpResponseCode > 0) {
        String response = http.getString();  // Отримуємо відповідь сервера
        Serial.println("Response from server: " + response);
    } else {
        Serial.println("Error on sending POST: " + String(httpResponseCode));
    }

    http.end();  // Завершуємо роботу з HTTP-клієнтом
    } else {
        Serial.println("WiFi not connected");
    }
}


String getRequest(){
    String response;

  if (WiFi.status() == WL_CONNECTED) {
    int httpResponseCode = http.GET();  // Виконуємо GET-запит
    if (httpResponseCode > 0) {
        response = http.getString();  // Отримуємо відповідь сервера
        Serial.println("Response from server: " + response);
    } else {
        Serial.println("Error on sending GET: " + String(httpResponseCode));
    }

    http.end();  // Завершуємо роботу з HTTP-клієнтом
  }
    return response;
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
  if(digitalRead(MODE_PIN) == HIGH){
  if (digitalRead(BUTTON_PIN) == LOW && !isPressed) {
    unpressDuration = millis() - unpressStart; //Обраховує скільки часу кнопка була ненатиснута
    pressStart = millis();  // Початок натискання
    isPressed = true;

    if (unpressDuration >= 500 && unpressDuration < 1500) {
      morseCode += " ";  // Додаємо проміжок між буквами
      Serial.println("letter space");
    } else if (unpressDuration >=1500) {
      morseCode += " ";
      wordOut = morseToWord(morseCode);
      morseCode += wordOut;  // Додаємо проміжок між словами
      Serial.println(morseCode);
      morseCode ="";
      postRequest(wordOut);
      isPressed = true;
    }
  }

  if (digitalRead(BUTTON_PIN) == HIGH && isPressed) {
    pressDuration = millis() - pressStart; //Обраховує скільки часу кнопка була натиснута
    unpressStart = millis();  // Початок ненатискання
    isPressed = false;

    if (pressDuration >= 10 && pressDuration < 300) {
      morseCode += ".";  // Додаємо точку
    } else if (pressDuration >= 300 && pressDuration <= 750) {
      morseCode += "-";  // Додаємо тире
    }

    Serial.print("Current Morse code: ");
    Serial.println(morseCode);
  }
  } else {
    wordIn = getRequest();
    stringToMorse(wordIn,SELECTED_PIN);
  }

  delay(50);  // Невелика затримка для уникнення надмірної чутливості до шуму
  
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
