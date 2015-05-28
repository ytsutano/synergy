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

#include "LogFileReader.h"

#include "CoreInterface.h"

#include <QFileSystemWatcher>
#include <QFile>
#include <QTextStream>
#include <QDir>

static const char kLogFilename[] = "synergy.log";

LogFileReader::LogFileReader(QString filename) :
	m_Filename(filename),
	m_pFileSystemWatcher(NULL),
	m_pFile(NULL)
{
	if (filename.isEmpty()) {
		CoreInterface coreInterface;
		m_Filename = coreInterface.getLogDir();
		m_Filename.append(QDir::separator()).append("synergy.log");
	}

	m_pFile = new QFile(m_Filename);
	m_pFile->open(QIODevice::ReadOnly);
	m_pFileSystemWatcher = new QFileSystemWatcher();
	m_pFileSystemWatcher->addPath(m_Filename);
	connect(m_pFileSystemWatcher, SIGNAL(fileChanged(const QString&)), this, SLOT(handleFileChanged(const QString&)));
}

LogFileReader::~LogFileReader()
{
	m_pFile->close();

	delete m_pFile;
	delete m_pFileSystemWatcher;
}

void LogFileReader::handleFileChanged(const QString& filename)
{
	QTextStream in(m_pFile);
	while (!in.atEnd()) {
		QString line = in.readLine();
		readLogLine(line);
	}
}
