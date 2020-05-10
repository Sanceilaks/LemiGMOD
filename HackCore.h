#pragma once
#include "Singleton.h"


class HackCore : public Singleton<HackCore>
{
public:
	bool Init();
	bool Unload(void* dll);

	//template <class T>
	//void AddError(T msg);
	//template <class T>
	//void AddMsg(T msg);
	//template <class T>
	//void AddLog(T msg);
};