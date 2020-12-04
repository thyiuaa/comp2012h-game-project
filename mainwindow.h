#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "GameField.h"
#include "GameEngine.h"
#include "exitconfirm.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// handle signal from user, i.e. keyboard pressing, menu clicking
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override; // close all windows if user click yes in exit confirm window, else do nothing
    bool up_pressed {false}, down_pressed {false}, left_pressed {false}, right_pressed {false}, space_pressed {false};
    void keyPressEvent(QKeyEvent *event) override; // set the above corresponding keypress to true
    void keyReleaseEvent(QKeyEvent *event) override; // set the above corresponding keypress to false

private slots:
    void on_startButton_clicked(); // start the game
    void on_leaveButton_clicked(); // show exit confirm window
    void refresh_screen(); // action performed by the refresher

private:
    Ui::MainWindow *ui;
    ExitConfirm exit_confirm_window;
    GameEngine game_engine; // interact with game element through the engine
    GameField game_field; // the display area of the game
    const int SCREEN_REFRESH_INTERVAL {10}; // millisecond
    QTimer* screen_refresher {nullptr}; // this will refresh the screen for every SCREEN_REFRESH_INTERVAL millisecond
};
#endif // MAINWINDOW_H
