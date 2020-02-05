#ifndef _WORKER_MUSIC_PLAYER_H
#define _WORKER_MUSIC_PLAYER_H

#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QBuffer>
#include <QAudioOutput>

#include "workers\Worker.h"

class WorkerMusicPlayer : public Worker
{
	Q_OBJECT

public:
	WorkerMusicPlayer();
	~WorkerMusicPlayer();

protected:
	void doWork();
	bool init();

public slots:
	void play();
	void setSignalValues(std::vector<float> vSignalValues);

signals:
	

private:
	

};

#endif