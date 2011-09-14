/*
 * dateType.cpp
 *
 *  Created on: 9.9.2011
 *      Author: Adam Juraszek
 */

#include "dateType.h"

QString DateType::format = "yyyyMMddHHmmss";

QString DateType::getDataType() {
	if (getName() == "date") {
		return "QDate";
	} else if (getName() == "time") {
		return "QTime";
	} else {
		return "QDateTime";
	}
}

QString DateType::normalize(QString inputString, QString outputVariable) {
	// removes timezone and separators
	return "QString " + outputVariable + " = " + inputString
			+ ".remove(QRegExp(\" [+-].*$\")).remove(QRegExp(\"[^0-9]\"));";
}

QString DateType::generateSetter(QString inputString, QString outputVariable) {
	QString setter = normalize(inputString, "normalized") + "\n";
	setter.append("  bool ok;\n");
	setter.append("  " + getDataType() + " date_;");
	setter.append("  if(normalized.isEmpty()) {\n");
	setter.append("    ok = false;\n");
	setter.append("  } else {\n");
	setter.append(
			"    date_ = " + getDataType()
					+ "::fromString(normalized, QString(\""
					+ (getName() == "time" ? format.right(6) : format)
					+ "\").left(normalized.length()));\n");
	setter.append("    ok = date_.isValid();\n");
	setter.append("  }");
	setter.append("  if(ok) {\n");
	setter.append("    " + outputVariable + " = date_;\n");
	setter.append("  } else {\n");
	setter.append("    return;\n");
	setter.append("  }");
	return setter;
}

QString DateType::generateControl(QString inputString) {
	QString control = "  " + normalize(inputString, "normalized") + "\n";
	control.append("  if(normalized.isEmpty()) {\n");
	control.append("    ok = false;\n");
	control.append("  } else {\n");
	control.append(
			"    " + getDataType() + " date_ = " + getDataType()
					+ "::fromString(normalized, QString(\""
					+ (getName() == "time" ? format.right(6) : format)
					+ "\").left(normalized.length()));\n");
	control.append("    ok = date_.isValid();\n");
	control.append("  }");
	return control;
}

QString DateType::generateInit(QString varName) {
	return varName + " = " + getDataType() + "();";
}
