#ifndef PICTUREDELEGATE_H
#define PICTUREDELEGATE_H

#include <QStyledItemDelegate>

class PictureDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    PictureDelegate(QObject* parent = 0);

    //allow us to paint the item like we want
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    //sizeHint() function will be used to specify the item size
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

#endif // PICTUREDELEGATE_H
