/**
 * @file Parking.cpp
 * @brief ガレージ駐車に使用するクラス
 * @author Oiwane
 * updated by match97
 */
#include "Parking.h"

Parking::Parking(Controller& controller_, int targetBrightness_)
  : controller(controller_),
    navigator(controller_, targetBrightness_),
    targetBrightness(targetBrightness_)
{
}

void Parking::parkAtAL()
{
  navigator.moveToSpecifiedColor(Color::green, 10);
  navigator.move(100, 10, 0.813);
  navigator.spin(10.0, false);
  navigator.moveToSpecifiedColor(Color::blue, 10);
  navigator.spin(10.0, true);
  navigator.move(300, 10, 0.813);
  navigator.spin(90.0, false);

  this->stopFor3sec();
}

void Parking::parkAtAR()
{
  // navigator.moveToSpecifiedColor(Color::blue, 10);
  navigator.move(250, 10, 0.813);                               // 250mm直進
  navigator.spin(60, false);                                    // 60度左回転
  navigator.moveToSpecifiedColor(Color::black, 10);             // 黒詠むまで走る
  navigator.move(40, 10, 0.813);                                // 40mm前進
  navigator.spin(70, true);                                     // 70度右回転
  navigator.lineTraceToSpecifiedColor(Color::blue, 10, false);  // ライントレースしながら青
  navigator.move(130, 10, 0.813);
  navigator.spin(90, false);
  navigator.move(400, 10, 0.813);

  this->stopFor3sec();
}

void Parking::stopFor3sec()
{
  for(int i = 0; i < 3; i++) {
    controller.speakerPlayToneFS6(100);
    controller.tslpTsk(1000);
  }
  controller.speakerPlayToneFS6(1000);
}
