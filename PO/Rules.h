#pragma once

#ifndef RULES_H_
#define RULES_H_

class Rules {
public:
    bool mandatory_capture;

    bool men_move_backwards;

    bool men_capture_backwards;

    bool kings_fly;

    Rules();

    Rules(bool mandatory_capture, bool men_move_backwards, bool men_capture_backwards, bool kings_fly);

    ~Rules();
};

#endif // RULES_H_