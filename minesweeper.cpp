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
    
    game_field.resize(height_cells);
    
    int bombs_to_add = bombs_count;
    int remain_cells = width_cells * height_cells;
    
    for (int h = 0; h < height_cells; h++) {
        for(int w = 0; w < width_cells; w++) {    
            int random = rand() % remain_cells + bombs_to_add;
            
            game_field.resize(width_cells);
            
            if (random >= remain_cells) {
                game_field[h][w] = 0;
            }
            
            remain_cells--;
        }
    }
    
    for (int h = 0; h < height_cells; h++) {
        for(int w = 0; w < width_cells; w++) {
            int bombs_around = 0;
            for (int i = 0; i < 8; i++) {
                if (w > 0 && h > 0) {
                    if(game_field[h - 1][w - 1] == 0) {
                        bombs_around++;
                    }
                }
                
                else if(h > 0) {
                    if(game_field[h - 1][w] == 0) {
                        bombs_around++;
                    }
                }
                
                else if (w < width_cells + 1 && h > 0) {
                    if(game_field[h - 1][w + 1] == 0) {
                        bombs_around++;
                    }
                }
                
                else if (w > 0) {
                    if(game_field[h][w - 1] == 0) {
                        bombs_around++;
                    }
                }
                
                else if (w < width_cells + 1) {
                    if(game_field[h][w + 1] == 0) {
                        bombs_around++;
                    }
                }
                
                else if (h < height_cells + 1 && w > 0) {
                    if(game_field[h + 1][w - 1] == 0) {
                        bombs_around++;
                    }
                }
                
                else if (h < height_cells + 1) {
                    if(game_field[h + 1][w] == 0) {
                        bombs_around++;
                    }
                }
                
                else if (h < height_cells + 1 && width_cells + 1) {
                    if(game_field[h][w - 1] == 0) {
                        bombs_around++;
                    }
                }
            }
            
            game_field[h][w] = bombs_around;
        }
    }
    
    ui->setupUi(this);
}

MineSweeper::~MineSweeper()
{
    delete ui;
}

void MineSweeper::printField() {
    for (int h = 0; h < height_cells; h++) {
        
    }
}

/*void MineSweeper::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::FlatCap));
    
    for(int h = 0; h < height_cells; h++) {
        for(int w = 0; w < width_cells; w++) {
            if (game_field[h * width_cells + w % height_cells] == 0) {
                painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
                painter.drawRect(w * side_length, h * side_length, side_length, side_length);
            } else {
                painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
                painter.drawRect(w * side_length, h * side_length, side_length, side_length);
            }
        }
    }
}*/
