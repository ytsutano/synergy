/*
 * synergy -- mouse and keyboard sharing utility
 * Copyright (C) 2015 Synergy Si Inc.
 *
 * This package is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * found in the file LICENSE that should have accompanied this file.
 *
 * This package is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LOGFILEREADER_H
#define LOGFILEREADER_H

#include <QObject>

class QFileSystemWatcher;
class QFile;

class LogFileReader : public QObject
{
	Q_OBJECT

public:
	LogFileReader(QString filename);
	~LogFileReader();

signals:
	void readLogLine(const QString& text);

public slots:
	void handleFileChanged(const QString& filenam);

private:
	QString m_Filename;
	QFileSystemWatcher* m_pFileSystemWatcher;
	QFile* m_pFile;
};

#endif // LOGFILEREADER_H
