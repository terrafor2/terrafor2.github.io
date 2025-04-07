#include <DHT.h>

#define DHTPIN 11       // DHT11 센서 데이터 핀
#define DHTTYPE DHT11  
#define BUZZER_PIN 9    // 부저 핀 (수동형이므로 tone() 사용)
#define LED_PIN 2       // LED 핀 (2번 포트에 LED 연결)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT); // LED 핀을 출력으로 설정
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW); // LED를 끈 상태로 초기화

  // 모니터링 시작 메시지 출력
  Serial.println("모니터링 시작...");
}

void loop() {
  delay(2000);  // 2초마다 측정

  // 센서 값 읽기
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // 센서 값을 읽지 못한 경우
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("ERROR: 센서 값을 읽을 수 없음");
    return;
  }

  // 센서 데이터를 Python 등 외부 프로그램으로 전송 (CSV 데이터 형식)
  Serial.print(temperature);
  Serial.print(",");
  Serial.println(humidity);

  // Python으로부터 명령 수신 및 모니터링용 출력
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();  // 개행 문자 제거

    Serial.print("수신된 명령: ");
    Serial.println(command);

    if (command == "BUZZER_ON") {
      tone(BUZZER_PIN, 1000); // 1000Hz 주파수로 부저 작동
      Serial.println("부저 작동 중...");

      // 부저와 함께 LED도 켜기
      digitalWrite(LED_PIN, HIGH);  // LED 켜기

      delay(1000); // 1초간 소리와 LED가 켜짐

      noTone(BUZZER_PIN); // 부저 정지
      Serial.println("부저 정지");

      // LED 끄기
      digitalWrite(LED_PIN, LOW);  // LED 끄기
    }
  }
}
