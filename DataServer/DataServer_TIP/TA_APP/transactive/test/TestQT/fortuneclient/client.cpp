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
#include <QtNetwork/QtNetwork>

#include "client.h"

//! [0]
Client::Client(QWidget *parent)
:   QDialog(parent)
{
//! [0]
    hostLabel = new QLabel(tr("&Server name:"));
    portLabel = new QLabel(tr("S&erver port:"));


    hostLineEdit = new QLineEdit("");
    portLineEdit = new QLineEdit;
    portLineEdit->setValidator(new QIntValidator(1, 65535, this));

    hostLabel->setBuddy(hostLineEdit);
    portLabel->setBuddy(portLineEdit);

    statusLabel = new QLabel(tr("This examples requires that you run the "
                                "Fortune Server example as well."));

    getFortuneButton = new QPushButton(tr("Get Fortune"));
    getFortuneButton->setDefault(true);
    getFortuneButton->setEnabled(true);

    quitButton = new QPushButton(tr("Quit"));

    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(getFortuneButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

//! [1]
    m_pClientTcpSocket = new QTcpSocket(NULL);
//! [1]

    connect(hostLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(enableGetFortuneButton()));
    connect(portLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(enableGetFortuneButton()));
    connect(getFortuneButton, SIGNAL(clicked()),
            this, SLOT(requestNewFortune()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(slotQuitButton()));
//! [2] //! [3]

	QObject::connect(m_pClientTcpSocket, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));

	connect(m_pClientTcpSocket, SIGNAL(connected()), this, SLOT(connectToServerOk()));

    connect(m_pClientTcpSocket, SIGNAL(readyRead()), this, SLOT(readFortune()));
//! [2] //! [4]
    connect(m_pClientTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
           this, SLOT(displayError(QAbstractSocket::SocketError)));
//! [4]

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(hostLabel, 0, 0);
    mainLayout->addWidget(hostLineEdit, 0, 1);
    mainLayout->addWidget(portLabel, 1, 0);
    mainLayout->addWidget(portLineEdit, 1, 1);
    mainLayout->addWidget(statusLabel, 2, 0, 1, 2);
    mainLayout->addWidget(buttonBox, 3, 0, 1, 2);
    setLayout(mainLayout);

    setWindowTitle(tr("Fortune Client"));
    portLineEdit->setFocus();
	getFortuneButton->setEnabled(true);
	statusLabel->setText(tr("Opening network session."));

//! [5]
}
//! [5]

//! [6]
void Client::requestNewFortune()
{
    getFortuneButton->setEnabled(false);
    blockSize = 0;
    m_pClientTcpSocket->abort();//Aborts the current connection and resets the socket.
//! [7]
    /*m_pClientTcpSocket->connectToHost(hostLineEdit->text(),
                             portLineEdit->text().toInt());*/

	m_pClientTcpSocket->connectToHost("192.168.253.130",5000);
	bool connected = m_pClientTcpSocket->waitForConnected();//只有使用waitForConnected()后,QTcpSocket才真正尝试连接服务器，并返回是否连接的结果
//! [7]
}
//! [6]

//! [8]
void Client::readFortune()
{
//! [9]
    QDataStream in(m_pClientTcpSocket);
	quint16 nHeaderDataValue = 0;

    in.setVersion(QDataStream::Qt_4_0);

    if (nHeaderDataValue == 0) {
        if (m_pClientTcpSocket->bytesAvailable() < (int)sizeof(quint16))
            return;
//! [8]

//! [10]
        in >> nHeaderDataValue;
    }

    if (m_pClientTcpSocket->bytesAvailable() < nHeaderDataValue)
        return;
//! [10] //! [11]

    QString nextFortune;
    in >> nextFortune;

    
//! [9]
    statusLabel->setText(nextFortune);
    getFortuneButton->setEnabled(true);

}
//! [12]

//! [13]
void Client::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(m_pClientTcpSocket->errorString()));
    }

    getFortuneButton->setEnabled(true);
}
//! [13]




void Client::connectToServerOk()
{
	QString strlocalAddress;
	quint16 nLocalPort = 0;
	QString strPeerAddress;
	QString strPeerName;
	quint16 nPeerPort = 0;
	strlocalAddress = m_pClientTcpSocket->localAddress().toString();
	nLocalPort = m_pClientTcpSocket->localPort();
	strPeerAddress = m_pClientTcpSocket->peerAddress().toString();
	strPeerName = m_pClientTcpSocket->peerName();
	nPeerPort = m_pClientTcpSocket->peerPort();

	send_req();

}

void Client::send_req()
{
	qint64 nWriteDataLen = 0;
	bool bwaitForBytesWritten = false;
	QString strReq = "Req_Type_1";
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);
	out << (quint16)(strReq.size());
	out << strReq;
	//! [3] //! [4]

	nWriteDataLen = m_pClientTcpSocket->write(block);
	bwaitForBytesWritten = m_pClientTcpSocket->waitForBytesWritten();

}

void Client::slotDisconnected()
{

}


void Client::slotQuitButton()
{
	if (NULL != m_pClientTcpSocket)
	{
		m_pClientTcpSocket->disconnectFromHost();
		m_pClientTcpSocket->waitForDisconnected();
		delete m_pClientTcpSocket;
		m_pClientTcpSocket = NULL;
	}

	//this->close();
}