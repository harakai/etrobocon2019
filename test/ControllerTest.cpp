/**
 *  @file   ControllerTest.cpp
 *  @brief  ライントレーサークラスのテストファイル
 *  @author korosuke613
 */
#include "Controller.h"
#include <gtest/gtest.h>

namespace etrobocon2019_test {
  TEST(Controller, color_buffer_only_black)
  {
    Controller controller;

    for(int i = 0; i < controller.color_buffer_size; i++) {
      controller.setMockRgb(0, 0, 0);
      controller.registerColor();
    }

    for(const auto& color : controller.color_buffer){
      ASSERT_EQ(color, Color::black);
    }
  }
  TEST(Controller, color_buffer_black3_white7)
  {
    Controller controller;

    for(int i = 0; i < controller.color_buffer_size; i++) {
      controller.setMockRgb(0, 0, 0);
      controller.registerColor();
    }

    for(int i = 0; i < 7; i++) {
      controller.setMockRgb(255, 255, 255);
      controller.registerColor();
    }

    ASSERT_EQ(controller.determineColor(), Color::white);
  }
}  // namespace etrobocon2019_test
