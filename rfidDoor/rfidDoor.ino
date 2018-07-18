long lastTime = 0, lastTime2 = 0;

bool bayrakGiris = false;

//relay pin
#define ROLE A0

//led pins
#define LED1 A4
#define LED2 A5
#define LED3 4
#define LED4 5

bool durum1 = true, durum2 = false;

void setup() {
  // put your setup code here, to run once:

  //start serial comminucation over 0 and 1 pins
  Serial.begin(9600);

  //set leds and relay as a output 
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  digitalWrite(ROLE, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  //check is rfid reader read something?
  if (Serial.available())
  {
    String cardId = dataOku();

    //if card id true and passed 2 seconds 
    if (girisYap(cardId) && !bayrakGiris)
    {
      bayrakGiris = true;
      digitalWrite(ROLE, LOW);
      ledDegis(true);
      lastTime2 = millis();
    } else {
      bayrakGiris = true;
      lastTime2 = millis();
    }

  }


  ledAnimasyon();
}

//add known card id to this function
bool girisYap(String cardId)
{
  if(cardId == "xxxxxxxxxx") return true;
  if(cardId == "xxxxxxxxxx") return true;
  else return false;
}

//read 11 charecter card id from serial
String dataOku()
{
  char _id[11];
  int i = 0, j = 0;

  while(j != 13 && i < 11)
  {
    j = Serial.read();
    if(isdigit(j))
      _id[i++] = (char)j;
  }

  _id[10] = '\0';
  String cardId(_id);
  Serial.println(_id);
  return cardId;
}

//make a led animation while waiting and wait 2 seconds between readings
void ledAnimasyon()
{
  if (bayrakGiris && millis() - lastTime2 > 2000)
  {
    digitalWrite(ROLE, HIGH);
    bayrakGiris = false;
    ledDegis(false);
  } else if (!bayrakGiris) {
    ledDondur();
  }
}

//change all led status
void ledDegis(bool _durum)
{
  digitalWrite(LED1, _durum);
  digitalWrite(LED2, _durum);
  digitalWrite(LED3, _durum);
  digitalWrite(LED4, _durum);
}

//change led status synchronous
void ledDondur()
{
  if (millis() - lastTime > 500)
  {
    durum1 = !durum1;
    durum2 = !durum2;
    lastTime = millis();
  }
  digitalWrite(LED1, durum1);
  digitalWrite(LED2, durum1);
  digitalWrite(LED3, durum2);
  digitalWrite(LED4, durum2);
}
