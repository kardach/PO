#include "Team.h"

Team operator!(const Team& other) {
	Team reversed = (other == Team::Black) ? Team::White : Team::Black;
	return reversed;
}