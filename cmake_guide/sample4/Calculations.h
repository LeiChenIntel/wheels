#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#ifdef calculations_EXPORTS
#define CALCULATIONS_API __declspec(dllexport)
#else
#define CALCULATIONS_API __declspec(dllimport)
#endif

extern CALCULATIONS_API int calFlag;

CALCULATIONS_API float add(float value1, float value2);
CALCULATIONS_API float subtract(float value1, float value2);
CALCULATIONS_API float multiple(float value1, float value2);
CALCULATIONS_API float divide(float value1, float value2);

#endif // !CALCULATIONS_H
