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
	Controller master = Controller();
	XDriveModel drive = ChassisModelFactory::create(
		M_DRIVE_FRONT_LEFT, M_DRIVE_FRONT_RIGHT, M_DRIVE_BACK_RIGHT, M_DRIVE_BACK_LEFT, 600
	);
	
	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);

		float forward = master.getAnalog(ControllerAnalog::leftY);
		float strafe = master.getAnalog(ControllerAnalog::leftX);
		float turn = master.getAnalog(ControllerAnalog::rightX);

		drive.xArcade(strafe, forward, turn);
		pros::delay(20);
	}
}
