#include "qextendedbutton.hh"

QExtendedButton::QExtendedButton(QWidget* parent) : QPushButton(parent)
{
    questioned = false;
    flagged = false;
}

void QExtendedButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::RightButton)
    {
        emit rightClicked();
    }
    else if(e->button() == Qt::LeftButton)
    {
        emit leftClicked();
    }
    QPushButton::mousePressEvent(e);
}

void QExtendedButton::setQuestioned(bool status)
{
    questioned = status;
}

bool QExtendedButton::isQuestioned()
{
    return questioned;
}

void QExtendedButton::setFlagged(bool flag)
{
    flagged = flag;
}

bool QExtendedButton::isFlagged()
{
    return flagged;
}
