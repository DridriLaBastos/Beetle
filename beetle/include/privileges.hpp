#ifndef __PRIVILEGES_H__
#define __PRIVILEGES_H__

constexpr unsigned int ADMIN  = 0;
constexpr unsigned int USER_1 = 1;
constexpr unsigned int USER_2 = 2;
constexpr unsigned int USER_3 = 3;

using USER = USER_3; //User space will always have segment with the less privilege level

#endif