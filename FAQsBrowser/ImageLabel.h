#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>

// A label for showing an image
// mouse click opens a dialog for selecting an image
class ImageLabel : public QLabel
{
	Q_OBJECT
public:
	ImageLabel(QWidget* parent = 0);

protected:
	void mousePressEvent(QMouseEvent*);

signals:
	void valueChanged();
};

#endif // IMAGELABEL_H
