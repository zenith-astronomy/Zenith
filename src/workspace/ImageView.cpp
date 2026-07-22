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

#include "ImageView.h"

#include <QPainter>

ImageView::ImageView(QWidget* parent) : QWidget(parent)
{
}

void ImageView::SetImage(const Image& image)
{
    m_image = QImage(image.width,
                     image.height,
                     QImage::Format_Grayscale8);

    const auto [minIt, maxIt] = std::minmax_element(image.pixels.begin(),
                                                    image.pixels.end());

    const float min = *minIt;
    const float max = *maxIt;
    const float range = std::max(max - min, 1.0f);

    for (int y = 0; y < image.height; ++y)
    {
        uchar* scanline = m_image.scanLine(y);

        for (int x = 0; x < image.width; ++x)
        {
            const float pixel = image.pixels[y * image.width + x];

            const float normalized = (pixel - min) / range;

            scanline[x] = static_cast<uchar>(
                normalized * 255.0f + 0.5f);
        }
    }

    resize(m_image.size());
    update();
}

void ImageView::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    painter.drawImage(0, 0, m_image);
}