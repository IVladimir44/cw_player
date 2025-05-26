/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QVBoxLayout *trackInfoLayout;
    QLabel *trackInfoLabel;
    QSlider *positionSlider;
    QLabel *timeLabel;
    QHBoxLayout *contentLayout;
    QVBoxLayout *controlLayout;
    QHBoxLayout *mainButtonsLayout;
    QPushButton *prevButton;
    QPushButton *playButton;
    QPushButton *nextButton;
    QHBoxLayout *additionalButtonsLayout;
    QPushButton *stopButton;
    QPushButton *shuffleButton;
    QPushButton *repeatButton;
    QVBoxLayout *volumeLayout;
    QLabel *volumeLabel;
    QSlider *volumeSlider;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *playlistLayout;
    QLabel *playlistLabel;
    QHBoxLayout *playlistButtonsLayout;
    QPushButton *openPlaylistButton;
    QPushButton *removeTrackButton;
    QPushButton *clearPlaylistButton;
    QListWidget *playlistWidget;
    QStatusBar *statusbar;
    QLabel *statusLabel;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(900, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QVBoxLayout(centralwidget);
        mainLayout->setObjectName("mainLayout");
        trackInfoLayout = new QVBoxLayout();
        trackInfoLayout->setObjectName("trackInfoLayout");
        trackInfoLabel = new QLabel(centralwidget);
        trackInfoLabel->setObjectName("trackInfoLabel");
        trackInfoLabel->setAlignment(Qt::AlignCenter);
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        trackInfoLabel->setFont(font);
        trackInfoLabel->setMinimumHeight(40);

        trackInfoLayout->addWidget(trackInfoLabel);

        positionSlider = new QSlider(centralwidget);
        positionSlider->setObjectName("positionSlider");
        positionSlider->setOrientation(Qt::Horizontal);
        positionSlider->setMinimum(0);
        positionSlider->setMaximum(0);

        trackInfoLayout->addWidget(positionSlider);

        timeLabel = new QLabel(centralwidget);
        timeLabel->setObjectName("timeLabel");
        timeLabel->setAlignment(Qt::AlignCenter);
        QFont font1;
        font1.setPointSize(12);
        timeLabel->setFont(font1);

        trackInfoLayout->addWidget(timeLabel);


        mainLayout->addLayout(trackInfoLayout);

        contentLayout = new QHBoxLayout();
        contentLayout->setObjectName("contentLayout");
        controlLayout = new QVBoxLayout();
        controlLayout->setSpacing(15);
        controlLayout->setObjectName("controlLayout");
        mainButtonsLayout = new QHBoxLayout();
        mainButtonsLayout->setObjectName("mainButtonsLayout");
        prevButton = new QPushButton(centralwidget);
        prevButton->setObjectName("prevButton");
        prevButton->setMinimumSize(QSize(120, 40));

        mainButtonsLayout->addWidget(prevButton);

        playButton = new QPushButton(centralwidget);
        playButton->setObjectName("playButton");
        playButton->setMinimumSize(QSize(150, 40));

        mainButtonsLayout->addWidget(playButton);

        nextButton = new QPushButton(centralwidget);
        nextButton->setObjectName("nextButton");
        nextButton->setMinimumSize(QSize(120, 40));

        mainButtonsLayout->addWidget(nextButton);


        controlLayout->addLayout(mainButtonsLayout);

        additionalButtonsLayout = new QHBoxLayout();
        additionalButtonsLayout->setObjectName("additionalButtonsLayout");
        stopButton = new QPushButton(centralwidget);
        stopButton->setObjectName("stopButton");
        stopButton->setMinimumSize(QSize(80, 35));

        additionalButtonsLayout->addWidget(stopButton);

        shuffleButton = new QPushButton(centralwidget);
        shuffleButton->setObjectName("shuffleButton");
        shuffleButton->setMinimumSize(QSize(100, 35));

        additionalButtonsLayout->addWidget(shuffleButton);

        repeatButton = new QPushButton(centralwidget);
        repeatButton->setObjectName("repeatButton");
        repeatButton->setMinimumSize(QSize(80, 35));

        additionalButtonsLayout->addWidget(repeatButton);


        controlLayout->addLayout(additionalButtonsLayout);

        volumeLayout = new QVBoxLayout();
        volumeLayout->setObjectName("volumeLayout");
        volumeLabel = new QLabel(centralwidget);
        volumeLabel->setObjectName("volumeLabel");
        volumeLabel->setAlignment(Qt::AlignCenter);
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        volumeLabel->setFont(font2);

        volumeLayout->addWidget(volumeLabel);

        volumeSlider = new QSlider(centralwidget);
        volumeSlider->setObjectName("volumeSlider");
        volumeSlider->setOrientation(Qt::Horizontal);
        volumeSlider->setMinimum(0);
        volumeSlider->setMaximum(100);
        volumeSlider->setValue(70);

        volumeLayout->addWidget(volumeSlider);


        controlLayout->addLayout(volumeLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        controlLayout->addItem(verticalSpacer);


        contentLayout->addLayout(controlLayout);

        playlistLayout = new QVBoxLayout();
        playlistLayout->setObjectName("playlistLayout");
        playlistLabel = new QLabel(centralwidget);
        playlistLabel->setObjectName("playlistLabel");
        QFont font3;
        font3.setPointSize(12);
        font3.setBold(true);
        playlistLabel->setFont(font3);

        playlistLayout->addWidget(playlistLabel);

        playlistButtonsLayout = new QHBoxLayout();
        playlistButtonsLayout->setObjectName("playlistButtonsLayout");
        openPlaylistButton = new QPushButton(centralwidget);
        openPlaylistButton->setObjectName("openPlaylistButton");
        openPlaylistButton->setMinimumSize(QSize(100, 30));

        playlistButtonsLayout->addWidget(openPlaylistButton);

        removeTrackButton = new QPushButton(centralwidget);
        removeTrackButton->setObjectName("removeTrackButton");
        removeTrackButton->setMinimumSize(QSize(100, 30));

        playlistButtonsLayout->addWidget(removeTrackButton);

        clearPlaylistButton = new QPushButton(centralwidget);
        clearPlaylistButton->setObjectName("clearPlaylistButton");
        clearPlaylistButton->setMinimumSize(QSize(100, 30));

        playlistButtonsLayout->addWidget(clearPlaylistButton);


        playlistLayout->addLayout(playlistButtonsLayout);

        playlistWidget = new QListWidget(centralwidget);
        playlistWidget->setObjectName("playlistWidget");
        playlistWidget->setMinimumSize(QSize(300, 200));
        playlistWidget->setAlternatingRowColors(true);

        playlistLayout->addWidget(playlistWidget);


        contentLayout->addLayout(playlistLayout);


        mainLayout->addLayout(contentLayout);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        statusLabel = new QLabel(statusbar);
        statusLabel->setObjectName("statusLabel");
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 900, 22));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Audio Player", nullptr));
        trackInfoLabel->setText(QCoreApplication::translate("MainWindow", "\320\222\320\270\320\261\320\265\321\200\321\226\321\202\321\214 \321\204\320\260\320\271\320\273\320\270 \320\264\320\273\321\217 \320\277\321\200\320\276\320\263\321\200\320\260\320\262\320\260\320\275\320\275\321\217", nullptr));
        timeLabel->setText(QCoreApplication::translate("MainWindow", "00:00 / 00:00", nullptr));
        prevButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\277\320\265\321\200\320\265\320\264\320\275\321\226\320\271", nullptr));
        playButton->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\263\321\200\320\260\320\262\320\260\320\275\320\275\321\217", nullptr));
        nextButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\203\320\277\320\275\320\270\320\271", nullptr));
        stopButton->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\276\320\277", nullptr));
        shuffleButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\274\321\226\321\210\320\260\321\202\320\270", nullptr));
        repeatButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\262\321\202\320\276\321\200", nullptr));
        volumeLabel->setText(QCoreApplication::translate("MainWindow", "\320\223\321\203\321\207\320\275\321\226\321\201\321\202\321\214: 70%", nullptr));
        playlistLabel->setText(QCoreApplication::translate("MainWindow", "\320\237\320\273\320\265\320\271\320\273\320\270\321\201\321\202", nullptr));
        openPlaylistButton->setText(QCoreApplication::translate("MainWindow", "\320\222\321\226\320\264\320\272\321\200\320\270\321\202\320\270", nullptr));
        removeTrackButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\270\320\264\320\260\320\273\320\270\321\202\320\270", nullptr));
        clearPlaylistButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\320\270", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "\320\223\320\276\321\202\320\276\320\262\320\270\320\271 \320\264\320\276 \320\277\321\200\320\276\320\263\321\200\320\260\320\262\320\260\320\275\320\275\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
