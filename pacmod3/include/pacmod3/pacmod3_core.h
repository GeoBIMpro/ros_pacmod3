#ifndef PACMOD3_CORE_HPP
#define PACMOD3_CORE_HPP

/*
* Unpublished Copyright (c) 2009-2017 AutonomouStuff, LLC, All Rights Reserved.
*
* This file is part of the PACMod v3 ROS 1.0 driver which is released under the MIT license.
* See file LICENSE included with this software or go to https://opensource.org/licenses/MIT for full license details.
*/

#include <cstring>
#include <sstream>
#include <cstdint>
#include <memory>
#include <vector>

namespace AS
{
namespace Drivers
{
namespace PACMod3
{
  enum VehicleType
  {
    POLARIS_GEM,
    POLARIS_RANGER,
    INTERNATIONAL_PROSTAR_122,
    LEXUS_RX_450H
  };

  class Pacmod3TxMsg
  {
    public:
      static std::shared_ptr<Pacmod3TxMsg> make_message(const int64_t& can_id);
      virtual void parse(uint8_t *in) = 0;
  };

  class SystemRptMsg :
    public Pacmod3TxMsg
  {
    public:
      SystemRptMsg();

      bool enabled;
      bool override_active;
      bool command_output_fault;
      bool input_output_fault;
      bool output_reported_fault;
      bool pacmod_fault;
      bool vehicle_fault;
  };

  class SystemRptBoolMsg :
    public SystemRptMsg
  {
    public:
      SystemRptBoolMsg();

      bool manual_input;
      bool command;
      bool output;

      void parse(uint8_t *in);
  };

  class SystemRptIntMsg :
    public SystemRptMsg
  {
    public:
      SystemRptIntMsg();

      uint8_t manual_input;
      uint8_t command;
      uint8_t output;

      void parse(uint8_t *in);
  };

  class SystemRptFloatMsg :
    public SystemRptMsg
  {
    public:
      SystemRptFloatMsg();

      double manual_input;
      double command;
      double output;

      void parse(uint8_t *in);
  };

  // TX Messages
  class GlobalRptMsg :
    public Pacmod3TxMsg
  {
    public:
      static const int64_t CAN_ID;

      bool enabled;
      bool override_active;
      bool user_can_timeout;
      bool steering_can_timeout;
      bool brake_can_timeout;
      bool subsystem_can_timeout;
      bool vehicle_can_timeout;
      uint16_t user_can_read_errors;

      void parse(uint8_t *in);
  };

  // System Reports
  class AccelRptMsg :
    public SystemRptFloatMsg
  {
    public:
      static const int64_t CAN_ID;
  };

  class AccelAuxRptMsg :
    public Pacmod3TxMsg
  {
    public:
      static const int64_t CAN_ID;

      void parse(uint8_t *in);
  };

  class BrakeRptMsg :
    public SystemRptFloatMsg
  {
    public:
      static const int64_t CAN_ID;
  };

  class BrakeAuxRptMsg :
    public Pacmod3TxMsg
  {
    public:
      static const int64_t CAN_ID;

      void parse(uint8_t *in);
  };

  class CruiseControlButtonsRptMsg :
    public SystemRptIntMsg
  {
    public:
      static const int64_t CAN_ID;
  };

  class DashControlsLeftRptMsg :
    public SystemRptIntMsg
  {
    public:
      static const int64_t CAN_ID;
  };

  class DashControlsRightRptMsg :
    public SystemRptIntMsg
  {
    public:
      static const int64_t CAN_ID;
  };

  class HeadlightRptMsg :
    public SystemRptIntMsg
  {
    public:
      static const int64_t CAN_ID;
  };

  class HornRptMsg :
    public SystemRptBoolMsg
  {
    public:
      static const int64_t CAN_ID;
  };

  class MediaControlsRptMsg :
    public SystemRptIntMsg
  {
    public:
      static const int64_t CAN_ID;
  };

  class ParkingBrakeRptMsg :
    public SystemRptBoolMsg
  {
    public:
      static const int64_t CAN_ID;
  };

  class ShiftRptMsg :
    public SystemRptIntMsg
  {
    public:
      static const int64_t CAN_ID;
  };

  class ShiftAuxRptMsg :
    public Pacmod3TxMsg
  {
    public:
      static const int64_t CAN_ID;

      void parse(uint8_t *in);
  };

  class SteerRptMsg :
    public SystemRptFloatMsg
  {
    public:
      static const int64_t CAN_ID;
  };

  class SteerAuxRptMsg :
    public Pacmod3TxMsg
  {
    public:
      static const int64_t CAN_ID;

      void parse(uint8_t *in);
  };

  class SteerRpt2Msg :
    public SystemRptFloatMsg
  {
    public:
      static const int64_t CAN_ID;
  };

  class SteerRpt3Msg :
    public SystemRptFloatMsg
  {
    public:
      static const int64_t CAN_ID;
  };

  class TurnSignalRptMsg :
    public SystemRptIntMsg
  {
    public:
      static const int64_t CAN_ID;
  };

  class WiperRptMsg :
    public SystemRptIntMsg
  {
    public:
      static const int64_t CAN_ID;
  };

  // Other Reports
  class ExteriorLightsRptMsg :
    public Pacmod3TxMsg
  {
    public:
      static const int64_t CAN_ID;

      void parse(uint8_t *in);
  };

  class InteriorLightsRptMsg :
    public Pacmod3TxMsg
  {
    public:
      static const int64_t CAN_ID;

      void parse(uint8_t *in);
  };

  class OccupancyRptMsg :
    public Pacmod3TxMsg
  {
    public:
      static const int64_t CAN_ID;

      void parse(uint8_t *in);
  };

  class MotorRpt1Msg :
    public Pacmod3TxMsg
  {
    public:
      double current;
      double position;

      void parse(uint8_t *in);
  };

  class MotorRpt2Msg :
    public Pacmod3TxMsg
  {
    public:
      double encoder_temp;
      double motor_temp;
      double velocity;

      void parse(uint8_t *in);
  };

  class MotorRpt3Msg :
    public Pacmod3TxMsg
  {
    public:
      double torque_output;
      double torque_input;

      void parse(uint8_t *in);
  };

  class BrakeMotorRpt1Msg :
    public MotorRpt1Msg
  {
    public:
      static const int64_t CAN_ID;
  };

  class BrakeMotorRpt2Msg :
    public MotorRpt2Msg
  {
    public:
      static const int64_t CAN_ID;
  };

  class BrakeMotorRpt3Msg :
    public MotorRpt3Msg
  {
    public:
      static const int64_t CAN_ID;
  };

  class DateTimeRptMsg :
    public Pacmod3TxMsg
  {
    public:
      static const int64_t CAN_ID;

      uint32_t year;
      uint8_t month;
      uint8_t day;
      uint8_t hour;
      uint8_t minute;
      uint8_t second;

      void parse(uint8_t *in);
  };

  class DoorRptMsg :
    public Pacmod3TxMsg
  {
    public:
      static const int64_t CAN_ID;

      void parse(uint8_t *in);
  };

  class LatLonHeadingRptMsg :
    public Pacmod3TxMsg
  {
    public:
      static const int64_t CAN_ID;
     
      int latitude_degrees;
      uint32_t latitude_minutes;
      uint32_t latitude_seconds;
      int longitude_degrees;
      uint32_t longitude_minutes;
      uint32_t longitude_seconds;
      double heading;

      void parse(uint8_t *in);
  };

  class SteeringPIDRpt1Msg :
    public Pacmod3TxMsg
  {
    public:
      static const int64_t CAN_ID;

      double dt;
      double Kp;
      double Ki;
      double Kd;

      void parse(uint8_t *in);
  };

  class SteeringPIDRpt2Msg :
    public Pacmod3TxMsg
  {
    public:
      static const int64_t CAN_ID;

      double P_term;
      double I_term;
      double D_term;
      double all_terms;

      void parse(uint8_t *in);
  };

  class SteeringPIDRpt3Msg :
    public Pacmod3TxMsg
  {
    public:
      static const int64_t CAN_ID;

      double new_torque;
      double str_angle_desired;
      double str_angle_actual;
      double error;

      void parse(uint8_t *in);
  };

  class SteeringPIDRpt4Msg :
    public Pacmod3TxMsg
  {
    public:
      static const int64_t CAN_ID;

      double angular_velocity;
      double angular_acceleration;

      void parse(uint8_t *in);
  };

  class SteerMotorRpt1Msg :
    public MotorRpt1Msg
  {
    public:
      static const int64_t CAN_ID;
  };

  class SteerMotorRpt2Msg :
    public MotorRpt2Msg
  {
    public:
      static const int64_t CAN_ID;
  };

  class SteerMotorRpt3Msg :
    public MotorRpt3Msg
  {
    public:
      static const int64_t CAN_ID;
  };

  class VehicleSpeedRptMsg :
    public Pacmod3TxMsg
  {
    public:
      static const int64_t CAN_ID;

      double vehicle_speed;
      bool vehicle_speed_valid;
      uint8_t vehicle_speed_raw[2];

      void parse(uint8_t *in);
  };

  class VinRptMsg :
    public Pacmod3TxMsg
  {
    public:
      static const int64_t CAN_ID;

      std::string mfg_code;
      std::string mfg;
      char model_year_code;
      uint32_t model_year;
      uint32_t serial;

      void parse(uint8_t *in);
  };

  class YawRateRptMsg :
    public Pacmod3TxMsg
  {
    public:
      static const int64_t CAN_ID;

      double yaw_rate;

      void parse(uint8_t *in);
  };

  class WheelSpeedRptMsg :
    public Pacmod3TxMsg
  {
    public:
      static const int64_t CAN_ID;

      double front_left_wheel_speed;
      double front_right_wheel_speed;
      double rear_left_wheel_speed;
      double rear_right_wheel_speed;

      void parse(uint8_t *in);
  };

  // RX Messages
  class Pacmod3RxMsg
  {
    public:
      Pacmod3RxMsg();
      std::vector<uint8_t> data;
      bool recent_state_change;
      uint8_t state_change_debounce_count;
  };

  class SystemCmdBool :
    public Pacmod3RxMsg
  {
    public:
      void encode(bool enable,
                  bool ignore_overrides,
                  bool cmd);
  };

  class SystemCmdFloat :
    public Pacmod3RxMsg
  {
    public:
      void encode(bool enable,
                  bool ignore_overrides,
                  float cmd);
  };

  class SystemCmdInt :
    public Pacmod3RxMsg
  {
    public:
      void encode(bool enable,
                  bool ignore_overrides,
                  uint8_t cmd);
  };

  class AccelCmdMsg :
    public SystemCmdFloat
  {
    public:
      static const int64_t CAN_ID;
  };

  class BrakeCmdMsg :
    public SystemCmdFloat
  {
    public:
      static const int64_t CAN_ID;
  };

  class CruiseControlButtonsCmdMsg :
    public SystemCmdInt
  {
    public:
      static const int64_t CAN_ID;
  };

  class DashControlsLeftCmdMsg :
    public SystemCmdInt
  {
    public:
      static const int64_t CAN_ID;
  };

  class DashControlsRightCmdMsg :
    public SystemCmdInt
  {
    public:
      static const int64_t CAN_ID;
  };
  
  class HeadlightCmdMsg :
    public SystemCmdInt
  {
    public:
      static const int64_t CAN_ID;
  };

  class HornCmdMsg :
    public SystemCmdBool
  {
    public:
      static const int64_t CAN_ID;
  };

  class MediaControlsCmdMsg :
    public SystemCmdInt
  {
    public:
      static const int64_t CAN_ID;
  };

  class ParkingBrakeCmdMsg :
    public SystemCmdBool
  {
    public:
      static const int64_t CAN_ID;
  };

  class ShiftCmdMsg :
    public SystemCmdInt
  {
    public:
      static const int64_t CAN_ID;
  };

  class SteerCmdMsg :
    public SystemCmdFloat
  {
    public:
      static const int64_t CAN_ID;

      void encode(bool enabled,
                  bool ignore_overrides,
                  float steer_pos,
                  float steer_spd);
  };

  class TurnSignalCmdMsg :
    public SystemCmdInt
  {
    public:
      static const int64_t CAN_ID;
  };

  class WiperCmdMsg :
    public SystemCmdInt
  {
    public:
      static const int64_t CAN_ID;
  };
}
}
}

#endif
