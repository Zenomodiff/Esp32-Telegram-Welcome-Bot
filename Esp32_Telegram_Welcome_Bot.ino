/*feel free to contact
 * sreeramaj53@gmail.com
 * www.youtube.com/ZenoModiff
 * last updated - time 10:36 PM - date 19 june 2021
 * Github Link :-- https://github.com/Zenomodiff/Esp32-Telegram-Welcome-Bot
 */

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>   
#include <ArduinoJson.h>

const char* ssid = "PASTE THE WIFI SSID";
const char* password = "PASTE THE WIFI PASSWORD";

#define BOTtoken "PASTE THE TELEGRAM BOT TOKEN" 
#define CHAT_ID "PASTE THE TELEGRAM CHAT ID"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {

    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }

    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;

    if (text == "/start") {
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "Use the following Commands To Get Replay.\n\n";
      welcome += "/How_Are_You \n";
      welcome += "/Who_Made_You\n";
      welcome += "/What_Can_I_Call_You\n";
      welcome += "/Sing_A_Song\n";
      welcome += "/Tell_Me_A_Joke\n";
      
      bot.sendMessage(chat_id, welcome, "");
    }

    if (text == "/How_Are_You") {
      bot.sendMessage(chat_id, "Iam Good Thanks For Asking");
    }
    
    if (text == "/Who_Made_You") {
      bot.sendMessage(chat_id, "ZenoModiff Made Me");
    }
    
    if (text == "/What_Can_I_Call_You") {
      bot.sendMessage(chat_id, "You Can Call Me ZenoBoT");
    } 

     if (text == "/Sing_A_Song") {
      bot.sendMessage(chat_id, "Like a small boat");
      bot.sendMessage(chat_id, "On the ocean");
      bot.sendMessage(chat_id, "Sending big waves");
      bot.sendMessage(chat_id, "Into motion");
      bot.sendMessage(chat_id, "Like how a single word");
      bot.sendMessage(chat_id, "Can make a heart open");
      bot.sendMessage(chat_id, "I might only have one match");
      bot.sendMessage(chat_id, "But I can make an explosion");
    }
    
    if (text == "/Tell_Me_A_Joke") {
      bot.sendMessage(chat_id, "Just Fuck Off ");
      delay(1000);
      bot.sendMessage(chat_id, "Iam Just Kidding :)");
    }
    
   }
  }

void setup() {
  
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  #ifdef ESP32
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  #endif
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());
}

void loop() {
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}
