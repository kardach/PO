#pragma once

#ifndef TEAM_H_
#define TEAM_H_

enum class Team : bool { Black, White };

Team operator!(const Team& other);

#endif // TEAM_H_