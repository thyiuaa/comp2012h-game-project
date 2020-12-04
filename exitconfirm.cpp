#include "exitconfirm.h"
#include "ui_exitconfirm.h"

ExitConfirm::ExitConfirm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExitConfirm)
{
    ui->setupUi(this);
    setWindowModality(Qt::ApplicationModal);
}

ExitConfirm::~ExitConfirm()
{
    delete ui;
}

bool ExitConfirm::get_leave_game() const {
    return leave_game;
}

void ExitConfirm::showEvent(QShowEvent *event) {
    show_signal();
}

void ExitConfirm::closeEvent(QCloseEvent *event) {
    close_signal();
}

void ExitConfirm::on_buttonBox_accepted()
{
    leave_game = true;
    close_mainwindow_signal();
    close();
}

void ExitConfirm::on_buttonBox_rejected()
{
    leave_game = false;
    close();
}

