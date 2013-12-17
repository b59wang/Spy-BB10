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
	AbstractPane *root = qml->createRootObject<AbstractPane>();

	// Set m_tabPanel = 0;
	m_tabPanel = 0;

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
	bb::cascades::ListView* pNameListView = m_tabPanel->findChild<
			bb::cascades::ListView*>("nameListViewQML");

	bb::cascades::DropDown* pPlayersDropDown = m_tabPanel->findChild<
			bb::cascades::DropDown*>("playerDropDownQML");

	bb::cascades::DropDown* pSpiesDropDown = m_tabPanel->findChild<
			bb::cascades::DropDown*>("spyDropDownQML");

	bb::cascades::DropDown* pBlanksDropDown = m_tabPanel->findChild<
			bb::cascades::DropDown*>("whiteDropDownQML");

	if (pNameListView && pPlayersDropDown && pSpiesDropDown &&  pBlanksDropDown){
		int iNumPlayers = pPlayersDropDown->selectedIndex();
		int iNumSpies = pSpiesDropDown->selectedIndex();
		int iNumBlanks = pBlanksDropDown->selectedIndex();
		qDebug() << iNumPlayers << iNumSpies << iNumBlanks << endl;
	}
}