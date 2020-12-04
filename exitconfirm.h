#ifndef EXITCONFIRM_H
#define EXITCONFIRM_H

#include <QDialog>

namespace Ui {
class ExitConfirm;
}

// a window to ask if the player really want to exit the game
class ExitConfirm : public QDialog
{
    Q_OBJECT

public:
    explicit ExitConfirm(QWidget *parent = nullptr);
    ~ExitConfirm();
    bool get_leave_game() const;

protected: // calls the signals when show or close
    void showEvent(QShowEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

signals: // no implementation just the triggers of the slots in mainwindow
    void close_mainwindow_signal();
    void show_signal();
    void close_signal();

private slots: // button handler
    void on_buttonBox_accepted(); // clicked yes
    void on_buttonBox_rejected(); // clicked no

private:
    Ui::ExitConfirm *ui;
    bool leave_game {false}; // whether the player want to leave the game
};

#endif // EXITCONFIRM_H
