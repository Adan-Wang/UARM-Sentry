/*
 * GImbal_App.h
 *
 *  Created on: Dec 5, 2020
 *      Author: AzureRin
 */

#ifndef SRC_APPLICATIONS_GIMBAL_APP_H_
#define SRC_APPLICATIONS_GIMBAL_APP_H_

#include "main.h"
#include "can.h"
#include "cmsis_os.h"
#include "../buzzer.h"
#include "../Device/Motor.h"

#define PACKLEN  32
#define DATALEN  3
#define STATELEN 1
#define PACKCOR 0
#define PACKERR 1
#define OVER_ZERO 1
#define NOT_OVER_ZERO 0
#define PITCH_FRONT 1
#define PITCH_BACK -1

//These are ABSOLUTE ANGLES, calibrate manually.
#define INIT_YAW 35
#define INIT_PITCH 0
#define YAW_MAX_HALF_DELTA 60
#define PITCH_MAX_HALF_DELTA 60 //Originally 45
#define MAX_PITCH_CHANGE_TIME 5
#define MAX_YAW_CHANGE_TIME 3
#define FRONT_ANGLE 280 //Hard set front and back angles
#define BACK_ANGLE 280
//min time in ms for computer vision to take over
#define TGT_CONST 500

#define YAW_POS 16
#define PITCH_POS 24
#define DIST_POS 32
//#define TARGET_POS DIST_POS+STATELEN
#define FCMD_POS 8

typedef struct {
	int32_t yaw_data;
	int32_t pitch_data;
	int32_t dist_data;
	int32_t target_num;
	int32_t fire_cmd;
	int32_t pack_cond;
}comm_rx_info;


int32_t parse_pack_indv(char* pack, int pos, int lens);
comm_rx_info parse_pack_string(char* pack);
comm_rx_info parse_all(char* pack);

double angle_preprocess(Motor* motor, int16_t recieved_angle);
int16_t check_angle_greater_than_max(int32_t input_angle, int16_t max_angle, int16_t min_angle);
int16_t check_angle_smaller_than_min(int32_t input_angle, int16_t max_angle, int16_t min_angle);
int16_t check_angle_out_of_range(int32_t input_angle, int16_t max_angle, int16_t min_angle);
int16_t check_angle_over_zero(int16_t min_angle, int16_t max_angle);
void SweepAndPatrol(void);
void Gimbal_Task_Function(void const * argument);
void CAN_Send_Gimbal(int16_t yaw_raw, int16_t pitch_raw);
int32_t parse_pack(char* pack, char* yaw_data);
double off_dist(double abs_angle);
// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

double abs_pitch;
double abs_yaw;
comm_rx_info comm_pack;
char *pdata[PACKLEN]; // data packet from computer //Make sure to define a size, else the interrupt will not work!
int16_t yaw_rx_angle;
int16_t pitch_rx_angle;

#endif /* SRC_APPLICATIONS_GIMBAL_APP_H_ */
