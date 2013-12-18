/*
 * Copyright (c) 2011-2013 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>
#include <bb/cascades/ListView>
#include <bb/cascades/QListDataModel>
#include <bb/cascades/ArrayDataModel>
#include <bb/cascades/DropDown>
#include <QString>
#include <QGlobal.h>
#include <QTime>
#include <QFile>

using namespace bb::cascades;

ApplicationUI::ApplicationUI(bb::cascades::Application *app) :
		QObject(app) {
	// prepare the localization
	m_pTranslator = new QTranslator(this);
	m_pLocaleHandler = new LocaleHandler(this);

	bool res = QObject::connect(m_pLocaleHandler,
			SIGNAL(systemLanguageChanged()), this,
			SLOT(onSystemLanguageChanged()));
	// This is only available in Debug builds
	Q_ASSERT(res);
	// Since the variable is not used in the app, this is added to avoid a
	// compiler warning
	Q_UNUSED(res);

	// initial load
	onSystemLanguageChanged();

	// Create scene document from main.qml asset, the parent is set
	// to ensure the document gets destroyed properly at shut down.
	QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

	// Set up context
	qml->setContextProperty("_App", this);

	// Create root object for the UI
	QTime time = QTime::currentTime();
	qsrand((uint) time.msec());
	AbstractPane *root = qml->createRootObject<AbstractPane>();

	// Set m_tabPanel = 0;
	m_numAlive = 0;
	m_numSpyAlive = 0;
	m_numWhiteAlive = 0;
	m_tabPanel = 0;
	m_arrayModel = 0;
	m_wordList = new QList<QString>();
	grabWords();

	// Set created root object as the application scene
	app->setScene(root);
}

void ApplicationUI::onSystemLanguageChanged() {
	QCoreApplication::instance()->removeTranslator(m_pTranslator);
	// Initiate, load and install the application translation files.
	QString locale_string = QLocale().name();
	QString file_name = QString("WhoIsSpy_%1").arg(locale_string);
	if (m_pTranslator->load(file_name, "app/native/qm")) {
		QCoreApplication::instance()->installTranslator(m_pTranslator);
	}
}

void ApplicationUI::setPane(TabbedPane* pane) {
	m_tabPanel = pane;
}

void ApplicationUI::setNameListView() {
	qDebug() << "here" << endl;

	bb::cascades::ListView* pNameListView =
			QCoreApplication::instance()->findChild<bb::cascades::ListView*>(
					"nameListViewQML");

	bb::cascades::DropDown* pPlayersDropDown =
			QCoreApplication::instance()->findChild<bb::cascades::DropDown*>(
					"playerDropDownQML");

	bb::cascades::DropDown* pSpiesDropDown =
			QCoreApplication::instance()->findChild<bb::cascades::DropDown*>(
					"spyDropDownQML");

	bb::cascades::DropDown* pBlanksDropDown =
			QCoreApplication::instance()->findChild<bb::cascades::DropDown*>(
					"whiteDropDownQML");

	if (pNameListView && pPlayersDropDown && pSpiesDropDown
			&& pBlanksDropDown) {
		int iNumPlayers = pPlayersDropDown->selectedIndex() + 5;
		int iNumSpies = pSpiesDropDown->selectedIndex() + 1;
		int iNumBlanks = pBlanksDropDown->selectedIndex() + 1;
		qDebug() << iNumPlayers << iNumSpies << iNumBlanks << endl;

		bb::cascades::ArrayDataModel* pDataModel =
				(bb::cascades::ArrayDataModel*) pNameListView->dataModel();

		int iOldSize = pDataModel->size();

		if (iNumPlayers < iOldSize) {
			for (int i = iOldSize - 1; i >= iNumPlayers; i--) {
				pDataModel->removeAt(i);
			}
		} else {
			QMap<QString, QVariant> mapPlayerInfo;
			for (int i = iOldSize; i < iNumPlayers; i++) {
				QVariant qPlayerName(QString::fromUtf8("玩家") + QString::number(i + 1));
				QVariant qPlayerRole("normal");
				QVariant qPlayerIndex(i);
				QVariant qPlayerStatus(true);
				mapPlayerInfo["name"] = qPlayerName;
				mapPlayerInfo["role"] = qPlayerRole;
				mapPlayerInfo["index"] = qPlayerIndex;
				mapPlayerInfo["alive"] = qPlayerStatus;
				pDataModel->append(mapPlayerInfo);
			}
		}

		m_arrayModel = pDataModel;
	}
}

void ApplicationUI::changeName(int index, QString name) {

	bb::cascades::ListView* pNameListView =
			QCoreApplication::instance()->findChild<bb::cascades::ListView*>(
					"nameListViewQML");

	bb::cascades::ArrayDataModel* pDataModel =
			(bb::cascades::ArrayDataModel*) pNameListView->dataModel();

	QMap<QString, QVariant> mapTempMap = pDataModel->value(index).toMap();
	mapTempMap["name"] = name;

	pDataModel->removeAt(index);
	pDataModel->insert(index, QVariant(mapTempMap));
}

void ApplicationUI::grabWords() {
	QFile textfile("app/native/assets/words/words.txt");

	if (textfile.exists()
			&& textfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream stream(&textfile);
		QString line;
		do {
			line = stream.readLine();
			if (line != "") {
				m_wordList->append(line);
			}
		} while (!line.isNull());
	} else {
		qDebug() << "No file ERROR!";
	}
	textfile.close();
}

void ApplicationUI::gameSetup() {
	QTime time = QTime::currentTime();
		qsrand((uint) time.msec());

	bb::cascades::ListView* pGameListView =
			QCoreApplication::instance()->findChild<bb::cascades::ListView*>(
					"gameRoleListViewQML");

	bb::cascades::DropDown* pPlayersDropDown =
			QCoreApplication::instance()->findChild<bb::cascades::DropDown*>(
					"playerDropDownQML");

	bb::cascades::DropDown* pSpiesDropDown =
			QCoreApplication::instance()->findChild<bb::cascades::DropDown*>(
					"spyDropDownQML");

	bb::cascades::DropDown* pBlanksDropDown =
			QCoreApplication::instance()->findChild<bb::cascades::DropDown*>(
					"whiteDropDownQML");

	if (pGameListView && pPlayersDropDown && pSpiesDropDown
			&& pBlanksDropDown) {
		int iNumPlayers = pPlayersDropDown->selectedIndex() + 5;
		int iNumSpies = pSpiesDropDown->selectedIndex() + 1;
		int iNumBlanks = pBlanksDropDown->selectedIndex() + 1;
		qDebug() << iNumPlayers << iNumSpies << iNumBlanks << endl;

		setNameListView();

		int iRandom = randInt(0, m_wordList->size() - 1);
		QStringList sRandomedWord = m_wordList->at(iRandom).split(",");
		QString sWordOne = sRandomedWord.at(0);
		QString sWordTwo = sRandomedWord.at(1);

		int arrRandomInt[iNumPlayers];
		for (int i = 0; i < iNumPlayers; i++) {
			arrRandomInt[i] = i;
		}

		m_numAlive = iNumPlayers;
		for (int i = 0; i < iNumPlayers; i++) {
			int iRandom = randInt(0, iNumPlayers - 1);
			int iTemp = arrRandomInt[iRandom];
			arrRandomInt[iRandom] = arrRandomInt[i];
			arrRandomInt[i] = iTemp;

			QMap<QString, QVariant> mapPlayerInfo =
					m_arrayModel->value(i).toMap();
			mapPlayerInfo["role"] = QVariant("normal");
			mapPlayerInfo["alive"] = QVariant(true);
			mapPlayerInfo["word"] = QVariant(sWordOne);
			m_arrayModel->replace(i, mapPlayerInfo);
		}

		m_numSpyAlive = iNumSpies;
		for (int i = 0; i < iNumSpies; i++) {
			QMap<QString, QVariant> mapPlayerInfo = m_arrayModel->value(
					arrRandomInt[i]).toMap();
			mapPlayerInfo["role"] = QVariant("spy");
			mapPlayerInfo["alive"] = QVariant(true);
			mapPlayerInfo["word"] = QVariant(sWordTwo);
			m_arrayModel->replace(arrRandomInt[i], mapPlayerInfo);
		}

		m_numWhiteAlive = iNumBlanks;
		for (int i = iNumSpies; i < iNumSpies + iNumBlanks; i++) {
			QMap<QString, QVariant> mapPlayerInfo = m_arrayModel->value(
					arrRandomInt[i]).toMap();
			mapPlayerInfo["role"] = QVariant("white");
			mapPlayerInfo["alive"] = QVariant(true);
			mapPlayerInfo["word"] = QVariant(QString::fromUtf8("[白][板]"));
			m_arrayModel->replace(arrRandomInt[i], mapPlayerInfo);
		}

		pGameListView->setDataModel(m_arrayModel);
	}
}

int ApplicationUI::randInt(int low, int high) {
	// Random number between low and high
	return qrand() % ((high + 1) - low) + low;
}

void ApplicationUI::elimateSetup() {
	bb::cascades::ListView* pGameListView =
			QCoreApplication::instance()->findChild<bb::cascades::ListView*>(
					"gameListViewQML");
	if (pGameListView) {
		pGameListView->setDataModel(m_arrayModel);
		pGameListView->setEnabled(true);
	}
}

QString ApplicationUI::elimate(int iSelectedIndex) {
	qDebug() << "elimate " <<  iSelectedIndex << " alive: " << m_numAlive << m_numSpyAlive << m_numWhiteAlive << endl;

	QString sResult = "";
	QMap<QString, QVariant> mapPlayerInfo =
			m_arrayModel->value(iSelectedIndex).toMap();

	mapPlayerInfo["alive"] = QVariant(false);
	QVariant temp = mapPlayerInfo["role"];

	m_numAlive--;
	if (temp.toString() == "spy") {
		m_numSpyAlive--;
	} else if (temp.toString() == "white"){
		m_numWhiteAlive--;
	}
	m_arrayModel->replace(iSelectedIndex, mapPlayerInfo);

	if(m_numSpyAlive == 0 && m_numWhiteAlive == 0){
		sResult = QString::fromUtf8("平民获胜");
	} else if(m_numAlive == 2){
		if (m_numSpyAlive == 0) {
			sResult = QString::fromUtf8("白板获胜");
		} else if (m_numWhiteAlive == 0){
			sResult = QString::fromUtf8("间谍获胜");
		} else {
			sResult = QString::fromUtf8("白板和间谍获胜");
		}
	} else if (m_numSpyAlive > (m_numAlive - m_numSpyAlive -  m_numWhiteAlive) && m_numWhiteAlive == 0){
		sResult = QString::fromUtf8("间谍获胜");
	} else if (m_numWhiteAlive > (m_numAlive - m_numSpyAlive -  m_numWhiteAlive) && m_numSpyAlive == 0){
		sResult = QString::fromUtf8("白板获胜");
	}

	return sResult;
}
