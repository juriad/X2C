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
	QDir* getDir() {
		return dir;
	}
	void setDir(QDir* dir) {
		Settings::dir = dir;
	}

private:
	static QMutex *mutex;
	static Settings *inst;
	QString schemaPrefix;
	QString userPrefix;
	QDir *dir;
	Settings();
	~Settings();
};

#endif /* SETTINGS_H_ */
