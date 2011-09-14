/*
 * settings.h
 *
 *  Created on: 21.8.2011
 *      Author: Adam Juraszek
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <QtCore/QtCore>

class Settings {
public:
	static Settings *settings();
	QString getSchemaPrefix() {
		return schemaPrefix;
	}
	void setSchemaPrefix(QString prefix) {
		schemaPrefix = prefix;
	}
	QString getUserPrefix() {
		return userPrefix;
	}
	void setUserPrefix(QString prefix) {
		userPrefix = prefix;
	}
	QString getDir() {
		return dir;
	}
	void setDir(QString dir) {
		Settings::dir = dir;
	}
	bool isDebug() {
		return debug;
	}
	void setDebug(bool debug) {
		Settings::debug = debug;
	}

private:
	static QMutex *mutex;
	static Settings *inst;
	QString schemaPrefix;
	QString userPrefix;
	QString dir;
	bool debug;
	Settings();
	~Settings();
};

#endif /* SETTINGS_H_ */
