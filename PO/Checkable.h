#pragma once

#ifndef CHECKABLE_H_
#define CHECKABLE_H_

class Checkable {
public:
    Checkable();

    virtual ~Checkable();

    virtual void check() = 0;

    virtual void uncheck() = 0;

    virtual bool isChecked() const = 0;

};

#endif // CHECKABLE_H_