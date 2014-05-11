#include <stdio.h>
#include "xc.h"

//Remerciements à Damien Radtke
//Mets à jouer les différents axes du controller en fonction de l'évènement reçu
static void xc_update_axes(XC_STATE *state, ALLEGRO_EVENT event)
{
	int axis = event.joystick.axis;
	float pos = event.joystick.pos;

	switch (event.joystick.stick) {
		case 0:
			if (axis == 0)
				state->left_stick_x = pos;
			else if (axis == 1)
				state->left_stick_y = pos;
			break;
		case 1:
			if (axis == 0)
				state->left_trigger = (pos + 1.0) / 2.0;
			else if (axis == 1)
				state->right_stick_x = pos;
			break;
		case 2:
			if (axis == 0)
				state->right_stick_y = pos;
			else if (axis == 1)
				state->right_trigger = (pos + 1.0) / 2.0;
			break;
		case 3:
			if (axis == 0)
				state->dpad_x = pos;
			else if (axis == 1)
				state->dpad_y = pos;
			break;
	}
}

//Met à jour les différents boutons du controlleur en fonction de l'évènement reçu
static void xc_update_buttons(XC_STATE *state, ALLEGRO_EVENT event)
{
	bool value = (event.type == XC_EVENT_BUTTON_DOWN);
	switch (event.joystick.button) {
		case 0:
			state->button_a = value;
			break;
		case 1:
			state->button_b = value;
			break;
		case 2:
			state->button_x = value;
			break;
		case 3:
			state->button_y = value;
			break;
		case 4:
			state->button_left_shoulder = value;
			break;
		case 5:
			state->button_right_shoulder = value;
			break;
		case 6:
			state->button_back = value;
			break;
		case 7:
			state->button_start = value;
			break;
		case 8:
			state->button_xbox = value;
			break;
		case 9:
			state->button_left_stick = value;
			break;
		case 10:
			state->button_right_stick = value;
			break;
		default:
			fprintf(stderr, "[XC] Error: unexpected button (%d)\n", event.joystick.button);
			break;
	}
}

//install de le controlleur avec la commande allegro
bool xc_install()
{
	return al_install_joystick();
}

//à utiliser pour permettre de brancher un controlleur en route
bool xc_reconfigure()
{
	return al_reconfigure_joysticks();
}

//Initialise les différents boutons et sticks
void xc_clear_state(XC_STATE *state)
{
	state->left_stick_x = 0;
	state->left_stick_y = 0;
	state->left_trigger = 0;
	state->right_stick_x = 0;
	state->right_stick_y = 0;
	state->right_trigger = 0;
	state->dpad_x = 0;
	state->dpad_y = 0;
	state->button_a = false;
	state->button_b = false;
	state->button_x = false;
	state->button_y = false;
	state->button_left_stick = false;
	state->button_right_stick = false;
	state->button_left_shoulder = false;
	state->button_right_shoulder = false;
	state->button_start = false;
	state->button_back = false;
	state->button_xbox = false;
}

/*
 * Gets the state for a controller.
 */
void xc_get_state(XC_STATE *controller)
{
	xc_clear_state(controller);
}

//libere la mémoire
void xc_free_state(XC_STATE *state)
{
	free(state->joy);
	free(state);
}


ALLEGRO_EVENT_SOURCE *xc_get_event_source()
{
	return al_get_joystick_event_source();
}


void xc_update(ALLEGRO_EVENT event,XC_STATE *controller)
{
	
	switch (event.type) {
		case XC_EVENT_AXIS:
			xc_update_axes(controller, event);
			break;
		case XC_EVENT_BUTTON_DOWN:
		case XC_EVENT_BUTTON_UP:
			xc_update_buttons(controller, event);
			break;
		default:
			fprintf(stderr, "[XC] Error: unrecognized event (%d)\n", event.type);
			break;
	}
}
