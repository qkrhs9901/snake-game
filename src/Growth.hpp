//아이템 중 Growth 입니다.

#pragma once
#include <ncurses.h>
#include "Drawable.hpp"

class Growth : public Drawable
{
public:
  Growth(int y, int x)
  {
    this->y = y;
    this->x = x;
    this->icon = 'G';
  }
};
