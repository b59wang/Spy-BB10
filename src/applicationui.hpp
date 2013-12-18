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

#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QObject>
#include <QMetaType>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/TabbedPane>
#include <bb/cascades/ArrayDataModel>
#include <QList>

namespace bb {
namespace cascades {
class Application;
class LocaleHandler;
class TabbedPane;
class ArrayDataModel;
}
}

class QTranslator;

/*!
 * @brief Application object
 *
 *
 */

class ApplicationUI: public QObject {
	Q_OBJECT
public:
	ApplicationUI(bb::cascades::Application *app);
	virtual ~ApplicationUI() {
	}
private slots:
	void onSystemLanguageChanged();
private:
	QTranslator* m_pTranslator;
	bb::cascades::LocaleHandler* m_pLocaleHandler;
	bb::cascades::TabbedPane* m_tabPanel;
	bb::cascades::ArrayDataModel* m_arrayModel;
	QList<QString>* m_wordList;
	int m_numAlive;
	int m_numSpyAlive;
	int m_numWhiteAlive;

public:
	Q_INVOKABLE
	void setPane(bb::cascades::TabbedPane* pane);
	Q_INVOKABLE
	void setNameListView();
	Q_INVOKABLE
	void changeName(int index, QString name);
	Q_INVOKABLE
	void elimateSetup();
	Q_INVOKABLE
	QString elimate(int iSelectedIndex);
	Q_INVOKABLE
	void gameSetup();
	int randInt(int low, int high);
	void grabWords();
};

#endif /* ApplicationUI_HPP_ */
