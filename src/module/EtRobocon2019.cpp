#include "EtRobocon2019.h"
#include "Controller.h"
#include "Calibrator.h"
#include "Display.h"
#include "Navigator.h"

void EtRobocon2019::start()
{
    Controller controller;
    // Calibrator calibrator(controller);

    // calibrator.calibration();

    Navigator navigator(controller);

    navigator.move(1000);
    controller.tslpTsk(1000);
    navigator.move(-1000);
}