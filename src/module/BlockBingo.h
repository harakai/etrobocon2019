/**
 *  @file   BlockBingo.h
 *  @brief  ブロックビンゴで使用する動作をまとめたクラス
 *  @author Oiwane
 */
#ifndef BLOCKBINGO_H
#define BLOCKBINGO_H

#include <array>
#include "Controller.h"
#include "Instructions.h"
#include "Navigator.h"

class BlockBingo {
 private:
  Controller& controller;
  Navigator navigator;
  //交点サークルから中点までの距離
  const int targetBrightness;
  static constexpr double lengthCrossCircleCenter = 175.0;
  static constexpr double lengthColorSensorAxis = 50.0;
  // FirstProcess = ブロックサークル内の黒ブロックをボーナスサークル内に設置する
  bool isFirstProcess;
  const double pGain;
  const int straightPwm;

  //ここからのprivate関数の詳細はモデルの2.2を参照
  /**
   * SPIN_RIGHTの命令を実行する
   * @brief 90度右に回頭する
   */
  void execSpinRight();
  /**
   * SPIN_LEFTの命令を実行する
   * @brief 90度左に回頭する
   */
  void execSpinLeft();
  /**
   * SPIN180の命令を実行する
   * @brief 180度回頭する
   */
  void execSpin180();
  /**
   * STRAIGHTの命令を実行する
   * @brief
   * 進行方向にブロックがない場合に使用する。ある交点サークルから隣接する交点サークルの距離の分だけ移動する
   */
  void execStraight();
  /**
   * STRAIGHT_DETOUR_RIGHTの命令を実行する
   * @brief 進行方向にブロックがある場合に使用する。右に迂回するように直進する
   */
  void execStraightDetourRight();
  /**
   * STRAIGHT_DETOUR_RIGHTの命令を実行する
   * @brief 進行方向にブロックがある場合に使用する。左に迂回するように直進する
   */
  void execStraightDetourLeft();
  /**
   * TURN_RIGHT90_EXIST_BLOCKの命令を実行する
   * @brief ブロックのある交点サークルで右に90度曲がる。
   */
  void execTurnRight90ExistBlock();
  /**
   * TURN_RIGHT90_UNEXIST_BLOCKの命令を実行する
   * @brief ブロックのない交点サークルで右に90度曲がる。
   */
  void execTurnRight90UnexistBlock();
  /**
   * TURN_LEFT90_EXIST_BLOCKの命令を実行する
   * @brief ブロックのある交点サークルで左に90度曲がる。
   */
  void execTurnLeft90ExistBlock();
  /**
   * TURN_LEFT90_UNEXIST_BLOCKの命令を実行する
   * @brief ブロックのない交点サークルで左に90度曲がる。
   */
  void execTurnLeft90UnexistBlock();
  /**
   * TURN180の命令を実行する
   * @brief ブロックがない場合に使用される。中点で180度旋回してから交点サークルまで直進する
   */
  void execTurn180();
  /**
   * PUTの命令を実行する
   * @brief ブロックをブロックサークルに設置する
   */
  void execPut();
  /**
   * MOVE_NODEの命令を実行する
   * @brief lengthだけ直進する
   */
  void execMoveNode();
  /**
   * QUICK_PUT_Rの命令を実行する
   * @brief
   * ブロックを持った状態で交点サークルから右向きにブロックサークルの中心に設置して出発した元の交点サークルまで戻る
   */
  void execQuickPutR();
  /**
   * QUICK_PUT_Lの命令を実行する
   * @brief
   * ブロックを持った状態で交点サークルから左向きにブロックサークルの中心に設置して出発した元の交点サークルまで戻る
   */
  void execQuickPutL();
  /**
   * PREPARE_TO_PUTの命令を実行する
   * @brief ブロックサークルの中心から黒線まで移動する
   */
  void execPrepareToPut();

 public:
  /**
   * コンストラクタ
   * @param controller_ [Controllerの参照]
   */
  BlockBingo(Controller& controller_, int targetBrightness_);

  /**
   * Lコースのブロックビンゴのブロックサークル4に移動する
   * @brief Lコースのブロックビンゴ開始点からブロックサークル4の手前の
   * 黒線の中点まで斜めに移動し、ブロックサークル4の中央まで移動する。
   */
  void moveCircle4OfL();
  /**
   * Lコースのブロックビンゴのブロックサークル6に移動する
   * @brief Lコースのブロックビンゴ開始点からブロックサークル6の手前の
   * 黒線の中点まで斜めに移動し、ブロックサークル6の中央まで移動する。
   */
  void moveCircle6OfL();
  /**
   * Rコースのブロックビンゴのブロックサークル6に移動する
   * @brief Lコースのブロックビンゴ開始点からブロックサークル6の手前の
   * 黒線の中点まで斜めに移動し、ブロックサークル6の中央まで移動する。
   */
  void moveCircle5OfR();
  /**
   * Rコースのブロックビンゴのブロックサークル8に移動する
   * @brief Rコースのブロックビンゴ開始点からブロックサークル8の手前の
   * 黒線の中点まで斜めに移動し、ブロックサークル8の中央まで移動する。
   */
  void moveCircle8OfR();
  
  /**
   * パソコンから受け取ったリストの通りに処理を実行する
   * @param orders [命令の情報のリスト]
   */
  template <int N>
  void execOrder(std::array<char, N>& orderKeys)
  {
    Instructions instructions;

    for(const auto& orderKey : orderKeys) {
      Order order = instructions.translate(orderKey);

      switch(order) {
        case Order::ENTER_BINGO_AREA_L4:
          this->moveCircle4OfL();
          break;

        case Order::ENTER_BINGO_AREA_L6:
          this->moveCircle6OfL();
          break;

        case Order::ENTER_BINGO_AREA_R5:
          this->moveCircle5OfR();
          break;

        case Order::ENTER_BINGO_AREA_R8:
          this->moveCircle8OfR();
          break;

        case Order::SPIN_RIGHT:
          this->execSpinRight();
          break;

        case Order::SPIN_LEFT:
          this->execSpinLeft();
          break;

        case Order::SPIN180:
          this->execSpin180();
          break;

        case Order::STRAIGHT:
          this->execStraight();
          break;

        case Order::STRAIGHT_DETOUR_RIGHT:
          this->execStraightDetourRight();
          break;

        case Order::STRAIGHT_DETOUR_LEFT:
          this->execStraightDetourLeft();
          break;

        case Order::TURN_RIGHT90_EXIST_BLOCK:
          this->execTurnRight90ExistBlock();
          break;

        case Order::TURN_RIGHT90_UNEXIST_BLOCK:
          this->execTurnRight90UnexistBlock();
          break;

        case Order::TURN_LEFT90_EXIST_BLOCK:
          this->execTurnLeft90ExistBlock();
          break;

        case Order::TURN_LEFT90_UNEXIST_BLOCK:
          this->execTurnLeft90UnexistBlock();
          break;

        case Order::TURN180:
          this->execTurn180();
          break;

        case Order::PUT:
          this->execPut();
          break;

        case Order::MOVE_NODE:
          this->execMoveNode();
          break;

        case Order::QUICK_PUT_R:
          this->execQuickPutR();
          break;

        case Order::QUICK_PUT_L:
          this->execQuickPutL();
          break;

        case Order::PREPARE_TO_PUT:
          this->execPrepareToPut();
          break;

        default:
          controller.speakerPlayToneFS6(1000);
      }
    }
  }
};

#endif
