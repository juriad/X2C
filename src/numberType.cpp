/*
 * numberType.cpp
 *
 *  Created on: 9.9.2011
 *      Author: Adam Juraszek
 */

#include "numberType.h"

QString NumberType::getDataType() {
	QString dt;
	if (getName() == "integer" || getName() == "nonPositiveInteger"
			|| getName() == "nonNegativeInteger"
			|| getName() == "positiveInteger") {
		dt = "long long";
		// biggest available
	} else if (getName() == "long" || getName() == "unsignedLong") {
		dt = "long long";
	} else if (getName() == "int" || getName() == "unsignedInt") {
		dt = "int";
	} else if (getName() == "short" || getName() == "unsignedShort") {
		dt = "short";
	} else if (getName() == "byte" || getName() == "unsignedByte") {
		// cannot work with char
		dt = "short";
	} else if (getName() == "decimal" || getName() == "double") {
		dt = "double";
	} else if (getName() == "float") {
		dt = "float";
	} else {
		// most general
		dt = "double";
	}
	if (getName().startsWith("unsigned", Qt::CaseInsensitive)) {
		dt.prepend("unsigned ");
	}
	return dt;
}
QString NumberType::generateSetter(QString inputString,
		QString outputVariable) {
	QString setter = "  QString trimmed = " + inputString + ".trimmed();\n";
	setter.append("  bool ok;\n");
	setter.append("  if(trimmed.isEmpty()) {\n");
	setter.append("    return;\n");
	setter.append("  }\n");
	setter.append("  " + toDataType("trimmed", "number", "&ok") + "\n");
	setter.append("  " + outputVariable + " = number;");
	return setter;
}

QString NumberType::generateControl(QString inputString) {
	QString control = "  QString trimmed = " + inputString + ".trimmed();\n";
	control.append("  if(trimmed.isEmpty()) {\n");
	control.append("    ok = false;\n");
	control.append("  } else {\n");
	control.append("  " + toDataType("trimmed", "number", "&ok") + "\n");
	control.append("  }");
	return control;
}

/*
 * input is previously defined string variable
 * output is dt variable
 * error is previously defined bool* variable -- rather positive
 */
QString NumberType::toDataType(QString input, QString output, QString error) {
	QString dt = getDataType();
	if (dt == "long long") {
		return "  " + dt + " " + output + " = " + input + ".toLongLong(" + error
				+ ");";
	} else if (dt == "unsigned long long") {
		return "  " + dt + " " + output + " = " + input + ".toULongLong("
				+ error + ");";
	} else if (dt == "int") {
		return "  " + dt + " " + output + " = " + input + ".toInt(" + error
				+ ");";
	} else if (dt == "unsigned int") {
		return "  " + dt + " " + output + " = " + input + ".toUInt(" + error
				+ ");";
	} else if (dt == "short") {
		return "  " + dt + " " + output + " = " + input + ".toShort(" + error
				+ ");";
	} else if (dt == "unsigned short") {
		return "  " + dt + " " + output + " = " + input + ".toUShort(" + error
				+ ");";
	} else if (dt == "double") {
		return "  " + dt + " " + output + " = " + input + ".toDouble(" + error
				+ ");";
	} else if (dt == "float") {
		return "  " + dt + " " + output + " = " + input + ".toFloat(" + error
				+ ");";
	}
	return "*(" + error + ") = false;";
}

QString NumberType::generateInit(QString varName) {
	return varName + " = 0;";
}

