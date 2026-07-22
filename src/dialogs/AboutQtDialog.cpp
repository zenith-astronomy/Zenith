/*
    Zenith, astrophotography image processing software
    Copyright (C) 2026 Stefano De Angelis and contributors (see AUTHORS file)

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
#include <QDialogButtonBox>

AboutQtDialog::AboutQtDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("About Qt");
    resize(560, 440);

    auto* root_layout = new QVBoxLayout(this);
    auto* content_layout = new QHBoxLayout();
    auto* text_layout = new QVBoxLayout();

    auto* title_label = new QLabel(QString("Qt version %1").arg(QLibraryInfo::version().toString()));
    QFont title_font;
    title_font.setBold(true);
    title_font.setPointSize(16);
    title_label->setFont(title_font);

    text_layout->addWidget(title_label);

    for (auto* label : {
             new QLabel(QString("This program uses Qt version %1.").arg(QLibraryInfo::version().toString())),
             new QLabel("Qt is a C++ toolkit for cross-platform application development."),
             new QLabel("Qt provides single-source portability across all major desktop operating systems. "
                        "It is also available for embedded Linux and other embedded and mobile operating systems."),
             new QLabel("Qt is available under multiple licensing options designed to accomodate the needs of our various users."),
             new QLabel("Qt licensed under our commercial license agreement is appropriate for development of "
                        "proprietary/commercial software where you do not want to share any source code with third parties "
                        "or otherwise cannot comply with the terms of GNU (L)GPL."),
             new QLabel("Qt licensed under GNU (L)GPL is appropriate for development of Qt applications "
                        "provided you can comply with the terms and conditions of the respective licenses."),
             new QLabel("Please see qt.io/licensing for an overview of Qt licensing."),
             new QLabel("Copyright (C) The Qt Company Ltd. and other contributors."),
             new QLabel("Qt and the Qt logo are trademarks of The Qt Company Ltd."),
             new QLabel("Qt is The Qt Company Ltd. product developed as an open source project. "
                        "See qt.io for more information.")
         })
    {
        label->setWordWrap(true);
        text_layout->addWidget(label);
    }

    auto* dialog_buttons = new QDialogButtonBox(QDialogButtonBox::Close);
    connect(dialog_buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

    text_layout->addWidget(dialog_buttons);

    content_layout->addLayout(text_layout);
    root_layout->addLayout(content_layout);
}