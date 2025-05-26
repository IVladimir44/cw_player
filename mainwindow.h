#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTimer>
#include <QListWidget>
#include <QUrl>
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
class QListWidgetItem;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum class RepeatMode {
        NoRepeat,
        RepeatAll,
        RepeatOne
    };

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openFile();
    void clearPlaylist();
    void removeSelectedTrack();

    void togglePlayPause();
    void playAudio();
    void pauseAudio();
    void stopAudio();
    void nextTrack();
    void previousTrack();

    void toggleShuffle();
    void toggleRepeat();

    void updatePosition(qint64 position);
    void setPosition(int position);
    void updateDuration(qint64 duration);
    void updateVolume(int volume);
    void updatePlaybackState(QMediaPlayer::PlaybackState state);
    void updateTimeDisplay();

    void handleMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void playlistItemActivated(QListWidgetItem *item);

private:
    void setupModernTheme();
    void setupConnections();
    void setupInitialSettings();
    void setupShortcuts();
    void loadCurrentTrack();
    void updateTrackInfo();
    void updatePlaybackButtons();

    Ui::MainWindow *ui;

    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QTimer *updateTimer;

    QList<QUrl> playlist;
    int currentTrackIndex;

    bool isPlaying;
    bool isShuffle;
    RepeatMode repeatMode;
};

#endif // MAINWINDOW_H
