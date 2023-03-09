/**************************************************************************
* Otter Browser: Web browser controlled by the user, not vice-versa.
* Copyright (C) 2013 - 2023 Michal Dutkiewicz aka Emdek <michal@emdek.pl>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
**************************************************************************/

#ifndef OTTER_CacheContentsWidget_H
#define OTTER_CacheContentsWidget_H

#include "../../../ui/ContentsWidget.h"

#include <QtGui/QStandardItemModel>

namespace Otter
{

namespace Ui
{
	class CacheContentsWidget;
}

class Window;

class CacheContentsWidget final : public ContentsWidget
{
	Q_OBJECT

public:
	enum DataRole
	{
		UrlRole = Qt::UserRole,
		SizeRole
	};

	explicit CacheContentsWidget(const QVariantMap &parameters, Window *window, QWidget *parent);
	~CacheContentsWidget();

	void print(QPrinter *printer) override;
	QString getTitle() const override;
	QLatin1String getType() const override;
	QUrl getUrl() const override;
	QIcon getIcon() const override;
	ActionsManager::ActionDefinition::State getActionState(int identifier, const QVariantMap &parameters = {}) const override;
	WebWidget::LoadingState getLoadingState() const override;
	bool eventFilter(QObject *object, QEvent *event) override;

public slots:
	void triggerAction(int identifier, const QVariantMap &parameters = {}, ActionsManager::TriggerType trigger = ActionsManager::UnknownTrigger) override;

protected:
	void changeEvent(QEvent *event) override;
	QStandardItem* findDomainItem(const QString &domain);
	QUrl getEntry(const QModelIndex &index) const;

protected slots:
	void populateCache();
	void removeDomainEntries();
	void removeDomainEntriesOrEntry();
	void openEntry();
	void handleEntryAdded(const QUrl &url);
	void handleEntryRemoved(const QUrl &url);
	void showContextMenu(const QPoint &position);
	void updateActions();

private:
	QStandardItemModel *m_model;
	bool m_isLoading;
	Ui::CacheContentsWidget *m_ui;
};

}

#endif
