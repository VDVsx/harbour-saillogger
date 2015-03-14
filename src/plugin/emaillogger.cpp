/*
  Copyright (C) 2015 Valério Valério <vdv100@gmail.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the author nor any other contributors names
      may be used to endorse or promote products derived from this software
      without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS
  BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
  THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "emaillogger.h"

#include <QFileInfo>
#include <QDir>
#include <QDebug>

EmailLogger::EmailLogger(QObject *parent) :
    QObject(parent),
    m_dirty(false),
    m_canWrite(true),
    m_messaging(false),
    m_imap(false),
    m_smtp(false),
    m_pop(false)
{
    // This is ~/.config/QtProject/Messageserver.conf
    m_settings = new QSettings("QtProject", "Messageserver", this);

    QString settingsFile = m_settings->fileName();
    m_canWrite = m_settings->isWritable();

    qDebug() << "File name is: " << settingsFile;
    qDebug() << "File is writable ?" << m_canWrite;

    loadCategories();
}

EmailLogger::~EmailLogger()
{
}

bool EmailLogger::canWrite() const
{
    return m_canWrite;
}

bool EmailLogger::loggingOn() const
{
    return m_loggingOn;
}

void EmailLogger::setLoggingOn(bool state)
{
    if (state != m_loggingOn) {
        m_loggingOn = state;
        m_dirty = true;
        emit loggingOnChanged();
    }
}

bool EmailLogger::category(const categories category) const
{
    switch (category) {
    case Messaging:
        return m_messaging;
    case IMAP:
        return m_imap;
    case SMTP:
        return m_smtp;
    case POP:
        return m_pop;
    default:
        qDebug() << "ERROR: Category not defined...";
        break;
    }
    return false;
}

void EmailLogger::setCategory(const categories category, const bool status)
{
    switch (category) {
    case Messaging:
        m_messaging = status;
        break;
    case IMAP:
        m_imap = status;
        break;
    case SMTP:
        m_smtp = status;
        break;
    case POP:
        m_pop = status;
        break;
    default:
        qDebug() << "ERROR: Can't set category, category not defined";
        break;
    }
}

void EmailLogger::loadCategories()
{
    if (m_settings->allKeys().isEmpty()) {
        qDebug() << "Creating config keys...";
        m_settings->beginGroup("Syslog");
        m_settings->setValue("Enabled",0);
        m_settings->endGroup();

        m_settings->beginGroup("FileLog");
        // proper value needs to be defined to fit harbour rules
        m_settings->setValue("Path", QDir::homePath() + "/messageserver.log");
        m_settings->setValue("Enabled",1);
        m_settings->endGroup();

        m_settings->beginGroup("StdStreamLog");
        m_settings->setValue("Enabled",0);
        m_settings->endGroup();

        m_settings->beginGroup("LogCategories");
        m_settings->setValue("IMAP",1);
        m_settings->setValue("Messaging",1);
        m_settings->setValue("POP",1);
        m_settings->setValue("SMTP",1);
        m_settings->endGroup();

        m_settings->sync();
    }

    m_loggingOn = m_settings->value("FileLog/Enabled", true).toBool();

    //categories
    m_messaging = m_settings->value("LogCategories/Messaging", true).toBool();
    m_imap = m_settings->value("LogCategories/IMAP", true).toBool();
    m_smtp = m_settings->value("LogCategories/SMTP", true).toBool();
    m_pop = m_settings->value("LogCategories/POP", true).toBool();
}

