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

#include "AboutZenithDialog.h"

#include <QBoxLayout>
#include <QLabel>

AboutZenithDialog::AboutZenithDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("About Zenith");
    resize(300, 200);

    auto* root_layout = new QVBoxLayout(this);
    auto* content_layout = new QHBoxLayout();
    auto* text_layout = new QVBoxLayout();

    root_layout->addLayout(content_layout);
    content_layout->addLayout(text_layout);

    auto* title = new QLabel("Zenith 1.0.0", this);
    QFont title_font;
    title_font.setBold(true);
    title_font.setPointSize(16);
    title->setFont(title_font);


    auto* p1 = new QLabel("Zenith is a free (free as in freedom) and open-source GUI application "
                          "for astrophotographic image processing, based around the Qt framework", this);
    p1->setWordWrap(true);

    text_layout->addWidget(title, 0);
    text_layout->addWidget(p1, 1);

}