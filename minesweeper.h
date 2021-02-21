#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MineSweeper; }
QT_END_NAMESPACE

class MineSweeper : public QWidget
{
    Q_OBJECT
    
public:
    MineSweeper(QWidget *parent = nullptr);
    ~MineSweeper();
    void printField();
    
protected:
    void paintEvent(QPaintEvent *event);
    
private:
    Ui::MineSweeper *ui;
    
    int side_length = 20;
    int width_cells = 4;
    int height_cells = 4;
    
    int bombs_count = round((width_cells * height_cells) * 0.2);
    
    QVector<QVector<int>> game_field;
};
#endif // MINESWEEPER_H
