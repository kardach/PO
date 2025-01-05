#include "Turn.h"
#include "Settings.h"

Turn::Turn(const Settings& settings) {
    m_team = settings.getFirstMove();
    m_count = 1;
}

Turn::~Turn() {
}

void Turn::change() {
    m_team = (Team)!(bool)m_team;
    m_count++;
}

Team Turn::getTeam() {
    return m_team;
}

unsigned int Turn::getCount() {
    return m_count;
}