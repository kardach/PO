#pragma once

#ifndef TURN_H_
#define TURN_H_

enum class Team : bool;
class Settings;

class Turn {
private:
    Team m_team;

    unsigned m_count;
public:
    Turn(const Settings&);

    ~Turn();

    void change();

    Team getTeam();

    unsigned int getCount();
};

#endif // TURN_H_