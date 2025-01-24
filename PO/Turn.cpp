//#include <SFML/Graphics.hpp> //???

#include "Turn.h"
#include "Settings.h"
#include "Team.h"

Turn::Turn(const Settings& settings) {
    m_team = settings.getFirstMove();
    m_count = 1;
}

Turn::~Turn() {
}

void Turn::change() {
    m_team = !m_team;
    m_count++;
}

Team Turn::getTeam() const {
    return m_team;
}

unsigned int Turn::getCount() const {
    return m_count;
}