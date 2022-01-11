#ifndef QEXTENDEDBUTTON_HH
#define QEXTENDEDBUTTON_HH

#include <QPushButton>
#include <QMouseEvent>

class QExtendedButton : public QPushButton
{
    Q_OBJECT
public:
    explicit QExtendedButton(QWidget* parent=0);
    bool isQuestioned();
    void setQuestioned(bool status);
    bool isFlagged();
    void setFlagged(bool flag);

protected:
    void mousePressEvent(QMouseEvent *e);// override;

signals:
    void rightClicked();
    void leftClicked();

private:
    bool questioned;
    bool flagged;
};

#endif // QEXTENDEDBUTTON_HH
