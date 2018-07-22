#include "picturedelegate.h"

#include <QPainter>

const unsigned int BANNER_HEIGHT = 20;
const unsigned int BANNER_COLOR = 0x303030;
const unsigned int BANNER_ALPHA = 200;
const unsigned int BANNER_TEXT_COLOR = 0xffffff;
const unsigned int HIGHLIGHT_ALPHA = 100;

PictureDelegate::PictureDelegate(QObject* parent) :
    QStyledItemDelegate(parent)
{
}

//each time QListView needs to display an item, this delegate's paint() function will be called
//paint system can be seen as layers that you paint one on top of each other
void PictureDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    painter->save(); //save the painter state before doing anything, to be able to restore it when finished our drawing

    QPixmap pixmap = index.model()->data(index, Qt::DecorationRole).value<QPixmap>(); //get the item thumbnail
    painter->drawPixmap(option.rect.x(), option.rect.y(), pixmap); //draw it with the QPainter::drawPixmap() function

    //paint a translucent gray banner on top of the thumbnail with the QPainter::fillRect() function
    QRect bannerRect = QRect(option.rect.x(), option.rect.y(), pixmap.width(), BANNER_HEIGHT);
    QColor bannerColor = QColor(BANNER_COLOR);
    bannerColor.setAlpha(BANNER_ALPHA);
    painter->fillRect(bannerRect, bannerColor);

    QString filename = index.model()->data(index, Qt::DisplayRole).toString(); //get the item display name
    painter->setPen(BANNER_TEXT_COLOR);
    painter->drawText(bannerRect, Qt::AlignCenter, filename); //draw it on the banner using the QPainter::drawText()

    //if the item is selected, we paint a translucent rectangle on the top using the highlight color from the item
    if (option.state.testFlag(QStyle::State_Selected))
    {
        QColor selectedColor = option.palette.highlight().color();
        selectedColor.setAlpha(HIGHLIGHT_ALPHA);
        painter->fillRect(option.rect, selectedColor);
    }

    painter->restore(); //restore the painter state to its original state
}

//we want the item's size to be equal to the thumbnail size
QSize PictureDelegate::sizeHint(const QStyleOptionViewItem& /*option*/, const QModelIndex& index) const
{
    //retrieve the thumbnail and return its size
    const QPixmap& pixmap = index.model()->data(index, Qt::DecorationRole).value<QPixmap>();
    return pixmap.size();
}
