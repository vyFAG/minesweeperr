#include "minesweeper.h"
#include "ui_minesweeper.h"
#include <QPainter>
#include <QDebug>
#include <cstdlib>
#include <ctime>

MineSweeper::MineSweeper(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MineSweeper)
{srand(time(0));
    this->setFixedSize(side_length * width_cells, side_length * height_cells);
    
    game_field.resize(height_cells + 1);
    
    int bombs_to_add = bombs_count;
    int remain_cells = width_cells * height_cells;
    
    QVector<QVector<int>> bombs_coords;
    int index_of_bomb = 0;
    bombs_coords.resize(bombs_count + 1);
    
    for (int h = 0; h < height_cells; h++) {
        for(int w = 0; w < width_cells; w++) {
            int random = rand() % (remain_cells + bombs_to_add);
            
            game_field[h].resize(width_cells + 1);
            
            if (random >= remain_cells) {
                bombs_coords[index_of_bomb].resize(2);
                bombs_coords[index_of_bomb][0] = h;
                bombs_coords[index_of_bomb][1] = w;
                
                index_of_bomb++;
                
                game_field[h][w] = -1;
                bombs_to_add--;
            } else {
                game_field[h][w] = 1;
            }
            
            remain_cells--;
        }
    }
    
    for (int h = 0; h < height_cells; h++) {
        for(int w = 0; w < width_cells; w++) {
            int bombs_around = 0;
            if (game_field[h][w] != -1) {
                for(int i = 0; i < bombs_count; i++) {
                    if (abs(bombs_coords[i][0] - h) <= 1 && abs(bombs_coords[i][1] - w) <= 1) {
                        bombs_around++;
                    }
                }
                
                game_field[h][w] = bombs_around;
            }
        }
    }
    
    printField();
    
    ui->setupUi(this);
}

MineSweeper::~MineSweeper()
{
    delete ui;
}

void MineSweeper::printField() {
    for (int h = 0; h < height_cells; h++) {
        qDebug() << game_field[h];
    }
}

void MineSweeper::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::FlatCap));
    
    for(int h = 0; h < height_cells; h++) {
        for(int w = 0; w < width_cells; w++) {
            if (game_field[h][w] == -1) {
                painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
                painter.drawRect(w * side_length, h * side_length, side_length, side_length);
            } else {
                painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
                painter.drawRect(w * side_length, h * side_length, side_length, side_length);
            }
        }
    }
}
