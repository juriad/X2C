/*
 * settings.cpp
 *
 *  Created on: 21.8.2011
 *      Author: Adam Juraszek
 */

#include "settings.h"

Settings *Settings::inst = NULL;
QMutex *Settings::mutex = new QMutex();

Settings::Settings() {
	schemaPrefix = QString();
	userPrefix = QString();
	dir = new QDir();
	debug = false;
}

Settings *Settings::settings() {
	if (Settings::inst == NULL) {
		mutex->lock();
		if (Settings::inst == NULL) {
			inst = new Settings();
		}
		mutex->unlock();
	}
	return inst;
}
