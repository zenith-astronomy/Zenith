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

#include "AboutZenithDialog.h"

#include <QBoxLayout>
#include <QLabel>
#include <QLibraryInfo>
#include <QDialogButtonBox>

AboutZenithDialog::AboutZenithDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("About Zenith");
    resize(500, 400);

    auto* root_layout = new QVBoxLayout(this);
    auto* content_layout = new QHBoxLayout();
    auto* text_layout = new QVBoxLayout();

    auto* title_label = new QLabel("Zenith version 1.0.0");
    QFont title_font;
    title_font.setBold(true);
    title_font.setPointSize(16);
    title_label->setFont(title_font);

    text_layout->addWidget(title_label);

    for (auto* label : {
             new QLabel(QString("This program uses Qt version %1.").arg(QLibraryInfo::version().toString())),
             new QLabel("Zenith is an astrophotography image processing application.")
         })
    {
        label->setWordWrap(true);
        text_layout->addWidget(label);
    }

    QFont license_font;
    license_font.setPointSize(8);

    for (auto* label : {
             new QLabel("Copyright (C) 2026 Stefano De Angelis and contributors (see AUTHORS file)."),
             new QLabel("This program is free software: you can redistribute it and/or modify "
                        "it under the terms of the GNU General Public License as published by "
                        "the Free Software Foundation, either version 3 of the License, or "
                        "(at your option) any later version."),
             new QLabel("This program is distributed in the hope that it will be useful, "
                        "but WITHOUT ANY WARRANTY; without even the implied warranty of "
                        "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the "
                        "GNU General Public License for more details."),
             new QLabel("You should have received a copy of the GNU General Public License "
                        "along with this program.  If not, see <https://www.gnu.org/licenses/>.")
         })
    {
        label->setWordWrap(true);
        label->setFont(license_font);
        text_layout->addWidget(label);
    }

    auto* dialog_buttons = new QDialogButtonBox(QDialogButtonBox::Close);
    connect(dialog_buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

    text_layout->addWidget(dialog_buttons);

    content_layout->addLayout(text_layout);
    root_layout->addLayout(content_layout);
}