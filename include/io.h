#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include <iostream>
#include <unistd.h>
#include <sys/select.h>

bool line_ready();

#endif // IO_H_INCLUDED