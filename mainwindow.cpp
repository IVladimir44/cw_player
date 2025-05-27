#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QUrl>
#include <QFileInfo>
#include <QTime>
#include <QMessageBox>
#include <QKeySequence>
#include <QShortcut>
#include <QStyleFactory>
#include <QApplication>
#include <QPalette>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , player(new QMediaPlayer(this))
    , audioOutput(new QAudioOutput(this))
    , currentTrackIndex(-1)
    , updateTimer(new QTimer(this))
    , isPlaying(false)
    , isShuffle(false)
    , repeatMode(RepeatMode::NoRepeat)
{
    ui->setupUi(this);

    setupModernTheme();

    player->setAudioOutput(audioOutput);

    setupConnections();

    setupInitialSettings();

    setupShortcuts();

    updatePlaybackButtons();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupModernTheme()
{
    setStyleSheet(R"(
        QMainWindow {
            background-color: #2b2b2b;
            color: #ffffff;
        }
        QPushButton {
            background-color: #404040;
            border: 1px solid #606060;
            border-radius: 5px;
            padding: 8px 16px;
            color: #ffffff;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #505050;
        }
        QPushButton:pressed {
            background-color: #353535;
        }
        QPushButton:disabled {
            background-color: #2a2a2a;
            color: #666666;
        }
        QSlider::groove:horizontal {
            border: 1px solid #999999;
            height: 8px;
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);
            margin: 2px 0;
            border-radius: 4px;
        }
        QSlider::handle:horizontal {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);
            border: 1px solid #5c5c5c;
            width: 18px;
            margin: -2px 0;
            border-radius: 9px;
        }
        QListWidget {
            background-color: #353535;
            border: 1px solid #606060;
            border-radius: 5px;
            color: #ffffff;
            selection-background-color: #0078d4;
        }
        QLabel {
            color: #ffffff;
        }
        QStatusBar {
            background-color: #404040;
            color: #ffffff;
        }
    )");
}

void MainWindow::setupConnections()
{
    connect(ui->playButton, &QPushButton::clicked, this, &MainWindow::togglePlayPause);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopAudio);
    connect(ui->prevButton, &QPushButton::clicked, this, &MainWindow::previousTrack);
    connect(ui->nextButton, &QPushButton::clicked, this, &MainWindow::nextTrack);
    connect(ui->shuffleButton, &QPushButton::clicked, this, &MainWindow::toggleShuffle);
    connect(ui->repeatButton, &QPushButton::clicked, this, &MainWindow::toggleRepeat);

    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::updatePosition);
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::updateDuration);
    connect(player, &QMediaPlayer::playbackStateChanged, this, &MainWindow::updatePlaybackState);
    connect(ui->positionSlider, &QSlider::sliderMoved, this, &MainWindow::setPosition);

    connect(ui->volumeSlider, &QSlider::valueChanged, this, &MainWindow::updateVolume);

    connect(player, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::handleMediaStatusChanged);
    connect(ui->playlistWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::playlistItemActivated);
    connect(ui->openPlaylistButton, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(ui->clearPlaylistButton, &QPushButton::clicked, this, &MainWindow::clearPlaylist);
    connect(ui->removeTrackButton, &QPushButton::clicked, this, &MainWindow::removeSelectedTrack);

    connect(updateTimer, &QTimer::timeout, this, &MainWindow::updateTimeDisplay);
    updateTimer->start(1000);
}

void MainWindow::setupInitialSettings()
{
    ui->volumeSlider->setRange(0, 100);
    ui->volumeSlider->setValue(70);
    audioOutput->setVolume(0.7);

    ui->statusLabel->setText("Готовий до відтворення");
    ui->trackInfoLabel->setText("Виберіть файли для відтворення");

    updatePlaybackButtons();
}

void MainWindow::setupShortcuts()
{
    QShortcut *spaceShortcut = new QShortcut(QKeySequence(Qt::Key_Space), this);
    connect(spaceShortcut, &QShortcut::activated, this, &MainWindow::togglePlayPause);

    QShortcut *nextShortcut = new QShortcut(QKeySequence(Qt::Key_Right), this);
    connect(nextShortcut, &QShortcut::activated, this, &MainWindow::nextTrack);

    QShortcut *prevShortcut = new QShortcut(QKeySequence(Qt::Key_Left), this);
    connect(prevShortcut, &QShortcut::activated, this, &MainWindow::previousTrack);

    QShortcut *openShortcut = new QShortcut(QKeySequence::Open, this);
    connect(openShortcut, &QShortcut::activated, this, &MainWindow::openFile);
}

void MainWindow::openFile()
{
    QStringList files = QFileDialog::getOpenFileNames(
        this,
        tr("Виберіть аудіофайли"),
        "",
        tr("Аудіофайли (*.mp3 *.wav *.ogg *.flac *.m4a *.aac);;Все файлы (*)")
        );

    if (!files.isEmpty()) {
        for (const QString &file : files) {
            QUrl trackUrl = QUrl::fromLocalFile(file);
            playlist.append(trackUrl);

            QFileInfo fileInfo(file);
            ui->playlistWidget->addItem(fileInfo.fileName());
        }

        if (currentTrackIndex < 0 && !playlist.isEmpty()) {
            currentTrackIndex = 0;
            loadCurrentTrack();
            updateTrackInfo();
        }

        ui->statusLabel->setText(QString("Завантажено %1 треків").arg(files.size()));
    }
}

void MainWindow::clearPlaylist()
{
    int ret = QMessageBox::question(this, "Очищення плейлиста",
                                    "Ви впевнені, що хочете очистити плейлист?",
                                    QMessageBox::Yes | QMessageBox::No);

    if (ret == QMessageBox::Yes) {
        playlist.clear();
        ui->playlistWidget->clear();
        currentTrackIndex = -1;
        player->stop();
        ui->statusLabel->setText("Плейлист очищено");
        ui->trackInfoLabel->setText("Виберіть файли для програвання");
    }
}

void MainWindow::removeSelectedTrack()
{
    int currentRow = ui->playlistWidget->currentRow();
    if (currentRow >= 0 && currentRow < playlist.size()) {
        playlist.removeAt(currentRow);
        delete ui->playlistWidget->takeItem(currentRow);

        if (currentRow == currentTrackIndex) {
            if (playlist.isEmpty()) {
                currentTrackIndex = -1;
                player->stop();
            } else {
                if (currentTrackIndex >= playlist.size()) {
                    currentTrackIndex = 0;
                }
                loadCurrentTrack();
            }
        } else if (currentRow < currentTrackIndex) {
            currentTrackIndex--;
        }

        updateTrackInfo();
    }
}

void MainWindow::togglePlayPause()
{
    if (playlist.isEmpty()) {
        openFile();
        return;
    }

    if (isPlaying) {
        pauseAudio();
    } else {
        playAudio();
    }
}

void MainWindow::playAudio()
{
    if (currentTrackIndex >= 0 && currentTrackIndex < playlist.size()) {
        player->play();
    }
}

void MainWindow::pauseAudio()
{
    player->pause();
}

void MainWindow::stopAudio()
{
    player->stop();
    player->setPosition(0);
}

void MainWindow::nextTrack()
{
    if (playlist.isEmpty()) return;

    if (isShuffle) {
        currentTrackIndex = QRandomGenerator::global()->bounded(playlist.size());
    } else {
        currentTrackIndex++;
        if (currentTrackIndex >= playlist.size()) {
            if (repeatMode == RepeatMode::RepeatAll) {
                currentTrackIndex = 0;
            } else {
                currentTrackIndex = playlist.size() - 1;
                stopAudio();
                return;
            }
        }
    }

    loadCurrentTrack();
    playAudio();
}

void MainWindow::previousTrack()
{
    if (playlist.isEmpty()) return;

    currentTrackIndex--;
    if (currentTrackIndex < 0) {
        if (repeatMode == RepeatMode::RepeatAll) {
            currentTrackIndex = playlist.size() - 1;
        } else {
            currentTrackIndex = 0;
            stopAudio();
            return;
        }
    }

    loadCurrentTrack();
    playAudio();
}

void MainWindow::toggleShuffle()
{
    isShuffle = !isShuffle;
    ui->shuffleButton->setText(isShuffle ? "Перемішати: УВІМК" : "Перемішати: ВИМК");
    ui->shuffleButton->setStyleSheet(isShuffle ?
                                         "QPushButton { background-color: #0078d4; }" : "");
}

void MainWindow::toggleRepeat()
{
    switch (repeatMode) {
    case RepeatMode::NoRepeat:
        repeatMode = RepeatMode::RepeatAll;
        ui->repeatButton->setText("Повтор: УСІ");
        break;
    case RepeatMode::RepeatAll:
        repeatMode = RepeatMode::RepeatOne;
        ui->repeatButton->setText("Повтор: ОДИН");
        break;
    case RepeatMode::RepeatOne:
        repeatMode = RepeatMode::NoRepeat;
        ui->repeatButton->setText("Повтор: ВИМК");
        break;
    }

    ui->repeatButton->setStyleSheet(repeatMode != RepeatMode::NoRepeat ?
                                        "QPushButton { background-color: #0078d4; }" : "");
}

void MainWindow::loadCurrentTrack()
{
    if (currentTrackIndex >= 0 && currentTrackIndex < playlist.size()) {
        player->setSource(playlist.at(currentTrackIndex));
        ui->playlistWidget->setCurrentRow(currentTrackIndex);
        updateTrackInfo();
    }
}

void MainWindow::updateTrackInfo()
{
    if (currentTrackIndex >= 0 && currentTrackIndex < playlist.size()) {
        QFileInfo fileInfo(playlist.at(currentTrackIndex).toLocalFile());
        ui->trackInfoLabel->setText(QString("Зараз грає: %1").arg(fileInfo.baseName()));
        ui->statusLabel->setText(QString("Трек %1 из %2").arg(currentTrackIndex + 1).arg(playlist.size()));
    } else {
        ui->trackInfoLabel->setText("Виберіть файли для програвання");
        ui->statusLabel->setText("Готовий до програвання");
    }
}

void MainWindow::updatePosition(qint64 position)
{
    ui->positionSlider->setValue(static_cast<int>(position));
}

void MainWindow::setPosition(int position)
{
    player->setPosition(position);
}

void MainWindow::updateDuration(qint64 duration)
{
    ui->positionSlider->setRange(0, static_cast<int>(duration));
}

void MainWindow::updateVolume(int volume)
{
    audioOutput->setVolume(volume / 100.0);
    ui->volumeLabel->setText(QString("Гучність: %1%").arg(volume));
}

void MainWindow::updatePlaybackState(QMediaPlayer::PlaybackState state)
{
    isPlaying = (state == QMediaPlayer::PlayingState);
    updatePlaybackButtons();

    switch (state) {
    case QMediaPlayer::PlayingState:
        ui->statusLabel->setText("Програвання");
        break;
    case QMediaPlayer::PausedState:
        ui->statusLabel->setText("Пауза");
        break;
    case QMediaPlayer::StoppedState:
        ui->statusLabel->setText("Зупинено");
        break;
    }
}

void MainWindow::updatePlaybackButtons()
{
    ui->playButton->setText(isPlaying ? "Пауза" : "Програвання");
    ui->prevButton->setEnabled(!playlist.isEmpty());
    ui->nextButton->setEnabled(!playlist.isEmpty());
    ui->stopButton->setEnabled(!playlist.isEmpty());
}

void MainWindow::handleMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::MediaStatus::EndOfMedia) {
        if (repeatMode == RepeatMode::RepeatOne) {
            player->setPosition(0);
            playAudio();
        } else {
            nextTrack();
        }
    }
}

void MainWindow::playlistItemActivated(QListWidgetItem *item)
{
    int index = ui->playlistWidget->row(item);
    if (index >= 0 && index < playlist.size()) {
        currentTrackIndex = index;
        loadCurrentTrack();
        playAudio();
    }
}

void MainWindow::updateTimeDisplay()
{
    qint64 pos = player->position();
    qint64 dur = player->duration();

    QString posStr = QTime::fromMSecsSinceStartOfDay(pos).toString("mm:ss");
    QString durStr = QTime::fromMSecsSinceStartOfDay(dur).toString("mm:ss");

    ui->timeLabel->setText(QString("%1 / %2").arg(posStr, durStr));

    if (dur > 0) {
        int progress = static_cast<int>((pos * 100) / dur);
        setWindowTitle(QString("Audio Player - %1%").arg(progress));
    } else {
        setWindowTitle("Audio Player");
    }
}
