#include "characterlabel.h"

CharacterProperty::CharacterProperty(QString name, int fullhp, int fullmove, int attrack, int attrackable, QWidget *parent):
    QLabel(parent)
{
    setFixedSize(165, 150);
    setPixmap(QPixmap(":/pic/dlg.png"));

    nameLabel.setText(name);
    hpLabel1.setText("血量");
    hpLabel2.setText(QString::number(fullhp)+"/"+QString::number(fullhp));
    moveLabel1.setText("行动力");
    moveLabel2.setText(QString::number(fullmove)+"/"+QString::number(fullmove));
    attrackLabel1.setText("攻击力");
    attrackLabel2.setText(QString::number(attrack));
    attrackableLabel1.setText("攻击范围");
    attrackableLabel2.setText(QString::number(attrackable));

    layout.addWidget(&nameLabel,0,0);
    layout.addWidget(&hpLabel1,1,0);
    layout.addWidget(&hpLabel2,1,1);
    layout.addWidget(&moveLabel1,2,0);
    layout.addWidget(&moveLabel2,2,1);
    layout.addWidget(&attrackLabel1,3,0);
    layout.addWidget(&attrackLabel2,3,1);
    layout.addWidget(&attrackableLabel1,4,0);
    layout.addWidget(&attrackableLabel2,4,1);
    layout.setVerticalSpacing(0);
    setLayout(&layout);
}
void CharacterProperty::updateData(int hp, int fullhp, int move1, int fullmove, int localCellx, int localCelly)
{
    bool ishidden = isHidden();
    int x = 0;
    if((localCellx-1)*CELL_SIZE-165 >= 0)
        x=(localCellx-1)*CELL_SIZE-165;
    else
        x=(localCellx-1)*CELL_SIZE+32;
    move(x,(localCelly-1)*CELL_SIZE);
    hpLabel2.setText(QString::number(hp)+"/"+QString::number(fullhp));
    moveLabel2.setText(QString::number(move1)+"/"+QString::number(fullmove));
    if(ishidden)hide();
    else show();
}

CharacterSelection::CharacterSelection(QWidget* parent):
    QLabel(parent)
{
    layout = new QVBoxLayout;
    moveButton = new QPushButton;
    attrackButton = new QPushButton;
    skipButton = new QPushButton;
    setFixedSize(90,90);
    moveButton->setText("移动");
    attrackButton->setText("攻击");
    skipButton->setText("跳过");
    layout->addWidget(moveButton);
    layout->addWidget(attrackButton);
    layout->addWidget(skipButton);
    layout->setSpacing(0);
    setLayout(layout);
}
void CharacterSelection::updateData(int localCellx, int localCelly)
{
    bool ishidden = isHidden();
    move((localCellx-1)*CELL_SIZE + 64,(localCelly-1)*CELL_SIZE-10);
    if(ishidden)hide();
    else
    {
        show();
        raise();
    }
}

HPLabel::HPLabel(int hp, int totalhp, bool belong,QWidget *parent):
    QLabel(parent), m_hp(hp), m_totalhp(totalhp), m_belong(belong)
{

}

void HPLabel::reset(int t_hp, int t_totalhp, bool t_belong)
{
    m_hp = t_hp;
    m_totalhp = t_totalhp;
    m_belong = t_belong;
}
void HPLabel::paintEvent(QPaintEvent *eve)
{
    QPainter painter(this);
    if(m_belong==YOURS)//敌人
        painter.setBrush(Qt::red);
    else
        painter.setBrush(Qt::blue);
    painter.drawRect(5,0, (1.0 * m_hp / m_totalhp)*CELL_SIZE-10, HP_HEIGHT);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::black);
    painter.drawRect(5,0, CELL_SIZE-10, HP_HEIGHT);
    painter.setPen(Qt::NoPen);
}
