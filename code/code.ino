// крутим мотор туда-сюда плавно с ускорением
#include <GyverStepper.h>
int mm = 200 * 16 / 4;  // Общее количество шагов на один оборот
GStepper<STEPPER2WIRE> stepper(mm, 2, 3); // Инициализация шагового мотора
int koef = 15200;
// 19703- шагов на мл глицерина
// 15200 - шагов на мл воды и пропиленглюколя 

void setup() {
  Serial.begin(115200);
  // режим следования к целевой позиции
  stepper.setRunMode(FOLLOW_POS);
  // установка макс. скорости в шагах/сек
  stepper.setMaxSpeed(2500);
  // установка ускорения в шагах/сек/сек
  stepper.setAcceleration(0); // Отключаем ускорением, чтобы двигатель двигался с постоянной скоростью
}

void loop() {
  // Если поступили данные в последовательный порт
  if (Serial.available()) {
    long shag = Serial.parseInt() * koef;  // Считываем целое число
    stepper.setTarget(shag, RELATIVE); // Устанавливаем целевую позицию
    Serial.print("Установленная целевая позиция: ");
    Serial.println(stepper.getTarget());
  }
  stepper.tick();
  // Обратная связь о позиции мотора(нерекомендую, замедляет мотор):
  // if (stepper.tick()) {
  //   // Если мотор шагает, можно выводить текущую позицию
  //   Serial.print("Текущая позиция: ");
  //   Serial.println(stepper.getCurrent());
  // }
}
