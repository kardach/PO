#include "Rules.h"

Rules::Rules() : mandatory_capture(false), men_move_backwards(false), men_capture_backwards(false), kings_fly(false) {
}

Rules::Rules(bool mandatory_capture, bool men_move_backwards, bool men_capture_backwards, bool kings_fly) :
	mandatory_capture(mandatory_capture),
	men_move_backwards(men_move_backwards),
	men_capture_backwards(men_capture_backwards),
	kings_fly(kings_fly) {
}

Rules::~Rules() {
}