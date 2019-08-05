#include "main.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor m_drive_front_left(M_DRIVE_FRONT_LEFT);
	pros::Motor m_drive_front_right(M_DRIVE_FRONT_RIGHT, true);
	pros::Motor m_drive_back_left(M_DRIVE_BACK_LEFT);
	pros::Motor m_drive_back_right(M_DRIVE_BACK_RIGHT, true);
	
	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);

		int forward = master.get_analog(ANALOG_LEFT_Y);
		int strafe = master.get_analog(ANALOG_LEFT_X);
		int turn = master.get_analog(ANALOG_RIGHT_X);

		m_drive_back_left 	= forward - strafe + turn;
		m_drive_back_right 	= forward + strafe - turn;
		m_drive_front_left 	= forward + strafe + turn;
		m_drive_front_right = forward - strafe - turn;
		pros::delay(20);
	}
}
