/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include <QtGui/QtGui>

#include "fortunethread.h"

#include <QtNetwork/QtNetwork>

//! [0]
FortuneThread::FortuneThread(int socketDescriptor, const QString &fortune, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor), text(fortune)
{
	m_bTerminter = false;
	m_pClientSocket = NULL;
	m_pClientSocket = new QTcpSocket();

	QObject::connect(m_pClientSocket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));

	QObject::connect(m_pClientSocket, SIGNAL(readyRead()), this, SLOT(readReq()));
	//! [2] //! [4]
	QObject::connect(m_pClientSocket, SIGNAL(error(QAbstractSocket::SocketError)),
		this, SLOT(displayError(QAbstractSocket::SocketError)));


	QString strlocalAddress;
	quint16 nLocalPort = 0;
	QString strPeerAddress;
	QString strPeerName;
	quint16 nPeerPort = 0;

	if (!m_pClientSocket->setSocketDescriptor(socketDescriptor))
	{
		QString strError;
		strError = "error:"+m_pClientSocket->errorString();
	}
	else
	{
		strlocalAddress = m_pClientSocket->localAddress().toString();
		nLocalPort = m_pClientSocket->localPort();
		strPeerAddress = m_pClientSocket->peerAddress().toString();
		strPeerName = m_pClientSocket->peerName();
		nPeerPort = m_pClientSocket->peerPort();

	}

}
//! [0]

void FortuneThread::displayError(QAbstractSocket::SocketError socketError)
{
	QString strError;
	switch (socketError) {
	case QAbstractSocket::RemoteHostClosedError:
		break;
	case QAbstractSocket::HostNotFoundError:
		strError = "QAbstractSocket::HostNotFoundError";
		break;
	case QAbstractSocket::ConnectionRefusedError:
		strError = "QAbstractSocket::ConnectionRefusedError";
		
		break;
	default:
		strError = "error:"+m_pClientSocket->errorString();

		
	}

	m_bTerminter = true;
}


void FortuneThread::readReq()
{
	//! [9]
	quint16 nHeaderDataValue = 0;
	QDataStream in(m_pClientSocket);
	in.setVersion(QDataStream::Qt_4_0);

	if (nHeaderDataValue == 0) {
		if (m_pClientSocket->bytesAvailable() < (int)sizeof(quint16))
			return;

		//! [10]
		in >> nHeaderDataValue;
	}

	if (m_pClientSocket->bytesAvailable() < nHeaderDataValue)
		return;

	QString strReq;
	in >> strReq;

	if (strReq == "Req_Type_1")
	{
		writeAck();
	}
}
void FortuneThread::writeAck()
{
	QByteArray block;
	QString strACK = "ACK_Type_1";

	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);
	out << (quint16)(strACK.size());
	out << strACK;
	//! [3] //! [4]

	m_pClientSocket->write(block);

}
//! [1]
void FortuneThread::run()
{

}

void FortuneThread::slotDisconnected()
{
	m_bTerminter = true;

	emit clientDisconnetcd();
}

void FortuneThread::_Unit()
{
	if (NULL != m_pClientSocket)
	{
		m_pClientSocket->waitForDisconnected();
		m_pClientSocket->close();
		delete m_pClientSocket;
		m_pClientSocket = NULL;
	}
}

FortuneThread::~FortuneThread()
{
	_Unit();
}


//! [4]
