#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setScene(&scene);
    ui->graphicsView->show();

    screen_refersher = new QTimer(this);
    screen_refersher->setInterval(screen_refresh_interval);
    connect(screen_refersher, &QTimer::timeout, this, &MainWindow::refresh_screen);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_startButton_clicked() {
    // hide main menu buttons
    ui->startButton->setVisible(false);
    ui->leaveButton->setVisible(false);

    // create player and enemys
    game_engine.spawn_player(game_field, scene);

    // start the screen refresher
    screen_refersher->start(10);
}

void MainWindow::on_leaveButton_clicked() {
    close();
}

void MainWindow::refresh_screen() {
    game_engine.send_player_move_to_unit(up_pressed, down_pressed, left_pressed, right_pressed);
    game_engine.refresh_all_units_update(game_field);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) return;

    if (!event->isAutoRepeat()) {
        switch (event->key()) {
            case Qt::Key_Up:
                up_pressed = true;
                break;

            case Qt::Key_Down:
                down_pressed = true;
                break;

            case Qt::Key_Left:
                left_pressed = true;
                break;

            case Qt::Key_Right:
                right_pressed = true;
                break;

            default:
                break;
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) return;

    switch (event->key()) {
        case Qt::Key_Up:
            up_pressed = false;
            break;

        case Qt::Key_Down:
            down_pressed = false;
            break;

        case Qt::Key_Left:
            left_pressed = false;
            break;

        case Qt::Key_Right:
            right_pressed = false;
            break;

        default:
            break;
    }
}
