#include "imageview.h"

ImageView::ImageView( QWidget* parent)
    :QGraphicsView( parent)
{
    setAcceptDrops(true);
}
void ImageView::dropEvent(QDropEvent* event)

{
    emit sgdropEvent(event);
}
