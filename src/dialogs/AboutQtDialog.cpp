/*
    Zenith, astrophotography image processing software.
    Copyright (C) 2026 Stefano De Angelis

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "AboutQtDialog.h"

#include <QBoxLayout>
#include <QLabel>
#include <QLibraryInfo>

AboutQtDialog::AboutQtDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("About Qt");
    resize(600, 500);

    auto* root_layout = new QVBoxLayout(this);
    auto* content_layout = new QHBoxLayout();
    auto* text_layout = new QVBoxLayout();

    root_layout->addLayout(content_layout);
    content_layout->addLayout(text_layout);

    auto* title = new QLabel("About Qt", this);
    QFont title_font;
    title_font.setBold(true);
    title_font.setPointSize(16);
    title->setFont(title_font);

    text_layout->addWidget(title);

    for (auto* label : {
             new QLabel(QString("This program uses Qt version %1.").arg(QLibraryInfo::version().toString()), this),
             new QLabel("Qt is a C++ toolkit for cross-platform application development.", this),
             new QLabel("Qt provides single-source portability across all major desktop operating systems. "
                        "It is also available for embedded Linux and other embedded and mobile operating systems.", this),
             new QLabel("Qt is available under multiple licensing options designed to accomodate the needs of our various users.", this),
             new QLabel("Qt licensed under our commercial license agreement is appropriate for development of "
                        "proprietary/commercial software where you do not want to share any source code with third parties "
                        "or otherwise cannot comply with the terms of GNU (L)GPL.", this),
             new QLabel("Qt licensed under GNU (L)GPL is appropriate for development of Qt applications "
                        "provided you can comply with the terms and conditions of the respective licenses.", this),
             new QLabel("Please see qt.io/licensing for an overview of Qt licensing.", this),
             new QLabel("Copyright (C) The Qt Company Ltd. and other contributors.", this),
             new QLabel("Qt and the Qt logo are trademarks of The Qt Company Ltd.", this),
             new QLabel("Qt is The Qt Company Ltd. product developed as an open source project. "
                        "See qt.io for more information.", this)
         })
    {
        label->setWordWrap(true);
        text_layout->addWidget(label);
    }
}